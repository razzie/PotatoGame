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
	class PlatformEntity : public Entity
	{
	public:
		PlatformEntity(uint32_t id, uint32_t platform_count);
		PlatformEntity(PlatformEntity& other);
		bool isInner() const;
		bool isOuter() const;
		float getAngle() const;
		void getNeighbors(uint32_t* id_array, size_t& count);
		bool getEntity(Entity::Type type, uint32_t& id) const;
		bool putEntity(Entity::Type type, uint32_t id, Entity::Type& conflict_type, uint32_t& conflict_id);
		bool removeEntity(Entity::Type type);

	private:
		struct Container
		{
			Entity::Type type = Entity::Type::NONE;
			uint32_t id = 0;
		};

		Container m_transport_spawn_portal_trap;
		Container m_charge_resource;
		Container m_trace_creature;
		float m_angle;
		bool m_inner;

		Container& getContainer(Entity::Type type);
	};
}
}
}
