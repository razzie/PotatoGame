/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <array>
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
		Entity* getEntity(Entity::Type type) const;
		bool putEntity(Entity* entity, Entity** conflict = nullptr);
		bool removeEntity(Entity::Type type);

	private:
		std::array<PlatformEntity*, 6> m_neighbors;
		Entity* m_transport_spawn_portal_trap;
		Entity* m_charge_resource;
		Entity* m_trace_creature;
		float m_angle;
		bool m_inner;

		Entity*& getContainer(Entity::Type type);
	};
}
}
}
