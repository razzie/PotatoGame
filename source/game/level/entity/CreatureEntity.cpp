/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "game/level/entity/CreatureEntity.hpp"

game::level::entity::CreatureEntity::CreatureEntity(uint32_t id, uint64_t seed, Entity::Platform platform, player::Player* player) :
	Entity(Type::CREATURE, id),
	m_seed(seed),
	m_platform(platform),
	m_player(player),
	m_charges(DEFAULT_CHARGES),
	m_max_charges(DEFAULT_MAX_CHARGES)
{
}

uint64_t game::level::entity::CreatureEntity::getSeed() const
{
	return m_seed;
}

game::level::entity::Entity::Platform game::level::entity::CreatureEntity::getPlatform() const
{
	return m_platform;
}

void game::level::entity::CreatureEntity::setPlatform(Platform platform)
{
	m_platform = platform;
}

game::player::Player* game::level::entity::CreatureEntity::getPlayer() const
{
	return m_player;
}

void game::level::entity::CreatureEntity::setPlayer(player::Player* player)
{
	m_player = player;
}

int game::level::entity::CreatureEntity::getCharges() const
{
	return m_charges;
}

void game::level::entity::CreatureEntity::addCharges(int amount)
{
	m_charges += amount;
	if (m_charges > m_max_charges)
		m_charges = m_max_charges;
}

void game::level::entity::CreatureEntity::lowerCharges()
{
	if (m_charges > 0)
		--m_charges;
}

int game::level::entity::CreatureEntity::getMaxCharges() const
{
	return m_max_charges;
}

void game::level::entity::CreatureEntity::setMaxCharges(int amount)
{
	m_max_charges = amount;
}
