/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "game/level/Level.hpp"
#include "game/level/LevelBuilder.hpp"
#include "game/level/entity/EntityManager.hpp"

game::level::Level::Level(raz::IMemoryPool* memory) :
	m_memory(memory),
	m_state(State::BUILD),
	m_entities(this, memory),
	m_players(memory)
{
}

game::level::Level::Level(LevelBuilder& builder, raz::IMemoryPool* memory) :
	Level(memory)
{
	build(builder);
}

game::level::Level::State game::level::Level::getState() const
{
	return m_state;
}

bool game::level::Level::build(LevelBuilder& builder)
{
	if (m_state != State::BUILD)
		return false;

	builder.build(m_entities);
	return true;
}

void game::level::Level::reset()
{
}

bool game::level::Level::connectPlayer(game::player::Player * player)
{
	return false;
}

bool game::level::Level::disconnectPlayer(game::player::Player * player)
{
	return false;
}

common::Diplomacy game::level::Level::getDiplomacy(game::player::Player* player1, player::Player* player2)
{
	return common::Diplomacy();
}

void game::level::Level::onEntityAdd(const entity::Entity* entity)
{
}

void game::level::Level::onEntityRemove(entity::Entity::Data entity_data)
{
}

void game::level::Level::onEntityPlayerChange(const entity::Entity* entity, player::Player* old_player, player::Player* new_player)
{
}

void game::level::Level::onEntityMove(const entity::Entity* entity, entity::Entity::Platform src_platform, entity::Entity::Platform dest_platform)
{
}
