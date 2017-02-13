/*
 * Copyright (C) G�bor G�rzs�ny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <cmath>
#include <boost/polygon/voronoi_builder.hpp>
#include <boost/polygon/voronoi_diagram.hpp>
#include <raz/random.hpp>
#include "common/Point2D.hpp"
#include "ui/scene/Scene.hpp"
#include "ui/scene/model/HubModel.hpp"

static constexpr double PI = 3.14159265358979323846;
static constexpr size_t VORONOI_SCALE = 64;

static void createCentralVoronoiDiagram(boost::polygon::voronoi_diagram<double>& diagram, raz::Random& random, size_t hub_size)
{
	const size_t complexity = 6;
	const float angle_step = static_cast<float>(PI * 2 / complexity);
	float angle_rad = 0.f;

	boost::polygon::voronoi_builder<int> builder;

	builder.insert_point(0, 0);

	for (size_t i = 1; i < hub_size; ++i)
	{
		for (size_t j = 0; j < complexity; ++j)
		{
			float x = std::sin(angle_rad) * (VORONOI_SCALE * i) + random(-8, 8);
			float y = -std::cos(angle_rad) * (VORONOI_SCALE * i) + random(-8, 8);
			
			builder.insert_point((int)x, (int)y);
			angle_rad += angle_step;
		}

		angle_rad += 0.5f * angle_step;
	}

	builder.construct(&diagram);
}

static common::Point2D<float> getVoronoiEdgePoint(const boost::polygon::voronoi_edge<double>* edge)
{
	if (edge->vertex0())
	{
		auto v = edge->vertex0()->vertex();
		return { (float)v.x() / VORONOI_SCALE, (float)v.y() / VORONOI_SCALE };
	}
	else
	{
		using point_type = boost::polygon::detail::point_2d<double>;

		auto* cell1 = edge->cell();
		auto* cell2 = edge->twin()->cell();
		point_type point1 = cell1->point0();
		point_type point2 = cell2->point0();

		if (point1 == point2) {
			if (cell1->contains_segment())
				point1 = cell1->point1();
			else
				point2 = cell2->point1();
		}

		return { (float)point1.x() / VORONOI_SCALE, (float)point1.y() / VORONOI_SCALE };
	}
}

static common::Point2D<float> getVoronoiCellCenter(const boost::polygon::voronoi_cell<double>& cell)
{
	return { (float)cell.point0().x() / VORONOI_SCALE, (float)cell.point0().y() / VORONOI_SCALE };
}

static void insertVoronoiCell(const boost::polygon::voronoi_cell<double>& cell, raz::Random& random, size_t hub_size, ui::core::MeshBuffer<>& meshbuffer)
{
	unsigned points_inserted = 0;
	float height = 0.5f * ((float)hub_size - getVoronoiCellCenter(cell).getDistanceFrom({ 0.f, 0.f }));
	height *= height;
	auto* edge = cell.incident_edge();

	GL::uchar color = random(128, 255);

	do
	{
		if (edge->is_primary())
		{
			auto point = getVoronoiEdgePoint(edge);
			float distance = point.getDistanceFrom({ 0.f, 0.f });

			if (distance < hub_size)
			{
				ui::core::Vertex v {GL::Vec3(point.x, height + 0.125f * ((float)hub_size - distance), point.y), GL::Vec3(0.f, 1.f, 0.f), GL::Color(color, color, color)};
				meshbuffer.vertices.push_back(v);
				++points_inserted;
			}
		}

		edge = edge->next();

	} while (edge != cell.incident_edge());

	if (points_inserted < 4)
	{
		for (unsigned i = 0; i < points_inserted; ++i)
			meshbuffer.vertices.pop_back();
	}
	else
	{
		uint16_t base_index = (uint16_t)meshbuffer.vertices.size() - points_inserted;

		// duplicating vertices for bottom
		for (unsigned i = base_index, len = meshbuffer.vertices.size(); i < len; ++i)
		{
			ui::core::Vertex v = meshbuffer.vertices[i];
			v.position.Y = 0.f;
			meshbuffer.vertices.push_back(v);
		}

		// indexing top
		for (unsigned i = 1; i < points_inserted - 1; ++i)
		{
			meshbuffer.indices.push_back(base_index);
			meshbuffer.indices.push_back(base_index + i + 1);
			meshbuffer.indices.push_back(base_index + i);
		}

		// indexing sides
		for (unsigned i = 0; i < points_inserted; ++i)
		{
			uint16_t top1 = base_index + i;
			uint16_t top2 = base_index + ((i + 1) % points_inserted);
			uint16_t bottom1 = base_index + i + points_inserted;
			uint16_t bottom2 = base_index + ((i + 1) % points_inserted) + points_inserted;

			meshbuffer.indices.push_back(top1);
			meshbuffer.indices.push_back(top2);
			meshbuffer.indices.push_back(bottom1);

			meshbuffer.indices.push_back(top2);
			meshbuffer.indices.push_back(bottom2);
			meshbuffer.indices.push_back(bottom1);
		}
	}
}

typedef std::vector<ui::scene::model::HubModel::Platform, raz::Allocator<ui::scene::model::HubModel::Platform>> PlatformsVector;

static void createPlatforms(PlatformsVector& platforms, size_t hub_size)
{

}

static void insertPlatforms(const PlatformsVector& platforms, ui::core::MeshBuffer<> meshbuffer)
{

}

ui::scene::model::HubModel::HubModel(scene::Scene& scene)
{
	const uint64_t seed = 12345;
	const size_t hub_size = 5;


	core::MeshBuffer<> meshbuffer;
	raz::Random random(seed);

	boost::polygon::voronoi_diagram<double> diagram;
	createCentralVoronoiDiagram(diagram, random, hub_size);
	for (auto& cell : diagram.cells())
		insertVoronoiCell(cell, random, hub_size, meshbuffer);

	createPlatforms(m_platforms, hub_size);
	insertPlatforms(m_platforms, meshbuffer);

	meshbuffer.recalculateNormals();
	m_mesh = meshbuffer.createMesh(scene.getShader("hub"_shader));
}

void ui::scene::model::HubModel::render(scene::Scene& scene)
{
	GL::Mat4 world;
	GL::Mat4 normal;
	getMatrices(world, normal);

	m_mesh.program.SetUniform("world_mat", world);
	m_mesh.program.SetUniform("normal_mat", normal);
	m_mesh.program.SetUniform("screen_mat", scene.getCameraMatrix() * world);
	m_mesh.program.SetUniform("light_source", scene.getCamera().getPosition());

	GL::Context& gl = scene.getContext();
	gl.DrawElements(m_mesh.vertex_array, GL::Primitive::Triangles, 0, m_mesh.num_of_indices, m_mesh.index_type);
}

const ui::scene::model::HubModel::Platform& ui::scene::model::HubModel::getPlatform(size_t id)
{
	return m_platforms[id];
}
