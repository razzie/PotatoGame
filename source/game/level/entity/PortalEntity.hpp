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
	class PortalEntity : public Entity
	{
	public:
		PortalEntity(uint32_t id, Entity::Platform platform);
		Platform getPlatform() const;

	private:
		Platform m_platform;
	};
}
}
}
