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
	class PlatformEntity : public Entity
	{
	public:
		static constexpr size_t MAX_ENTITIES = 3;

		PlatformEntity(uint32_t id, uint32_t platform_count);
		uint32_t getSubID() const;
		float getAngle() const;
		bool isInner() const;
		bool isOuter() const;
		bool getEntity(Entity::Type type, Entity::Data& entity_data) const;
		int getEntities(Entity::Data* entity_array) const;

	protected:
		friend class EntityManager;

		bool putEntity(Entity::Data entity, Entity::Data& conflicting_entity);
		bool removeEntity(Entity::Type type);

	private:
		class Container
		{
		public:
			bool getEntity(Entity::Type type, Entity::Data& entity_data) const;
			bool putEntity(Entity::Data entity_data, Entity::Data& conflicting_entity);
			bool removeEntity(Entity::Type type);
			void loadEntityToArray(Entity::Data*& entity_data_array, int& count) const;

		private:
			Entity::Data m_entity_data;
		};

		uint32_t m_sub_id;
		float m_angle;
		Container m_containers[MAX_ENTITIES];

		int getContainerID(Entity::Type type) const;
		Container* getContainer(Entity::Type type);
		const Container* getContainer(Entity::Type type) const;
	};
}
}
