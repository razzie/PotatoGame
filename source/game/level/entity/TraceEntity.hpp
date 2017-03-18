/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
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
	class TraceEntity : public Entity
	{
	public:
		constexpr static int DEFAULT_LIFESPAN = 5;

		TraceEntity(uint32_t id, Entity::Platform platform, player::Player* player);
		Platform getPlatform() const;
		player::Player* getPlayer() const;
		int getLifespan() const;
		void lowerLifespan();

	private:
		Platform m_platform;
		player::Player* m_player;
		int m_lifespan;
	};
}
}
}
