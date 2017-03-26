/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "game/entity/ChargeEntity.hpp"

game::entity::ChargeEntity::ChargeEntity(uint32_t id, Entity::Platform platform) :
	Entity(Type::CHARGE, id),
	m_platform(platform)
{
}

game::entity::Entity::Platform game::entity::ChargeEntity::getPlatform() const
{
	return m_platform;
}
