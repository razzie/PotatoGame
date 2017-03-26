/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "game/entity/PortalEntity.hpp"

game::entity::PortalEntity::PortalEntity(uint32_t id, Entity::Platform platform) :
	Entity(Type::PORTAL, id),
	m_platform(platform)
{
}

game::entity::Entity::Platform game::entity::PortalEntity::getPlatform() const
{
	return m_platform;
}
