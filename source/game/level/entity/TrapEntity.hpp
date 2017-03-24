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
	class TrapEntity : public Entity
	{
	public:
		TrapEntity(uint32_t id, Entity::Platform platform, int player_id);
		Platform getPlatform() const;

	private:
		Platform m_platform;
	};
}
}
}
