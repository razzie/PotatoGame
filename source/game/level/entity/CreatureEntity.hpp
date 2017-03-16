/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <array>
#include "game/level/entity/Entity.hpp"

namespace game
{
namespace level
{
namespace entity
{
	class CreatureEntity : public Entity
	{
	public:
		CreatureEntity(uint32_t id, uint64_t seed, Entity::Platform platform, player::Player* player);
		uint64_t getSeed() const;
		Platform getPlatform() const;
		player::Player* getPlayer() const;
		void setPlayer(player::Player* player);

	private:
		uint64_t m_seed;
		Platform m_platform;
		player::Player* m_player;
	};
}
}
}
