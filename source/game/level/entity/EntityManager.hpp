/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <vector>
#include <raz/memory.hpp>
#include "game/level/entity/HubEntity.hpp"
#include "game/level/entity/PlatformEntity.hpp"
#include "game/level/entity/TransportEntity.hpp"
#include "game/level/entity/ChargeEntity.hpp"
#include "game/level/entity/ResourceEntity.hpp"
#include "game/level/entity/TraceEntity.hpp"
#include "game/level/entity/SpawnEntity.hpp"
#include "game/level/entity/PortalEntity.hpp"
#include "game/level/entity/TrapEntity.hpp"
#include "game/level/entity/CreatureEntity.hpp"

namespace game
{
namespace level
{
namespace entity
{
	class EntityManager
	{
	public:
		struct Result
		{
			enum Type
			{
				OK,
				FAIL,
				CONFLICT
			};

			Type type;
			Entity* entity = nullptr;
			Entity* conflicting_entity = nullptr;
		};

		EntityManager(raz::IMemoryPool* memory = nullptr);
		bool addPlayer(player::Player* player);
		bool removePlayer(player::Player* player);
		void reset();
		Result addHub(uint64_t seed, uint32_t size, HubEntity::Platform platform, bool player_start = false);
		Result addTransport(Entity::Platform platform1, Entity::Platform platform2);
		Result addCharge(Entity::Platform platform);
		Result addResource(Entity::Platform platform, ResourceEntity::Value value);
		Result addTrace(Entity::Platform platform, player::Player* player);
		Result addSpawn(Entity::Platform platform, player::Player* player);
		Result addPortal(Entity::Platform platform);
		Result addTrap(Entity::Platform platform, player::Player* player);
		Result addCreature(uint64_t seed, Entity::Platform platform, player::Player* player);
		Entity* getEntity(Entity::Type type, uint32_t id);
		HubEntity* getHub(uint32_t id);
		PlatformEntity* getPlatform(Entity::Platform platform);
		ChargeEntity* getCharge(uint32_t id);
		ResourceEntity* getResource(uint32_t id);
		TraceEntity* getTrace(uint32_t id);
		SpawnEntity* getSpawn(uint32_t id);
		PortalEntity* getPortal(uint32_t id);
		TrapEntity* getTrap(uint32_t id);
		CreatureEntity* getCreature(uint32_t id);
		bool removeCharge(uint32_t id);
		bool removeResource(uint32_t id);
		bool removeTrace(uint32_t id);
		bool removeTrap(uint32_t id);
		bool removeCreature(uint32_t id);

	private:
		template<class T>
		using Vector = std::vector<T, raz::Allocator<T>>;

		template<class T>
		struct EntityContainer
		{
			uint32_t last_id = 0;
			Vector<T> entities;

			EntityContainer(raz::IMemoryPool* memory) :
				last_id(0),
				entities(memory)
			{
			}

			T* find(uint32_t id)
			{
				for (auto& entity : entities)
				{
					if (entity.getID() == id)
						return &entity;
				}
				return nullptr;
			}

			bool remove(uint32_t id)
			{
				for (auto it = entities.begin(), end = entities.end(); it != end; ++it)
				{
					if (it->getID() == id)
					{
						entities.erase(it);
						return true;
					}
				}
				return false;
			}
		};

		struct PlayerHubContainer
		{
			uint32_t hub_id = 0;
			bool used = false;
		};

		EntityContainer<HubEntity> m_hubs;
		EntityContainer<TransportEntity> m_transports;
		EntityContainer<ChargeEntity> m_charges;
		EntityContainer<ResourceEntity> m_resources;
		EntityContainer<TraceEntity> m_traces;
		EntityContainer<SpawnEntity> m_spawns;
		EntityContainer<PortalEntity> m_portals;
		EntityContainer<TrapEntity> m_traps;
		EntityContainer<CreatureEntity> m_creatures;
		Vector<PlayerHubContainer> m_player_hubs;
	};
}
}
}
