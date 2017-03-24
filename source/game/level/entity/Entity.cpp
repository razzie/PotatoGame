/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <cassert>
#include "game/level/entity/Entity.hpp"

game::level::entity::Entity::Entity(Type type, uint32_t id, int player_id) :
	m_type(type),
	m_id(id),
	m_player_id(0)
{
	assert(type != Type::NONE);
}

game::level::entity::Entity::Type game::level::entity::Entity::getType() const
{
	return m_type;
}

uint32_t game::level::entity::Entity::getID() const
{
	return m_id;
}

int game::level::entity::Entity::getPlayerID() const
{
	return m_player_id;
}

game::level::entity::Entity::Data game::level::entity::Entity::getData() const
{
	return Data(m_type, m_id, m_player_id);
}

bool game::level::entity::Entity::getVisibility(int player_id) const
{
	if (player_id < 0 && player_id >= MAX_PLAYERS)
		return false;
	else
		return m_visibility.test((size_t)player_id);
}

void game::level::entity::Entity::setVisibility(int player_id, bool visible)
{
	if (player_id < 0 && player_id >= MAX_PLAYERS)
		return;

	m_visibility.set((size_t)player_id, visible);
}
