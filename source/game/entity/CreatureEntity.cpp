/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "game/entity/CreatureEntity.hpp"

game::entity::CreatureEntity::CreatureEntity(uint32_t id, uint64_t seed, Entity::Platform platform, int player_id) :
	Entity(Type::CREATURE, id, player_id),
	m_seed(seed),
	m_platform(platform),
	m_charges(DEFAULT_CHARGES),
	m_max_charges(DEFAULT_MAX_CHARGES)
{
}

uint64_t game::entity::CreatureEntity::getSeed() const
{
	return m_seed;
}

game::entity::Entity::Platform game::entity::CreatureEntity::getPlatform() const
{
	return m_platform;
}

void game::entity::CreatureEntity::setPlatform(Platform platform)
{
	m_platform = platform;
}

void game::entity::CreatureEntity::setPlayerID(int player_id)
{
	m_player_id = player_id;
}

int game::entity::CreatureEntity::getCharges() const
{
	return m_charges;
}

void game::entity::CreatureEntity::addCharges(int amount)
{
	m_charges += amount;
	if (m_charges > m_max_charges)
		m_charges = m_max_charges;
}

void game::entity::CreatureEntity::lowerCharges()
{
	if (m_charges > 0)
		--m_charges;
}

int game::entity::CreatureEntity::getMaxCharges() const
{
	return m_max_charges;
}

void game::entity::CreatureEntity::setMaxCharges(int amount)
{
	m_max_charges = amount;
}
