/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <cmath>
#include <ctime>
#include <boost/polygon/voronoi_builder.hpp>
#include <Windows.h>
#include "common/PI.hpp"
#include "common/Point2D.hpp"
#include "game/event/entityevents.hpp"
#include "Demo.hpp"
#include "Potato.hpp"

#define PLAYERS 3
#define HUB_DISTANCE 48

Demo::Demo(Potato& potato) :
	m_potato(&potato),
	m_random((uint64_t)std::time(NULL)),
	m_entities(&m_handler, nullptr),
	m_handler(potato),
	m_progress(1)
{
	const unsigned radius = m_random(3u, 4u);
	const unsigned complexity = m_random(5u, 8u);

	const float angle_step = static_cast<float>(common::PI * 2 / complexity);
	float angle_rad = 0.f;

	boost::polygon::voronoi_builder<int> builder;

	builder.insert_point(0, 0);

	for (size_t i = 0; i < radius; ++i)
	{
		for (size_t j = 0; j < complexity; ++j)
		{
			float x = std::sin(angle_rad) * (HUB_DISTANCE * (i + 1)) + m_random(-8, 8);
			float y = -std::cos(angle_rad) * (HUB_DISTANCE * (i + 1)) + m_random(-8, 8);

			builder.insert_point((int)x, (int)y);
			angle_rad += angle_step;
		}

		angle_rad += 0.5f * angle_step;
	}

	builder.construct(&m_diagram);

	for (auto& v : m_diagram.vertices())
	{
		common::Point2D<double> p{ v.vertex().x(), v.vertex().y() };
		if (p.getDistanceFrom({ 0.0, 0.0 }) > radius * HUB_DISTANCE)
			v.color(~0);
	}
}

void Demo::operator()()
{
	if (m_progress < m_diagram.vertices().size() && m_timer.peekElapsed() > 1000)
	{
		auto& vertex = m_diagram.vertices()[m_progress];

		if (vertex.is_degenerate())
		{
			++m_progress;
			return;
		}

		auto* edge = vertex.incident_edge();
		do {
			edge = edge->next();
			addHub(*edge);
		} while (edge != vertex.incident_edge());

		if (vertex.color())
			populateHub(vertex.color());

		m_timer.reset();
		++m_progress;
	}

	std::this_thread::yield();
}

const boost::polygon::voronoi_vertex<double>& Demo::findCloseVertex(const boost::polygon::voronoi_vertex<double>& v) const
{
	if (v.color())
		return v;

	common::Point2D<double> p1{ v.vertex().x(), v.vertex().y() };

	for (auto& vertex : m_diagram.vertices())
	{
		common::Point2D<double> p2{ vertex.vertex().x(), vertex.vertex().y() };
		if (p1.getDistanceFromSq(p2) < 400 && vertex.color())
			return vertex;
	}

	return v;
}

void Demo::addHub(const boost::polygon::voronoi_vertex<double>& v)
{
	if (!v.is_degenerate() && !v.color())
	{
		auto result = m_entities.addHub(m_random(), m_random(5u, 8u), { (float)v.vertex().x(), (float)v.vertex().y() });
		v.color(result.entity.id);
	}
}

void Demo::addHub(const boost::polygon::voronoi_edge<double>& e)
{
	auto* v1 = e.vertex0();
	auto* v2 = e.vertex1();

	if (v1)
	{
		v1 = &findCloseVertex(*v1);
		addHub(*v1);
	}

	if (v2)
	{
		v2 = &findCloseVertex(*v2);
		addHub(*v2);
	}

	if (v1 && v2 && v1->color() && v2->color())
		m_entities.addTransport(v1->color(), v2->color());
}

void Demo::addRandomEntity(uint32_t hub)
{
	game::entity::Entity::Platform platform;
	platform.hub_id = hub;
	unsigned type = m_random(1, 6);

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
		if (m_entities.getRandomEmptyPlatform(m_random, game::entity::Entity::Type::PORTAL, platform))
		{
			m_entities.addPortal(platform);
		}
		break;

	case 6:
		if (m_entities.getRandomEmptyPlatform(m_random, game::entity::Entity::Type::TRAP, platform))
		{
			m_entities.addTrap(platform, m_random(0, PLAYERS - 1));
		}
		break;
	}
}

void Demo::populateHub(uint32_t hub)
{
	game::entity::Entity::Platform platform;
	platform.hub_id = hub;
	m_entities.getRandomEmptyPlatform(m_random, game::entity::Entity::Type::SPAWN, platform);
	m_entities.addSpawn(platform, (m_random() % 2) ? -1 : m_random(-1, PLAYERS - 1));

	for (int i = 0; i < 10; ++i)
		addRandomEntity(hub);
}
