/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include "game/entity/Entity.hpp"

namespace game
{
namespace entity
{
	class TraceEntity : public Entity
	{
	public:
		constexpr static int DEFAULT_LIFESPAN = 5;

		TraceEntity(uint32_t id, Entity::Platform platform, int player_id);
		Platform getPlatform() const;
		int getLifespan() const;
		void lowerLifespan();

	private:
		Platform m_platform;
		int m_lifespan;
	};
}
}
