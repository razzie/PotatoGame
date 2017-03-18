/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "game/level/entity/EntityManager.hpp"

game::level::entity::EntityManager::EntityManager(EntityHandler* handler, raz::IMemoryPool* memory) :
	m_handler(handler),
	m_hubs(memory),
	m_transports(memory),
	m_charges(memory),
	m_resources(memory),
	m_traces(memory),
	m_spawns(memory),
	m_portals(memory),
	m_traps(memory),
	m_creatures(memory),
	m_player_hubs(memory)
{
}

bool game::level::entity::EntityManager::addPlayer(player::Player* player, uint32_t& hub_id)
{
	for (auto& hub : m_player_hubs)
	{
		if (!hub.player)
		{
			hub.player = player;
			hub_id = hub.id;
			return true;
		}
	}

	return false;
}

bool game::level::entity::EntityManager::removePlayer(player::Player* player)
{
	for (auto& hub : m_player_hubs)
	{
		if (hub.player == player)
		{
			hub.player = nullptr;
			return true;
		}
	}

	return false;
}

void game::level::entity::EntityManager::reset()
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
	m_player_hubs.clear();
}

game::level::entity::EntityManager::Result game::level::entity::EntityManager::addHub(uint64_t seed, uint32_t size, HubEntity::Position position, bool player_hub)
{
	HubEntity* hub = m_hubs.add(seed, size, position);

	if (player_hub)
		m_player_hubs.emplace_back(hub->getID());

	return Result().success(hub->getData());
}

game::level::entity::EntityManager::Result game::level::entity::EntityManager::addTransport(uint32_t hub1_id, uint32_t hub2_id)
{
	return Result(); // TODO
}

game::level::entity::EntityManager::Result game::level::entity::EntityManager::addTransport(Entity::Platform platform1, Entity::Platform platform2)
{
	PlatformEntity* p1 = getPlatformInternal(platform1);
	PlatformEntity* p2 = getPlatformInternal(platform2);

	if ((p1 == p2) || !p1 || !p2)
		return Result().fail();

	Entity::Data transport_data;
	transport_data.type = Entity::Type::TRANSPORT;
	transport_data.id = m_transports.last_id + 1;

	Entity::Data conflict;

	if (!p1->putEntity(transport_data, conflict))
		return Result().conflict(conflict);

	if (!p2->putEntity(transport_data, conflict))
	{
		p1->removeEntity(Entity::Type::TRANSPORT);
		return Result().conflict(conflict);
	}

	m_transports.add(platform1, platform2);

	return Result().success(transport_data);
}

game::level::entity::EntityManager::Result game::level::entity::EntityManager::addCharge(Entity::Platform platform)
{
	return Result();
}

game::level::entity::EntityManager::Result game::level::entity::EntityManager::addResource(Entity::Platform platform, ResourceEntity::Value value)
{
	return Result();
}

game::level::entity::EntityManager::Result game::level::entity::EntityManager::addTrace(Entity::Platform platform, player::Player* player)
{
	return Result();
}

game::level::entity::EntityManager::Result game::level::entity::EntityManager::addSpawn(Entity::Platform platform, player::Player* player)
{
	return Result();
}

game::level::entity::EntityManager::Result game::level::entity::EntityManager::addPortal(Entity::Platform platform)
{
	return Result();
}

game::level::entity::EntityManager::Result game::level::entity::EntityManager::addTrap(Entity::Platform platform, player::Player* player)
{
	return Result();
}

game::level::entity::EntityManager::Result game::level::entity::EntityManager::addCreature(uint64_t seed, Entity::Platform platform, player::Player* player)
{
	return Result();
}

bool game::level::entity::EntityManager::removeEntity(Entity::Data entity_data)
{
	return false;
}

bool game::level::entity::EntityManager::removeCharge(uint32_t id)
{
	return false;
}

bool game::level::entity::EntityManager::removeResource(uint32_t id)
{
	return false;
}

bool game::level::entity::EntityManager::removeTrace(uint32_t id)
{
	return false;
}

bool game::level::entity::EntityManager::removeTrap(uint32_t id)
{
	return false;
}

bool game::level::entity::EntityManager::removeCreature(uint32_t id)
{
	return false;
}

game::level::entity::EntityManager::Result game::level::entity::EntityManager::moveEntity(Entity::Data entity_data, Entity::Platform src_platform, Entity::Platform dest_platform)
{
	return Result();
}

bool game::level::entity::EntityManager::changeEntityPlayer(Entity::Data entity_data, player::Player* new_player)
{
	return false;
}


int game::level::entity::EntityManager::collect(Entity::Type type, Vector<Entity::Data>& results) const
{
	return 0;
}

int game::level::entity::EntityManager::collect(Entity::Type type, Vector<const Entity*>& results) const
{
	return 0;
}

int game::level::entity::EntityManager::collect(player::Player* player, Vector<Entity::Data>& results) const
{
	return 0;
}

int game::level::entity::EntityManager::collect(player::Player* player, Vector<const Entity*>& results) const
{
	return 0;
}

const game::level::entity::Entity* game::level::entity::EntityManager::getEntity(Entity::Type type, uint32_t id) const
{
	return nullptr;
}

const game::level::entity::Entity* game::level::entity::EntityManager::getEntity(Entity::Type type, Entity::Platform platform) const
{
	return nullptr;
}

const game::level::entity::HubEntity* game::level::entity::EntityManager::getHub(uint32_t id) const
{
	return nullptr;
}

const game::level::entity::HubEntity* game::level::entity::EntityManager::getHub(player::Player* player) const
{
	return nullptr;
}

const game::level::entity::PlatformEntity* game::level::entity::EntityManager::getPlatform(Entity::Platform platform) const
{
	const HubEntity* hub = m_hubs.find(platform.hub_id);
	if (hub)
		return hub->getPlatform(platform.platform_id);
	else
		return nullptr;
}

const game::level::entity::ChargeEntity* game::level::entity::EntityManager::getCharge(uint32_t id) const
{
	return nullptr;
}

const game::level::entity::ResourceEntity* game::level::entity::EntityManager::getResource(uint32_t id) const
{
	return nullptr;
}

const game::level::entity::TraceEntity* game::level::entity::EntityManager::getTrace(uint32_t id) const
{
	return nullptr;
}

const game::level::entity::SpawnEntity* game::level::entity::EntityManager::getSpawn(uint32_t id) const
{
	return nullptr;
}

const game::level::entity::PortalEntity* game::level::entity::EntityManager::getPortal(uint32_t id) const
{
	return nullptr;
}

const game::level::entity::TrapEntity* game::level::entity::EntityManager::getTrap(uint32_t id) const
{
	return nullptr;
}

const game::level::entity::CreatureEntity* game::level::entity::EntityManager::getCreature(uint32_t id) const
{
	return nullptr;
}

game::level::entity::PlatformEntity* game::level::entity::EntityManager::getPlatformInternal(Entity::Platform platform)
{
	HubEntity* hub = m_hubs.find(platform.hub_id);
	if (hub)
		return hub->getPlatform(platform.platform_id);
	else
		return nullptr;
}
