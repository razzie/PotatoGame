/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */


#include <cmath>
#include <GL/Math/Vec2.hpp>
#include "common/PI.hpp"
#include "game/entity/EntityManager.hpp"

game::entity::EntityManager::EntityManager(EntityHandler* handler, raz::IMemoryPool* memory) :
	m_handler(handler),
	m_memory(memory),
	m_hubs(memory),
	m_transports(memory),
	m_charges(memory),
	m_resources(memory),
	m_traces(memory),
	m_spawns(memory),
	m_portals(memory),
	m_traps(memory),
	m_creatures(memory)
{
}

bool game::entity::EntityManager::addPlayer(int player, uint32_t& hub_id)
{
	if (player < 0 || player >= Entity::MAX_PLAYERS)
		return false;

	for (size_t n : m_player_hub_slots.truebits())
	{
		PlayerHub& hub = m_player_hubs[n];
		if (hub.player_id < 0)
		{
			hub.player_id = player;
			hub_id = hub.hub_id;
			return true;
		}
	}

	return false;
}

bool game::entity::EntityManager::removePlayer(int player)
{
	if (player < 0 || player >= Entity::MAX_PLAYERS)
		return false;

	removePlayerEntities(player, m_traces);
	removePlayerEntities(player, m_traps);
	removePlayerEntities(player, m_creatures);

	for (auto& spawn : m_spawns.getEntities())
	{
		changeEntityPlayer(spawn.getData(), player);
	}

	for (size_t n : m_player_hub_slots.truebits())
	{
		PlayerHub& data = m_player_hubs[n];
		if (data.player_id == player)
		{
			data.player_id = -1;
			break;
		}
	}

	return true;
}

size_t game::entity::EntityManager::getMaxPlayers() const
{
	return m_player_hubs.size();
}

void game::entity::EntityManager::tick(raz::Random& random)
{
	auto& traces = m_traces.getEntities();
	for (auto it = traces.begin(); it != traces.end(); )
	{
		it->lowerLifespan();

		if (it->getLifespan() == 0)
			it = traces.erase(it);
		else
			++it;
	}

	for (auto& hub : m_hubs.getEntities())
	{
		uint32_t size = hub.getSize();
		unsigned charges = hub.countEntities(Entity::Type::CHARGE);

		if (charges < size)
		{
			for (int i = 0, count = size - charges; i < count; ++i)
			{
				PlatformEntity* platform = hub.getRandomFreePlatformFor(random, Entity::Type::CHARGE);
				if (!platform)
					break;

				addEntity(platform, m_charges, Entity::Platform{ hub.getID(), platform->getID() });
			}
		}
	}
}

void game::entity::EntityManager::reset()
{
	m_hubs.clear();
	m_transports.clear();
	m_charges.clear();
	m_resources.clear();
	m_traces.clear();
	m_spawns.clear();
	m_portals.clear();
	m_traps.clear();
	m_creatures.clear();
	initPlayerHubs();
}

game::entity::EntityManager::Result game::entity::EntityManager::addHub(uint64_t seed, uint32_t size, HubEntity::Position position, bool player_hub)
{
	if (player_hub)
	{
		uint32_t hub_id = m_hubs.peekNextID();

		auto unused_slots = m_player_hub_slots.falsebits();
		auto it = unused_slots.begin();
		if (it == unused_slots.end())
			return Result().fail();

		PlayerHub& data = m_player_hubs[*it];
		data.hub_id = hub_id;
		m_player_hub_slots.set(*it);
	}

	HubEntity* hub = m_hubs.add(seed, size, position, m_memory);
	m_handler->onEntityAdd(hub);
	return Result().success(hub->getData());
}

game::entity::EntityManager::Result game::entity::EntityManager::addTransport(uint32_t hub1_id, uint32_t hub2_id)
{
	HubEntity* hub1 = m_hubs.find(hub1_id);
	if (!hub1)
		return Result().fail();

	HubEntity* hub2 = m_hubs.find(hub2_id);
	if (!hub2)
		return Result().fail();

	GL::Vec2 dir(hub2->getPosition().x - hub1->getPosition().x, hub2->getPosition().z - hub1->getPosition().z);
	dir = dir.Normal();
	float angle = (float)std::atan2(dir.Y, dir.X);

	float half_pi = (float)common::PI / 2.f;

	PlatformEntity* p1 = hub1->getPlatformByAngle(angle + half_pi);
	if (!p1)
		return Result().fail();

	PlatformEntity* p2 = hub2->getPlatformByAngle(angle + (float)common::PI + half_pi);
	if (!p2)
		return Result().fail();

	return addTransport(hub1_id, p1, hub2_id, p2);
}

game::entity::EntityManager::Result game::entity::EntityManager::addTransport(Entity::Platform platform1, Entity::Platform platform2)
{
	return addTransport(platform1.hub_id, getPlatform(platform1), platform2.hub_id, getPlatform(platform2));
}

game::entity::EntityManager::Result game::entity::EntityManager::addCharge(Entity::Platform platform)
{
	return addEntity(platform, m_charges, platform);
}

game::entity::EntityManager::Result game::entity::EntityManager::addResource(Entity::Platform platform, ResourceEntity::Value value)
{
	return addEntity(platform, m_resources, platform, value);
}

game::entity::EntityManager::Result game::entity::EntityManager::addTrace(Entity::Platform platform, int player)
{
	return addEntity(platform, m_traces, platform, player);
}

game::entity::EntityManager::Result game::entity::EntityManager::addSpawn(Entity::Platform platform, int player)
{
	return addEntity(platform, m_spawns, platform, player);
}

game::entity::EntityManager::Result game::entity::EntityManager::addPortal(Entity::Platform platform)
{
	return addEntity(platform, m_portals, platform);
}

game::entity::EntityManager::Result game::entity::EntityManager::addTrap(Entity::Platform platform, int player)
{
	return addEntity(platform, m_traps, platform, player);
}

game::entity::EntityManager::Result game::entity::EntityManager::addCreature(uint64_t seed, Entity::Platform platform, int player)
{
	Result result = addEntity(platform, m_creatures, seed, platform, player);

	if (result.status == Result::Status::SUCCESS)
		updateHubVisibility(platform.hub_id, player);

	return result;
}

bool game::entity::EntityManager::removeEntity(Entity::Data entity_data)
{
	switch (entity_data.type)
	{
	case Entity::Type::CHARGE:
		return removeCharge(entity_data.id);

	case Entity::Type::RESOURCE:
		return removeResource(entity_data.id);

	case Entity::Type::TRACE:
		return removeTrace(entity_data.id);

	case Entity::Type::TRAP:
		return removeTrap(entity_data.id);

	case Entity::Type::CREATURE:
		return removeCreature(entity_data.id);

	default:
		return false;
	}
}

bool game::entity::EntityManager::removeCharge(uint32_t id)
{
	return removeEntity(id, m_charges);
}

bool game::entity::EntityManager::removeResource(uint32_t id)
{
	return removeEntity(id, m_resources);
}

bool game::entity::EntityManager::removeTrace(uint32_t id)
{
	return removeEntity(id, m_traces);
}

bool game::entity::EntityManager::removeTrap(uint32_t id)
{
	return removeEntity(id, m_traps);
}

bool game::entity::EntityManager::removeCreature(uint32_t id)
{
	return removeEntity(id, m_creatures);
}

bool game::entity::EntityManager::changeEntityPlayer(Entity::Data entity_data, int new_player)
{
	switch (entity_data.type)
	{
	case Entity::Type::SPAWN:
		return changeEntityPlayer(entity_data.id, m_spawns, new_player);

	case Entity::Type::CREATURE:
		return changeEntityPlayer(entity_data.id, m_creatures, new_player);

	default:
		return false;
	}
}

game::entity::EntityManager::Result game::entity::EntityManager::moveCreature(uint32_t id, Entity::Platform dest_platform)
{
	CreatureEntity* creature = m_creatures.find(id);
	if (!creature)
		return Result().fail();

	Entity::Platform src_platform = creature->getPlatform();
	uint32_t src_hub = src_platform.hub_id;
	PlatformEntity* src_p = getPlatform(src_platform);
	if (!src_p)
		return Result().fail();

	uint32_t dest_hub = dest_platform.hub_id;
	PlatformEntity* dest_p = getPlatform(dest_platform);
	if (!dest_p)
		return Result().fail();

	Entity::Data creature_data = creature->getData();
	Entity::Data conflict;

	if (!dest_p->putEntity(creature_data, conflict))
		return Result().conflict(conflict);

	src_p->removeEntity(Entity::Type::CREATURE);

	creature->setPlatform(dest_platform);
	m_handler->onEntityMove(creature, src_platform, dest_platform);

	return Result().success(creature_data);
}

void game::entity::EntityManager::initPlayerHubs()
{
	for (PlayerHub& hub : m_player_hubs)
	{
		hub.player_id = -1;
	}

	m_player_hub_slots.reset();
}

game::entity::Entity* game::entity::EntityManager::getEntity(Entity::Data entity_data)
{
	switch (entity_data.type)
	{
	case Entity::Type::CHARGE:
		return m_charges.find(entity_data.id);

	case Entity::Type::RESOURCE:
		return m_resources.find(entity_data.id);

	case Entity::Type::TRACE:
		return m_traces.find(entity_data.id);

	case Entity::Type::TRAP:
		return m_traps.find(entity_data.id);

	case Entity::Type::CREATURE:
		return m_creatures.find(entity_data.id);

	default:
		return false;
	}
}

game::entity::PlatformEntity* game::entity::EntityManager::getPlatform(Entity::Platform platform)
{
	HubEntity* hub = m_hubs.find(platform.hub_id);
	if (hub)
		return hub->getPlatform(platform.platform_id);
	else
		return nullptr;
}

game::entity::EntityManager::Result game::entity::EntityManager::addTransport(uint32_t hub1_id, PlatformEntity* p1, uint32_t hub2_id, PlatformEntity* p2)
{
	if ((p1 == p2) || !p1 || !p2)
		return Result().fail();

	Entity::Platform platform1{ hub1_id, p1->getID() };
	Entity::Platform platform2{ hub2_id, p2->getID() };

	Entity::Data transport_data;
	transport_data.type = Entity::Type::TRANSPORT;
	transport_data.id = m_transports.peekNextID();

	Entity::Data conflict;

	if (!p1->putEntity(transport_data, conflict))
		return Result().conflict(conflict);

	if (!p2->putEntity(transport_data, conflict))
	{
		p1->removeEntity(Entity::Type::TRANSPORT);
		return Result().conflict(conflict);
	}

	TransportEntity* transport = m_transports.add(platform1, platform2);
	m_handler->onEntityAdd(transport);

	return Result().success(transport_data);
}

void game::entity::EntityManager::updateHubVisibility(uint32_t hub_id, int player)
{
	if (player < 0 || player >= Entity::MAX_PLAYERS)
		return;

	HubEntity* hub = m_hubs.find(hub_id);
	if (!hub)
		return;

	unsigned entity_count = hub->countPlayerEntities(hub_id);
	bool visible = entity_count > 0;

	for (uint32_t i = 0, platforms = hub->getPlatformCount(); i < platforms; ++i)
	{
		PlatformEntity* platform = hub->getPlatform(i);

		Entity::Data data[PlatformEntity::MAX_ENTITIES];
		int data_count = platform->getEntities(data);

		for (int j = 0; j < data_count; ++j)
		{
			Entity::Data entity_data = data[j];
			Entity* entity = getEntity(entity_data);
			if (entity)
			{
				entity->setVisibility(player, visible);
			}
		}
	}
}
