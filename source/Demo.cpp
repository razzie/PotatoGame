/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <ctime>
#include <Windows.h>
#include "common/ColorGenerator.hpp"
#include "game/event/entityevents.hpp"
#include "Demo.hpp"
#include "Potato.hpp"

Demo::Demo(Potato& potato) :
	m_potato(&potato),
	m_random((uint64_t)std::time(NULL)),
	m_entities(this, nullptr),
	m_progress(1)
{
}

void Demo::operator()()
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

void Demo::onEntityAdd(const game::entity::Entity* entity)
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
			game::event::AddHubEvent ev({ hub->getID(), hub->getSeed(), hub->getSize(),{ hub->getPosition().x, hub->getPosition().z } });
			m_potato->getRenderThread()(ev);
		}
		break;

	case game::entity::Entity::Type::TRANSPORT:
		{
			auto transport = static_cast<const game::entity::TransportEntity*>(entity);
			game::event::AddTransportEvent ev({ transport->getID(),
				transport->getPlatform1().hub_id, transport->getPlatform1().platform_id,
				transport->getPlatform2().hub_id, transport->getPlatform2().platform_id });
			m_potato->getRenderThread()(ev);
		}
		break;

	case game::entity::Entity::Type::CHARGE:
		{
			auto charge = static_cast<const game::entity::ChargeEntity*>(entity);
			game::event::AddChargeEvent ev({ charge->getID(), charge->getPlatform().hub_id, charge->getPlatform().platform_id });
			m_potato->getRenderThread()(ev);
		}
		break;

	case game::entity::Entity::Type::RESOURCE:
		{
			auto resource = static_cast<const game::entity::ResourceEntity*>(entity);
			auto value = resource->getValue();
			game::event::AddResourceEvent ev({ resource->getID(), value.a * 3 + value.b * 2 + value.c,
				resource->getPlatform().hub_id, resource->getPlatform().platform_id });
			m_potato->getRenderThread()(ev);
		}
		break;

	case game::entity::Entity::Type::TRACE:
		{
			auto trace = static_cast<const game::entity::TraceEntity*>(entity);
			game::event::AddTraceEvent ev({ trace->getID(), 0, color, trace->getPlatform().hub_id, trace->getPlatform().platform_id });
			m_potato->getRenderThread()(ev);
		}
		break;

	case game::entity::Entity::Type::SPAWN:
		{
			auto spawn = static_cast<const game::entity::SpawnEntity*>(entity);
			game::event::AddSpawnEvent ev({ spawn->getID(), 0, color, spawn->getPlatform().hub_id, spawn->getPlatform().platform_id });
			m_potato->getRenderThread()(ev);
		}
		break;

	case game::entity::Entity::Type::PORTAL:
		{
			auto portal = static_cast<const game::entity::PortalEntity*>(entity);
			game::event::AddPortalEvent ev({ portal->getID(), portal->getPlatform().hub_id, portal->getPlatform().platform_id });
			m_potato->getRenderThread()(ev);
		}
		break;

	case game::entity::Entity::Type::TRAP:
		{
			auto trap = static_cast<const game::entity::TrapEntity*>(entity);
			game::event::AddTrapEvent ev({ trap->getID(), 0, color, trap->getPlatform().hub_id, trap->getPlatform().platform_id });
			m_potato->getRenderThread()(ev);
		}
		break;

	case game::entity::Entity::Type::CREATURE:
		{
			auto creature = static_cast<const game::entity::CreatureEntity*>(entity);
			game::event::AddCreatureEvent ev({ creature->getID(), creature->getSeed(), 0, color,
				creature->getPlatform().hub_id, creature->getPlatform().platform_id });
			m_potato->getRenderThread()(ev);
		}
		break;
	}
}

void Demo::onEntityRemove(game::entity::Entity::Data entity_data)
{
}

void Demo::onEntityPlayerChange(const game::entity::Entity* entity, int old_player, int new_player)
{
}

void Demo::onEntityVisibilityChange(const game::entity::Entity* entity, int player, bool new_visibility)
{
}

void Demo::onEntityMove(const game::entity::Entity* entity, game::entity::Entity::Platform src_platform, game::entity::Entity::Platform dest_platform)
{
}

void Demo::addRandomEntity(uint32_t hub)
{
	game::entity::Entity::Platform platform;
	platform.hub_id = hub;
	unsigned type = m_random(1, 5);

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
		if (m_entities.getRandomEmptyPlatform(m_random, game::entity::Entity::Type::TRACE, platform))
		{
			m_entities.addTrace(platform, m_random(0, 5));
		}
		break;

	case 5:
		if (m_entities.getRandomEmptyPlatform(m_random, game::entity::Entity::Type::TRAP, platform))
		{
			m_entities.addTrap(platform, m_random(0, 5));
		}
		break;
	}
}
