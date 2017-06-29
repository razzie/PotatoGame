/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <boost/polygon/voronoi_diagram.hpp>
#include <raz/timer.hpp>
#include <raz/random.hpp>
#include "gfx/scene/SceneEntityHandler.hpp"

class Potato;

namespace gfx
{
namespace scene
{
	class Scene;
}
}

class Demo
{
public:
	Demo(Potato& potato);
	void operator()();

private:
	Potato* m_potato;
	raz::Timer m_timer;
	raz::Random m_random;
	boost::polygon::voronoi_diagram<double> m_diagram;
	game::entity::EntityManager m_entities;
	gfx::scene::SceneEntityHandler m_handler;
	unsigned m_progress;

	const boost::polygon::voronoi_vertex<double>& findCloseVertex(const boost::polygon::voronoi_vertex<double>& v) const;
	void addHub(const boost::polygon::voronoi_vertex<double>& v);
	void addHub(const boost::polygon::voronoi_edge<double>& e);
	void addRandomEntity(uint32_t hub);
	void populateHub(uint32_t hub);
};
