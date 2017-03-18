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
	class EntityHandler
	{
	public:
		virtual ~EntityHandler() = default;
		virtual void onEntityAdd(const Entity* entity) = 0;
		virtual void onEntityRemove(Entity::Data entity_data) = 0;
		virtual void onEntityPlayerChange(const Entity* entity, player::Player* old_player, player::Player* new_player) = 0;
		virtual void onEntityMove(const Entity* entity, Entity::Platform src_platform, Entity::Platform dest_platform) = 0;
	};

	class EntityManager
	{
	public:
		template<class T>
		using Vector = std::vector<T, raz::Allocator<T>>;

		struct Result
		{
			enum Status
			{
				SUCCESS,
				FAIL,
				CONFLICT
			};

			Status status = Status::FAIL;
			Entity::Data entity;

			Result& success(Entity::Data data)
			{
				status = Status::SUCCESS;
				entity = data;
				return *this;
			}

			Result& fail()
			{
				status = Status::FAIL;
				return *this;
			}

			Result& conflict(Entity::Data data)
			{
				status = Status::CONFLICT;
				entity = data;
				return *this;
			}
		};

		EntityManager(EntityHandler* handler, raz::IMemoryPool* memory = nullptr);
		bool addPlayer(player::Player* player, uint32_t& hub_id);
		bool removePlayer(player::Player* player);
		void reset();
		Result addHub(uint64_t seed, uint32_t size, HubEntity::Position position, bool player_hub = false);
		Result addTransport(uint32_t hub1_id, uint32_t hub2_id);
		Result addTransport(Entity::Platform platform1, Entity::Platform platform2);
		Result addCharge(Entity::Platform platform);
		Result addResource(Entity::Platform platform, ResourceEntity::Value value);
		Result addTrace(Entity::Platform platform, player::Player* player);
		Result addSpawn(Entity::Platform platform, player::Player* player);
		Result addPortal(Entity::Platform platform);
		Result addTrap(Entity::Platform platform, player::Player* player);
		Result addCreature(uint64_t seed, Entity::Platform platform, player::Player* player);
		bool removeEntity(Entity::Data entity_data);
		bool removeCharge(uint32_t id);
		bool removeResource(uint32_t id);
		bool removeTrace(uint32_t id);
		bool removeTrap(uint32_t id);
		bool removeCreature(uint32_t id);
		Result moveEntity(Entity::Data entity_data, Entity::Platform src_platform, Entity::Platform dest_platform);
		bool changeEntityPlayer(Entity::Data entity_data, player::Player* new_player);

		int collect(Entity::Type type, Vector<Entity::Data>& results) const;
		int collect(Entity::Type type, Vector<const Entity*>& results) const;
		int collect(player::Player* player, Vector<Entity::Data>& results) const;
		int collect(player::Player* player, Vector<const Entity*>& results) const;
		const Entity* getEntity(Entity::Type type, uint32_t id) const;
		const Entity* getEntity(Entity::Type type, Entity::Platform platform) const;
		const HubEntity* getHub(uint32_t id) const;
		const HubEntity* getHub(player::Player* player) const;
		const PlatformEntity* getPlatform(Entity::Platform platform) const;
		const ChargeEntity* getCharge(uint32_t id) const;
		const ResourceEntity* getResource(uint32_t id) const;
		const TraceEntity* getTrace(uint32_t id) const;
		const SpawnEntity* getSpawn(uint32_t id) const;
		const PortalEntity* getPortal(uint32_t id) const;
		const TrapEntity* getTrap(uint32_t id) const;
		const CreatureEntity* getCreature(uint32_t id) const;

	private:
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

			template<class... Args>
			T* add(Args... args)
			{
				entities.emplace_back(++last_id, std::forward<Args>(args)...);
				return &entities.back();
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

			const T* find(uint32_t id) const
			{
				for (auto& entity : entities)
				{
					if (entity.getID() == id)
						return &entity;
				}
				return nullptr;
			}

			template<class F>
			bool remove(uint32_t id, F callback)
			{
				for (auto it = entities.begin(), end = entities.end(); it != end; ++it)
				{
					if (it->getID() == id)
					{
						callback(*it);
						entities.erase(it);
						return true;
					}
				}
				return false;
			}

			void clear()
			{
				last_id = 0;
				entities.clear();
			}
		};

		struct PlayerHub
		{
			PlayerHub(uint32_t hub_id) :
				id(hub_id), player(nullptr)
			{
			}

			uint32_t id;
			player::Player* player;
		};

		EntityHandler* m_handler;
		EntityContainer<HubEntity> m_hubs;
		EntityContainer<TransportEntity> m_transports;
		EntityContainer<ChargeEntity> m_charges;
		EntityContainer<ResourceEntity> m_resources;
		EntityContainer<TraceEntity> m_traces;
		EntityContainer<SpawnEntity> m_spawns;
		EntityContainer<PortalEntity> m_portals;
		EntityContainer<TrapEntity> m_traps;
		EntityContainer<CreatureEntity> m_creatures;
		Vector<PlayerHub> m_player_hubs;

		PlatformEntity* getPlatformInternal(Entity::Platform platform);
	};
}
}
}
