/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "game/level/entity/PlatformEntity.hpp"

game::level::entity::PlatformEntity::PlatformEntity(uint32_t id, uint32_t platform_count) :
	Entity(Type::PLATFORM, id)
{
}

float game::level::entity::PlatformEntity::getAngle() const
{
	return 0.0f;
}

bool game::level::entity::PlatformEntity::isInner() const
{
	return false;
}

bool game::level::entity::PlatformEntity::isOuter() const
{
	return false;
}

void game::level::entity::PlatformEntity::getNeighbors(uint32_t* id_array, size_t& count)
{
}

bool game::level::entity::PlatformEntity::getEntity(Entity::Type type, uint32_t& id) const
{
	return false;
}

int game::level::entity::PlatformEntity::getEntities(Entity::Data* entity_array) const
{
	return 0;
}

bool game::level::entity::PlatformEntity::putEntity(Entity::Data entity, Entity::Data& conflicting_entity)
{
	return false;
}

bool game::level::entity::PlatformEntity::removeEntity(Entity::Type type)
{
	return false;
}
