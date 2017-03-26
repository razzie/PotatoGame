/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <cassert>
#include "common/PI.hpp"
#include "game/level/entity/PlatformEntity.hpp"

game::level::entity::PlatformEntity::PlatformEntity(uint32_t id, uint32_t platform_count) :
	Entity(Type::PLATFORM, id)
{
	assert(platform_count % 3 == 0);

	const uint32_t inner_platform_count = platform_count / 3;
	const uint32_t outer_platform_count = inner_platform_count * 2;

	if (id < inner_platform_count)
	{
		m_sub_id = id;
		m_angle = (2.f * (float)common::PI) / inner_platform_count;
	}
	else
	{
		m_sub_id = id - inner_platform_count;
		m_angle = (2.f * (float)common::PI) / outer_platform_count;
	}
}

uint32_t game::level::entity::PlatformEntity::getSubID() const
{
	return m_sub_id;
}

float game::level::entity::PlatformEntity::getAngle() const
{
	return m_angle;
}

bool game::level::entity::PlatformEntity::isInner() const
{
	return (getID() == m_sub_id);
}

bool game::level::entity::PlatformEntity::isOuter() const
{
	return (getID() != m_sub_id);
}

bool game::level::entity::PlatformEntity::getEntity(Entity::Type type, Entity::Data& entity_data) const
{
	const Container* container = getContainer(type);
	if (!container)
		return false;

	return container->getEntity(type, entity_data);
}

int game::level::entity::PlatformEntity::getEntities(Entity::Data* entity_array) const
{
	int count = 0;

	for (int i = 0; i < MAX_ENTITIES; ++i)
		m_containers[i].loadEntityToArray(entity_array, count);

	return count;
}

bool game::level::entity::PlatformEntity::putEntity(Entity::Data entity, Entity::Data& conflicting_entity)
{
	Container* container = getContainer(entity.type);
	if (!container)
		return false;

	return container->putEntity(entity, conflicting_entity);
}

bool game::level::entity::PlatformEntity::removeEntity(Entity::Type type)
{
	Container* container = getContainer(type);
	if (!container)
		return false;

	return container->removeEntity(type);
}

int game::level::entity::PlatformEntity::getContainerID(Entity::Type type) const
{
	switch (type)
	{
	case Entity::Type::TRANSPORT:
	case Entity::Type::SPAWN:
	case Entity::Type::PORTAL:
	case Entity::Type::TRAP:
		return 0;

	case Entity::Type::CHARGE:
	case Entity::Type::RESOURCE:
		return 1;

	case Entity::Type::TRACE:
	case Entity::Type::CREATURE:
		return 2;

	default:
		return -1;
	}
}

game::level::entity::PlatformEntity::Container* game::level::entity::PlatformEntity::getContainer(Entity::Type type)
{
	int container_id = getContainerID(type);
	if (container_id >= 0)
		return &m_containers[container_id];
	else
		return nullptr;
}

const game::level::entity::PlatformEntity::Container* game::level::entity::PlatformEntity::getContainer(Entity::Type type) const
{
	int container_id = getContainerID(type);
	if (container_id >= 0)
		return &m_containers[container_id];
	else
		return nullptr;
}


bool game::level::entity::PlatformEntity::Container::getEntity(Entity::Type type, Entity::Data& entity_data) const
{
	if (m_entity_data.type == type)
	{
		entity_data = m_entity_data;
		return true;
	}

	return false;
}

bool game::level::entity::PlatformEntity::Container::putEntity(Entity::Data entity_data, Entity::Data& conflicting_entity)
{
	if (m_entity_data.type != Entity::Type::NONE)
	{
		conflicting_entity = m_entity_data;
		return false;
	}

	m_entity_data = entity_data;
	return true;
}

bool game::level::entity::PlatformEntity::Container::removeEntity(Entity::Type type)
{
	return false;
}

void game::level::entity::PlatformEntity::Container::loadEntityToArray(Entity::Data*& entity_data_array, int& count) const
{
	if (m_entity_data.type != Entity::Type::NONE)
	{
		*entity_data_array = m_entity_data;
		++entity_data_array;
		++count;
	}
}
