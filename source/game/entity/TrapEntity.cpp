/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "game/entity/TrapEntity.hpp"

game::entity::TrapEntity::TrapEntity(uint32_t id, Entity::Platform platform, int player_id) :
	Entity(Type::TRAP, id, player_id),
	m_platform(platform)
{
}

game::entity::Entity::Platform game::entity::TrapEntity::getPlatform() const
{
	return m_platform;
}
