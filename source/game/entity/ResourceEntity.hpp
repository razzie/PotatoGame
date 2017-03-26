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
	class ResourceEntity : public Entity
	{
	public:
		struct Value
		{
			uint32_t a, b, c;
		};

		ResourceEntity(uint32_t id, Entity::Platform platform, Value value);
		Platform getPlatform() const;
		Value getValue() const;

	private:
		Platform m_platform;
		Value m_value;
	};
}
}
