/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "game/level/entity/ResourceEntity.hpp"

game::level::entity::ResourceEntity::ResourceEntity(uint32_t id, Entity::Platform platform, Value value) :
	Entity(Type::RESOURCE, id),
	m_platform(platform),
	m_value(value)
{
}

game::level::entity::Entity::Platform game::level::entity::ResourceEntity::getPlatform() const
{
	return m_platform;
}

game::level::entity::ResourceEntity::Value game::level::entity::ResourceEntity::getValue() const
{
	return m_value;
}
