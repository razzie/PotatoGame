/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <array>
#include <cstdint>
#include <GL/Util/Color.hpp>
#include <raz/bitset.hpp>
#include <raz/random.hpp>
#include <raz/timer.hpp>
#include "common/Diplomacy.hpp"
#include "game/entity/EntityManager.hpp"

namespace game
{
namespace player { class Player; }
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

		struct PlayerData
		{
			player::Player* player;
			int player_id;
			int team_id;
			GL::Color color;
		};

		Level(raz::IMemoryPool* memory = nullptr);
		Level(LevelBuilder& builder, raz::IMemoryPool* memory = nullptr);
		State getState() const;
		bool build(LevelBuilder& builder);
		void reset();
		void update();
		bool connectPlayer(player::Player* player);
		bool disconnectPlayer(player::Player* player);
		const PlayerData* getPlayerData(player::Player* player) const;
		const PlayerData* getPlayerData(int player_id) const;
		common::Diplomacy getDiplomacy(game::player::Player* player1, player::Player* player2);

		virtual void onEntityAdd(const entity::Entity* entity);
		virtual void onEntityRemove(entity::Entity::Data entity_data);
		virtual void onEntityPlayerChange(const entity::Entity* entity, int old_player, int new_player);
		virtual void onEntityVisibilityChange(const entity::Entity* entity, int player, bool new_visibility);
		virtual void onEntityMove(const entity::Entity* entity, entity::Entity::Platform src_platform, entity::Entity::Platform dest_platform);

	private:
		//template<class T>
		//using Vector = std::vector<T, raz::Allocator<T>>;

		raz::IMemoryPool* m_memory;
		State m_state;
		entity::EntityManager m_entities;
		std::array<PlayerData, entity::Entity::MAX_PLAYERS> m_players;
		raz::Bitset<entity::Entity::MAX_PLAYERS> m_player_slots;
		raz::Random m_random;
		raz::Timer m_timer;

		void initPlayers();
	};
}
}
