/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <cstdint>

namespace game
{
namespace player { class Player; }
namespace level
{
namespace entity
{
	class Entity
	{
	public:
		enum Type
		{
			NONE,
			HUB,
			TRANSPORT,
			CHARGE,
			RESOURCE,
			TRACE,
			SPAWN,
			PORTAL,
			TRAP,
			CREATURE
		};

		struct Platform
		{
			uint32_t hub_id;
			uint32_t platform_id;
		};

		Entity(Type type, uint32_t id);
		Type getType() const;
		uint32_t getID() const;

	private:
		Type m_type;
		uint32_t m_id;
	};
}
}
}
