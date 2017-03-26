/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "game/entity/ResourceEntity.hpp"

game::entity::ResourceEntity::ResourceEntity(uint32_t id, Entity::Platform platform, Value value) :
	Entity(Type::RESOURCE, id),
	m_platform(platform),
	m_value(value)
{
}

game::entity::Entity::Platform game::entity::ResourceEntity::getPlatform() const
{
	return m_platform;
}

game::entity::ResourceEntity::Value game::entity::ResourceEntity::getValue() const
{
	return m_value;
}
