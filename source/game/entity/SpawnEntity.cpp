/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "game/entity/SpawnEntity.hpp"

game::entity::SpawnEntity::SpawnEntity(uint32_t id, Entity::Platform platform, int player_id) :
	Entity(Type::SPAWN, id, player_id),
	m_platform(platform)
{
}

game::entity::Entity::Platform game::entity::SpawnEntity::getPlatform() const
{
	return m_platform;
}

void game::entity::SpawnEntity::setPlayerID(int player_id)
{
	m_player_id = player_id;
}
