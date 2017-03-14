/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "game/level/entity/Entity.hpp"

game::level::entity::Entity::Entity(Type type, uint32_t id) :
	m_type(type),
	m_id(id)
{
}

game::level::entity::Entity::Type game::level::entity::Entity::getType() const
{
	return m_type;
}

uint32_t game::level::entity::Entity::getID() const
{
	return m_id;
}
