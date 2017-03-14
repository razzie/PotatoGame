/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include "game/level/entity/Entity.hpp"

namespace game
{
namespace player
{
	class Player;
}
namespace level
{
namespace entity
{
	class PlayerEntity : public Entity
	{
	public:
		PlayerEntity(Entity::Type type, uint32_t id, player::Player* player);
		player::Player* getPlayer() const;

	private:
		player::Player* m_player;
	};
}
}
}
