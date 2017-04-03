/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <ctime>
#include <Windows.h>
#include "common/ColorGenerator.hpp"
#include "gfx/scene/Scene.hpp"
#include "gfx/scene/Demo.hpp"

gfx::scene::Demo::Demo(Scene& scene) :
	m_scene(&scene),
	m_random((uint64_t)std::time(NULL)),
	m_entities(this, scene.getMemoryPool()),
	m_progress(1)
{
	//ShowCursor(FALSE);
}

void gfx::scene::Demo::update()
{
	if (m_timer.peekElapsed() > 1500)
	{
		m_timer.reset();

		auto result = m_entities.addHub(m_random(), m_random(5u, 7u), { 30.f * m_progress, m_random(-15.f, 15.f) });
		if (!result)
			return;

		uint32_t hub = result.entity.id;

		if (hub > 0)
			m_entities.addTransport(hub - 1, hub);

		for (int i = 0; i < 10; ++i)
			addRandomEntity(hub);

		++m_progress;
	}
}

void gfx::scene::Demo::onEntityAdd(const game::entity::Entity* entity)
{
	int player = entity->getPlayerID();
	common::ColorGenerator color_gen;
	GL::Color color;

	if (player >= 0)
		color = color_gen[player];
	else
		color = GL::Color(128, 128, 128);

	switch (entity->getType())
	{
	case game::entity::Entity::Type::HUB:
		{
			auto hub = static_cast<const game::entity::HubEntity*>(entity);
			m_scene->addHub(hub->getID(), hub->getSeed(), hub->getSize(), { hub->getPosition().x, hub->getPosition().z });
		}
		break;

	case game::entity::Entity::Type::TRANSPORT:
		{
			auto transport = static_cast<const game::entity::TransportEntity*>(entity);
			m_scene->addTransport(transport->getID(),
				transport->getPlatform1().hub_id, transport->getPlatform1().platform_id,
				transport->getPlatform2().hub_id, transport->getPlatform2().platform_id);
		}
		break;

	case game::entity::Entity::Type::CHARGE:
		{
			auto charge = static_cast<const game::entity::ChargeEntity*>(entity);
			m_scene->addCharge(charge->getID(), charge->getPlatform().hub_id, charge->getPlatform().platform_id);
		}
		break;

	case game::entity::Entity::Type::RESOURCE:
		{
			auto resource = static_cast<const game::entity::ResourceEntity*>(entity);
			auto value = resource->getValue();
			m_scene->addResource(resource->getID(), value.a * 3 + value.b * 2 + value.c,
				resource->getPlatform().hub_id, resource->getPlatform().platform_id);
		}
		break;

	case game::entity::Entity::Type::TRACE:
		{
			auto trace = static_cast<const game::entity::TraceEntity*>(entity);
			m_scene->addTrace(trace->getID(), color, trace->getPlatform().hub_id, trace->getPlatform().platform_id);
		}
		break;

	case game::entity::Entity::Type::SPAWN:
		{
			auto spawn = static_cast<const game::entity::SpawnEntity*>(entity);
			m_scene->addSpawn(spawn->getID(), color, spawn->getPlatform().hub_id, spawn->getPlatform().platform_id);
		}
		break;

	case game::entity::Entity::Type::PORTAL:
		{
			auto portal = static_cast<const game::entity::PortalEntity*>(entity);
			m_scene->addPortal(portal->getID(), portal->getPlatform().hub_id, portal->getPlatform().platform_id);
		}
		break;

	case game::entity::Entity::Type::TRAP:
		{
			auto trap = static_cast<const game::entity::TrapEntity*>(entity);
			m_scene->addTrap(trap->getID(), color, trap->getPlatform().hub_id, trap->getPlatform().platform_id);
		}
		break;

	case game::entity::Entity::Type::CREATURE:
		{
			auto creature = static_cast<const game::entity::CreatureEntity*>(entity);
			m_scene->addCreature(creature->getID(), creature->getSeed(), color,
				creature->getPlatform().hub_id, creature->getPlatform().platform_id);
		}
		break;
	}
}

void gfx::scene::Demo::onEntityRemove(game::entity::Entity::Data entity_data)
{
}

void gfx::scene::Demo::onEntityPlayerChange(const game::entity::Entity* entity, int old_player, int new_player)
{
}

void gfx::scene::Demo::onEntityVisibilityChange(const game::entity::Entity* entity, int player, bool new_visibility)
{
}

void gfx::scene::Demo::onEntityMove(const game::entity::Entity* entity, game::entity::Entity::Platform src_platform, game::entity::Entity::Platform dest_platform)
{
}

void gfx::scene::Demo::addRandomEntity(uint32_t hub)
{
	game::entity::Entity::Platform platform;
	platform.hub_id = hub;
	unsigned type = m_random(1, 4);

	switch (type)
	{
	case 1:
		if (m_entities.getRandomEmptyPlatform(m_random, game::entity::Entity::Type::CREATURE, platform))
		{
			m_entities.addCreature(m_random(), platform, m_random(0, 5));
		}
		break;

	case 2:
		if (m_entities.getRandomEmptyPlatform(m_random, game::entity::Entity::Type::CHARGE, platform))
		{
			m_entities.addCharge(platform);
		}
		break;

	case 3:
		if (m_entities.getRandomEmptyPlatform(m_random, game::entity::Entity::Type::RESOURCE, platform))
		{
			m_entities.addResource(platform, { m_random(0u, 1u), m_random(0u, 2u), m_random(0u, 3u) });
		}
		break;

	case 4:
		if (m_entities.getRandomEmptyPlatform(m_random, game::entity::Entity::Type::TRAP, platform))
		{
			m_entities.addTrap(platform, m_random(0, 5));
		}
		break;
	}
}
