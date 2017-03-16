/*
 * Copyright (C) G�bor G�rzs�ny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include "game/level/entity/Entity.hpp"

namespace game
{
namespace level
{
namespace entity
{
	class TrapEntity : public Entity
	{
	public:
		TrapEntity(uint32_t id, Entity::Platform platform, player::Player* player);
		Platform getPlatform() const;
		player::Player* getPlayer() const;

	private:
		Platform m_platform;
		player::Player* m_player;
	};
}
}
}
