/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "game/level/entity/TrapEntity.hpp"

game::level::entity::TrapEntity::TrapEntity(uint32_t id, Entity::Platform platform, int player_id) :
	Entity(Type::TRAP, id, player_id),
	m_platform(platform)
{
}

game::level::entity::Entity::Platform game::level::entity::TrapEntity::getPlatform() const
{
	return m_platform;
}
