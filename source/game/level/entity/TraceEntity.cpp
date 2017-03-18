/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "game/level/entity/TraceEntity.hpp"

game::level::entity::TraceEntity::TraceEntity(uint32_t id, Entity::Platform platform, player::Player* player) :
	Entity(Type::TRACE, id),
	m_platform(platform),
	m_player(player),
	m_lifespan(DEFAULT_LIFESPAN)
{
}

game::level::entity::Entity::Platform game::level::entity::TraceEntity::getPlatform() const
{
	return m_platform;
}

game::player::Player* game::level::entity::TraceEntity::getPlayer() const
{
	return m_player;
}

int game::level::entity::TraceEntity::getLifespan() const
{
	return m_lifespan;
}

void game::level::entity::TraceEntity::lowerLifespan()
{
	if (m_lifespan > 0)
		--m_lifespan;
}
