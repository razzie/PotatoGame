/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "game/level/Level.hpp"
#include "game/level/LevelBuilder.hpp"
#include "game/entity/EntityManager.hpp"

game::level::Level::Level(raz::IMemoryPool* memory) :
	m_memory(memory),
	m_state(State::BUILD),
	m_entities(this, memory)
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
	m_entities.reset();
	initPlayers();

	m_state = State::BUILD;
}

void game::level::Level::update()
{
	m_entities.update(m_random);
}

bool game::level::Level::connectPlayer(game::player::Player* player)
{
	return false;
}

bool game::level::Level::disconnectPlayer(game::player::Player* player)
{
	return false;
}

const game::level::Level::PlayerData* game::level::Level::getPlayerData(player::Player* player) const
{
	return nullptr;
}

const game::level::Level::PlayerData* game::level::Level::getPlayerData(int player_id) const
{
	return nullptr;
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

void game::level::Level::onEntityPlayerChange(const entity::Entity* entity, int old_player, int new_player)
{
}

void game::level::Level::onEntityVisibilityChange(const entity::Entity* entity, int player, bool new_visibility)
{
}

void game::level::Level::onEntityMove(const entity::Entity* entity, entity::Entity::Platform src_platform, entity::Entity::Platform dest_platform)
{
}

void game::level::Level::initPlayers()
{
	for (size_t i = 0; i < entity::Entity::MAX_PLAYERS; ++i)
	{
		PlayerData& data = m_players[i];
		data.player = nullptr;
		data.player_id = i;
		data.team_id = -1;
		//data.color = 
	}

	m_player_slots.reset();
}
