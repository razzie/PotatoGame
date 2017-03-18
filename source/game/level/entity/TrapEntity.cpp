/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "game/level/entity/TrapEntity.hpp"

game::level::entity::TrapEntity::TrapEntity(uint32_t id, Entity::Platform platform, player::Player* player) :
	Entity(Type::TRAP, id),
	m_platform(platform),
	m_player(player)
{
}

game::level::entity::Entity::Platform game::level::entity::TrapEntity::getPlatform() const
{
	return m_platform;
}

game::player::Player* game::level::entity::TrapEntity::getPlayer() const
{
	return m_player;
}
