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
	class ChargeEntity : public Entity
	{
	public:
		ChargeEntity(uint32_t id, Entity::Platform platform);
		Platform getPlatform() const;

	private:
		Platform m_platform;
	};
}
}
