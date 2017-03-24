/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <array>
#include <vector>
#include <raz/memory.hpp>
#include <raz/bitset.hpp>
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
		virtual void onEntityPlayerChange(const Entity* entity, int old_player, int new_player) = 0;
		virtual void onEntityVisibilityChange(const Entity* entity, int player, bool new_visibility) = 0;
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

			operator bool() const
			{
				return (status == Status::SUCCESS);
			}
		};

		EntityManager(EntityHandler* handler, raz::IMemoryPool* memory = nullptr);
		bool addPlayer(int player, uint32_t& hub_id);
		bool removePlayer(int player);
		size_t getMaxPlayers() const;
		void tick();
		void reset();
		Result addHub(uint64_t seed, uint32_t size, HubEntity::Position position, bool player_hub = false);
		Result addTransport(uint32_t hub1_id, uint32_t hub2_id);
		Result addTransport(Entity::Platform platform1, Entity::Platform platform2);
		Result addCharge(Entity::Platform platform);
		Result addResource(Entity::Platform platform, ResourceEntity::Value value);
		Result addTrace(Entity::Platform platform, int player);
		Result addSpawn(Entity::Platform platform, int player);
		Result addPortal(Entity::Platform platform);
		Result addTrap(Entity::Platform platform, int player);
		Result addCreature(uint64_t seed, Entity::Platform platform, int player);
		bool removeEntity(Entity::Data entity_data);
		bool removeCharge(uint32_t id);
		bool removeResource(uint32_t id);
		bool removeTrace(uint32_t id);
		bool removeTrap(uint32_t id);
		bool removeCreature(uint32_t id);
		bool changeEntityPlayer(Entity::Data entity_data, int new_player);
		Result moveCreature(uint32_t id, Entity::Platform dest_platform);

	private:
		template<class T, Entity::Type EType>
		class EntityContainer
		{
		public:
			typedef T* EntityPtr;
			typedef typename Vector<T>::iterator Iterator;

			static constexpr Entity::Type ENTITY_TYPE = EType;

			EntityContainer(raz::IMemoryPool* memory) :
				m_last_id(0),
				m_entities(memory)
			{
			}

			uint32_t peekNextID() const
			{
				return (m_last_id + 1);
			}

			template<class... Args>
			T* add(Args... args)
			{
				m_entities.emplace_back(++m_last_id, std::forward<Args>(args)...);
				return &m_entities.back();
			}

			T* find(uint32_t id)
			{
				for (auto& entity : m_entities)
				{
					if (entity.getID() == id)
						return &entity;
				}
				return nullptr;
			}

			bool find(uint32_t id, Iterator& iter)
			{
				for (auto it = m_entities.begin(), end = m_entities.end(); it != end; ++it)
				{
					if (it->getID() == id)
					{
						iter = it;
						return true;
					}
				}
				return false;
			}

			void remove(Iterator iter)
			{
				m_entities.erase(iter);
			}

			void clear()
			{
				m_last_id = 0;
				m_entities.clear();
			}

			Vector<T>& getEntities()
			{
				return m_entities;
			}

		private:
			uint32_t m_last_id = 0;
			Vector<T> m_entities;
		};

		struct PlayerHub
		{
			uint32_t hub_id;
			int player_id;
		};

		raz::IMemoryPool* m_memory;
		EntityHandler* m_handler;
		EntityContainer<HubEntity, Entity::Type::HUB> m_hubs;
		EntityContainer<TransportEntity, Entity::Type::TRANSPORT> m_transports;
		EntityContainer<ChargeEntity, Entity::Type::CHARGE> m_charges;
		EntityContainer<ResourceEntity, Entity::Type::RESOURCE> m_resources;
		EntityContainer<TraceEntity, Entity::Type::TRACE> m_traces;
		EntityContainer<SpawnEntity, Entity::Type::SPAWN> m_spawns;
		EntityContainer<PortalEntity, Entity::Type::PORTAL> m_portals;
		EntityContainer<TrapEntity, Entity::Type::TRAP> m_traps;
		EntityContainer<CreatureEntity, Entity::Type::CREATURE> m_creatures;
		std::array<PlayerHub, Entity::MAX_PLAYERS> m_player_hubs;
		raz::Bitset<Entity::MAX_PLAYERS> m_player_hub_slots;

		template<class Container, class... Args>
		Result addEntity(Entity::Platform platform, Container& container, Args... args)
		{
			PlatformEntity* p = getPlatform(platform);
			if (!p)
				return Result().fail();

			Entity::Data entity_data;
			entity_data.type = Container::ENTITY_TYPE;
			entity_data.id = container.peekNextID();

			Entity::Data conflict;

			if (p->putEntity(entity_data, conflict))
			{
				Entity* entity = container.add(std::forward<Args>(args)...);
				m_handler->onEntityAdd(entity);
				return Result().success(entity_data);
			}

			return Result().conflict(conflict);
		}

		template<class Container>
		bool removeEntity(uint32_t id, Container& container)
		{
			typename Container::Iterator iter;

			if (!container.find(id, iter))
				return false;

			PlatformEntity* platform = getPlatform(iter->getPlatform());
			if (!platform)
				return false;

			if (!platform->removeEntity(Container::ENTITY_TYPE))
				return false;

			uint32_t hub_id = iter->getPlatform().hub_id;
			int player_id = iter->getPlayerID();
			updateHubVisibility(hub_id, player_id);

			Entity::Data entity_data = iter->getData();
			container.remove(iter);
			m_handler->onEntityRemove(entity_data);
			return true;
		}

		template<class Container>
		void removePlayerEntities(int player_id, Container& container)
		{
			auto& entities = container.getEntities();
			for (auto iter = entities.begin(); iter != entities.end(); )
			{
				if (iter->getPlayerID() == player_id)
				{
					PlatformEntity* platform = getPlatform(iter->getPlatform());
					if (platform)
					{
						if (platform->removeEntity(Container::ENTITY_TYPE))
						{
							uint32_t hub_id = iter->getPlatform().hub_id;
							int player_id = iter->getPlayerID();
							updateHubVisibility(hub_id, player_id);

							Entity::Data entity_data = iter->getData();
							iter = entities.erase(iter);
							m_handler->onEntityRemove(entity_data);
							continue;
						}
					}
				}

				++iter;
			}
		}

		template<class Container>
		bool changeEntityPlayer(uint32_t id, Container& container, int new_player)
		{
			auto* entity = container.find(id);
			if (!entity)
				return false;

			int old_player = entity->getPlayerID();
			entity->setPlayerID(new_player);

			entity->setVisibility(old_player, false);
			entity->setVisibility(new_player, true);

			m_handler->onEntityPlayerChange(entity, old_player, new_player);

			uint32_t hub_id = entity->getPlatform().hub_id;
			updateHubVisibility(hub_id, old_player);
			updateHubVisibility(hub_id, new_player);

			return true;
		}

		void initPlayerHubs();
		Entity* getEntity(Entity::Data entity_data);
		PlatformEntity* getPlatform(Entity::Platform platform);
		Result addTransport(uint32_t hub1_id, PlatformEntity* platform1, uint32_t hub2_id, PlatformEntity* platform2);
		void updateHubVisibility(uint32_t hub_id, int player);
	};
}
}
}
