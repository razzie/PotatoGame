/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <cstdint>
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

	class Level
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
		bool connectPlayer(game::player::Player* player);
		bool disconnectPlayer(game::player::Player* player);

	private:
		raz::IMemoryPool* m_memory;
		State m_state;
		entity::EntityManager m_entities;
	};
}
}
