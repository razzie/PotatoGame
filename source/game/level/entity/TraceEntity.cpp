/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "game/level/entity/TraceEntity.hpp"

game::level::entity::TraceEntity::TraceEntity(uint32_t id, Entity::Platform platform, int player_id) :
	Entity(Type::TRACE, id, player_id),
	m_platform(platform),
	m_lifespan(DEFAULT_LIFESPAN)
{
}

game::level::entity::Entity::Platform game::level::entity::TraceEntity::getPlatform() const
{
	return m_platform;
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
