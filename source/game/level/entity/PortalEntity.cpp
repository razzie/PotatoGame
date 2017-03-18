/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "game/level/entity/PortalEntity.hpp"

game::level::entity::PortalEntity::PortalEntity(uint32_t id, Entity::Platform platform) :
	Entity(Type::PORTAL, id),
	m_platform(platform)
{
}

game::level::entity::Entity::Platform game::level::entity::PortalEntity::getPlatform() const
{
	return m_platform;
}
