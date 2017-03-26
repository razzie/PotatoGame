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
	class TransportEntity : public Entity
	{
	public:
		TransportEntity(uint32_t id, Entity::Platform platform1, Entity::Platform platform2);
		Platform getPlatform1() const;
		Platform getPlatform2() const;

	private:
		Platform m_platform1;
		Platform m_platform2;
	};
}
}
