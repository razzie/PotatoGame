/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <ctime>
#include <Windows.h>
#include "game/event/entityevents.hpp"
#include "Demo.hpp"
#include "Potato.hpp"

#define PLAYERS 3

Demo::Demo(Potato& potato) :
	m_potato(&potato),
	m_random((uint64_t)std::time(NULL)),
	m_entities(&m_handler, nullptr),
	m_handler(potato),
	m_progress(1)
{
}

void Demo::operator()()
{
	if (m_timer.peekElapsed() > 1500)
	{
		m_timer.reset();

		auto result = m_entities.addHub(m_random(), m_random(5u, 7u), { 30.f * m_progress, m_random(-15.f, 15.f) });
		if (!result)
			return;

		uint32_t hub = result.entity.id;

		game::entity::Entity::Platform platform;
		platform.hub_id = hub;
		m_entities.getRandomEmptyPlatform(m_random, game::entity::Entity::Type::SPAWN, platform);
		m_entities.addSpawn(platform, (m_random() % 2) ? -1 : m_random(-1, PLAYERS - 1));

		if (hub > 0)
			m_entities.addTransport(hub - 1, hub);

		for (int i = 0; i < 10; ++i)
			addRandomEntity(hub);

		++m_progress;
	}
}

void Demo::addRandomEntity(uint32_t hub)
{
	game::entity::Entity::Platform platform;
	platform.hub_id = hub;
	unsigned type = m_random(1, 5);

	switch (type)
	{
	case 1:
		if (m_entities.getRandomEmptyPlatform(m_random, game::entity::Entity::Type::CREATURE, platform))
		{
			m_entities.addCreature(m_random(), platform, m_random(0, PLAYERS - 1));
		}
		break;

	case 2:
		if (m_entities.getRandomEmptyPlatform(m_random, game::entity::Entity::Type::CHARGE, platform))
		{
			m_entities.addCharge(platform);
		}
		break;

	case 3:
		if (m_entities.getRandomEmptyPlatform(m_random, game::entity::Entity::Type::RESOURCE, platform))
		{
			m_entities.addResource(platform, { m_random(0u, 1u), m_random(0u, 2u), m_random(0u, 3u) });
		}
		break;

	case 4:
		if (m_entities.getRandomEmptyPlatform(m_random, game::entity::Entity::Type::TRACE, platform))
		{
			m_entities.addTrace(platform, m_random(0, PLAYERS - 1));
		}
		break;

	case 5:
		if (m_entities.getRandomEmptyPlatform(m_random, game::entity::Entity::Type::TRAP, platform))
		{
			m_entities.addTrap(platform, m_random(0, PLAYERS - 1));
		}
		break;
	}
}
