/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "game/level/entity/SpawnEntity.hpp"

game::level::entity::SpawnEntity::SpawnEntity(uint32_t id, Entity::Platform platform, player::Player* player) :
	Entity(Type::SPAWN, id),
	m_platform(platform),
	m_player(player)
{
}

game::level::entity::Entity::Platform game::level::entity::SpawnEntity::getPlatform() const
{
	return m_platform;
}

game::player::Player* game::level::entity::SpawnEntity::getPlayer() const
{
	return m_player;
}

void game::level::entity::SpawnEntity::setPlayer(player::Player* player)
{
	m_player = player;
}
