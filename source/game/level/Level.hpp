/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <cstdint>
#include "common/Diplomacy.hpp"
#include "game/level/entity/EntityManager.hpp"

namespace game
{
namespace player
{
	class Player;
}
namespace level
{
	class LevelBuilder;

	class Level : public entity::EntityHandler
	{
	public:
		enum State
		{
			BUILD,
			ONLINE,
			OFFLINE
		};

		Level(raz::IMemoryPool* memory = nullptr);
		Level(LevelBuilder& builder, raz::IMemoryPool* memory = nullptr);
		State getState() const;
		bool build(LevelBuilder& builder);
		void reset();
		bool connectPlayer(player::Player* player);
		bool disconnectPlayer(player::Player* player);
		common::Diplomacy getDiplomacy(game::player::Player* player1, player::Player* player2);

		virtual void onEntityAdd(const entity::Entity* entity);
		virtual void onEntityRemove(entity::Entity::Data entity_data);
		virtual void onEntityPlayerChange(const entity::Entity* entity, player::Player* old_player, player::Player* new_player);
		virtual void onEntityMove(const entity::Entity* entity, entity::Entity::Platform src_platform, entity::Entity::Platform dest_platform);

	private:
		template<class T>
		using Vector = std::vector<T, raz::Allocator<T>>;

		raz::IMemoryPool* m_memory;
		State m_state;
		entity::EntityManager m_entities;
		Vector<player::Player*> m_players;
	};
}
}
