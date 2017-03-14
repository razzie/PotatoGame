/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "game/level/entity/EntityManager.hpp"

game::level::entity::EntityManager::EntityManager(raz::IMemoryPool* memory) :
	m_hubs(memory),
	m_transports(memory),
	m_charges(memory),
	m_resources(memory),
	m_traces(memory),
	m_spawns(memory),
	m_portals(memory),
	m_traps(memory),
	m_creatures(memory),
	m_player_hubs(memory)
{
}
