/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "game/level/entity/PlayerEntity.hpp"

game::level::entity::PlayerEntity::PlayerEntity(Entity::Type type, uint32_t id, player::Player* player) :
	Entity(type, id),
	m_player(player)
{
}

game::player::Player* game::level::entity::PlayerEntity::getPlayer() const
{
	return m_player;
}
