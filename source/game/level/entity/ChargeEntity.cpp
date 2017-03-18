/*
 * Copyright (C) G�bor G�rzs�ny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "game/level/entity/ChargeEntity.hpp"

game::level::entity::ChargeEntity::ChargeEntity(uint32_t id, Entity::Platform platform) :
	Entity(Type::CHARGE, id),
	m_platform(platform)
{
}

game::level::entity::Entity::Platform game::level::entity::ChargeEntity::getPlatform() const
{
	return m_platform;
}
