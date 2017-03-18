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
		float getAngle() const;
		bool isInner() const;
		bool isOuter() const;
		void getNeighbors(uint32_t* id_array, size_t& count);
		bool getEntity(Entity::Type type, uint32_t& id) const;
		int getEntities(Entity::Data* entity_array) const;

	protected:
		friend class EntityManager;

		bool putEntity(Entity::Data entity, Entity::Data& conflicting_entity);
		bool removeEntity(Entity::Type type);

	private:
		struct Container
		{
			Entity::Type type = Entity::Type::NONE;
			uint32_t id = 0;

			bool getEntity(Entity::Type type, uint32_t& id) const;
			bool putEntity(Entity::Data entity, Entity::Data& conflicting_entity);
			bool removeEntity(Entity::Type type);
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
