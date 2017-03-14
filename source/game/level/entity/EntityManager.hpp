/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <vector>
#include <raz/memory.hpp>
#include "game/level/entity/HubEntity.hpp"
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
		Result addHub(uint64_t seed, uint32_t size, float x, float z);
		Result addTransport(uint32_t hub1_id, uint32_t hub1_platform_id, uint32_t hub2_id, uint32_t hub2_platform_id);
		Result addCharge(uint32_t hub_id, uint32_t platform_id);
		Result addResource(uint32_t hub_id, uint32_t platform_id, ResourceEntity::Value value);
		Result addTrace(uint32_t hub_id, uint32_t platform_id, player::Player* player);
		Result addSpawn(uint32_t hub_id, uint32_t platform_id, player::Player* player);
		Result addPortal(uint32_t hub_id, uint32_t platform_id);
		Result addTrap(uint32_t hub_id, uint32_t platform_id, player::Player* player);
		Result addCreature(uint64_t seed, uint32_t hub_id, uint32_t platform_id, player::Player* player);

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

		EntityContainer<HubEntity> m_hubs;
		EntityContainer<TransportEntity> m_transports;
		EntityContainer<ChargeEntity> m_charges;
		EntityContainer<ResourceEntity> m_resources;
		EntityContainer<TraceEntity> m_traces;
		EntityContainer<SpawnEntity> m_spawns;
		EntityContainer<PortalEntity> m_portals;
		EntityContainer<TrapEntity> m_traps;
		EntityContainer<CreatureEntity> m_creatures;

		Vector<HubEntity*> m_player_hubs;
	};
}
}
}
