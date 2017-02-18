/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <cstdint>

namespace game
{
namespace level
{
namespace entity
{
	class Entity
	{
	public:
		enum Type
		{
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

		Entity(Type type, uint32_t id, uint32_t parent_id);
		Type getType() const;
		uint32_t getID() const;
		uint32_t getParentID() const;

	private:
		Type m_type;
		uint32_t m_id;
		uint32_t m_parent_id;
	};
}
}
}
