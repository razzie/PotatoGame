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
			PLATFORM,
			TRANSPORT,
			CHARGE,
			RESOURCE,
			TRACE,
			SPAWN,
			PORTAL,
			TRAP,
			CREATURE
		};

		struct Data
		{
			Type type = Type::NONE;
			uint32_t id = 0;

			Data() = default;

			Data(Type t, uint32_t i) :
				type(t), id(i)
			{
			}
		};

		struct Platform
		{
			uint32_t hub_id;
			uint32_t platform_id;
		};

		Entity(Type type, uint32_t id);
		Type getType() const;
		uint32_t getID() const;
		Data getData() const;

	private:
		Type m_type;
		uint32_t m_id;
	};
}
}
}
