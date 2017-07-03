/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <cmath>
#include <boost/polygon/voronoi_builder.hpp>
#include <boost/polygon/voronoi_diagram.hpp>
#include "common/Point2D.hpp"
#include "common/PI.hpp"
#include "gfx/shape/VoronoiPillarShape.hpp"

static constexpr size_t VORONOI_SCALE = 64;

static void createVoronoiDiagram(boost::polygon::voronoi_diagram<double>& diagram, raz::Random& random, float radius, unsigned complexity)
{
	const float scale = radius / complexity;
	const float angle_step = static_cast<float>(common::PI * 2 / complexity);
	float angle_rad = 0.f;

	boost::polygon::voronoi_builder<int> builder;

	builder.insert_point(0, 0);

	for (size_t i = 1; i < complexity; ++i)
	{
		for (size_t j = 0; j < complexity; ++j)
		{
			float x = std::sin(angle_rad) * (VORONOI_SCALE * scale * i) + random(-16, 16);
			float y = -std::cos(angle_rad) * (VORONOI_SCALE * scale * i) + random(-16, 16);

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
		return{ (float)v.x() / VORONOI_SCALE, (float)v.y() / VORONOI_SCALE };
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

		return{ (float)point1.x() / VORONOI_SCALE, (float)point1.y() / VORONOI_SCALE };
	}
}

static GL::Vec3 getVoronoiCellPosition(const boost::polygon::voronoi_cell<double>& cell, float radius)
{
	float x = (float)cell.point0().x() / VORONOI_SCALE;
	float z = (float)cell.point0().y() / VORONOI_SCALE;

	float y = 0.5f * (radius - common::Point2D<float>{x, z}.getDistanceFrom({ 0.f, 0.f }));

	return GL::Vec3(x, y, z);
}

static size_t getVoronoiCellPointCount(const boost::polygon::voronoi_cell<double>& cell, float radius)
{
	size_t valid_points = 0;

	auto* edge = cell.incident_edge();

	do
	{
		if (edge->is_primary())
		{
			auto point = getVoronoiEdgePoint(edge);
			float distance = point.getDistanceFrom({ 0.f, 0.f });

			if (distance < radius)
				++valid_points;
		}

		edge = edge->next();

	} while (edge != cell.incident_edge());

	return valid_points;
}

static void insertVoronoiCell(const boost::polygon::voronoi_cell<double>& cell, raz::Random& random, float radius, gfx::core::MeshBuffer<>& meshbuffer)
{
	const common::Point2D<float> center{ 0.f,0.f };

	unsigned points_inserted = 0;
	GL::Vec3 pos = getVoronoiCellPosition(cell, radius);
	float height = pos.Y * random(0.8f, 1.2f);
	auto* edge = cell.incident_edge();

	GL::Color color = random(0, 1) ? GL::Color(224, 224, 224) : GL::Color(128, 128, 128);

	do
	{
		if (edge->is_primary())
		{
			auto point = getVoronoiEdgePoint(edge);
			float distance = point.getDistanceFrom(center);

			if (distance < radius)
			{
				gfx::core::Vertex v{ GL::Vec3(point.x, 0.f, point.y), GL::Vec3(0.f, 1.f, 0.f), color };
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
		float radius = random(0.f, 0.5f);

		// duplicating vertices for top
		for (unsigned i = base_index, len = meshbuffer.vertices.size(); i < len; ++i)
		{
			gfx::core::Vertex v = meshbuffer.vertices[i];

			float distance = center.getDistanceFrom({ v.position.X, v.position.Z });

			v.position.X = 0.5f * std::cbrt(0.75f * v.position.X) + (pos.X * radius);
			v.position.Z = 0.5f * std::cbrt(0.75f * v.position.Z) + (pos.Z * radius);

			v.position.Y = 3.f * height + 0.25f * (radius - distance);

			v.color = color;

			meshbuffer.vertices.push_back(v);
		}

		// indexing bottom
		//for (unsigned i = 1; i < points_inserted - 1; ++i)
		//{
		//	meshbuffer.indices.push_back(base_index);
		//	meshbuffer.indices.push_back(base_index + i);
		//	meshbuffer.indices.push_back(base_index + i + 1);
		//}

		// indexing sides
		for (unsigned i = 0; i < points_inserted; ++i)
		{
			uint16_t top1 = base_index + i;
			uint16_t top2 = base_index + ((i + 1) % points_inserted);
			uint16_t bottom1 = base_index + i + points_inserted;
			uint16_t bottom2 = base_index + ((i + 1) % points_inserted) + points_inserted;

			meshbuffer.indices.push_back(top1);
			meshbuffer.indices.push_back(bottom1);
			meshbuffer.indices.push_back(top2);

			meshbuffer.indices.push_back(top2);
			meshbuffer.indices.push_back(bottom1);
			meshbuffer.indices.push_back(bottom2);
		}

		// indexing top
		for (unsigned i = 1; i < points_inserted - 1; ++i)
		{
			meshbuffer.indices.push_back(base_index + points_inserted);
			meshbuffer.indices.push_back(base_index + points_inserted + i + 1);
			meshbuffer.indices.push_back(base_index + points_inserted + i);
		}
	}
}

gfx::shape::VoronoiPillarShape::VoronoiPillarShape(float radius, unsigned complexity) :
	m_radius(radius),
	m_complexity(complexity)
{
}

void gfx::shape::VoronoiPillarShape::generate(raz::Random& random, gfx::core::MeshBuffer<>& meshbuffer) const
{
	boost::polygon::voronoi_diagram<double> diagram;

	createVoronoiDiagram(diagram, random, m_radius, m_complexity);
	for (auto& cell : diagram.cells())
		insertVoronoiCell(cell, random, m_radius, meshbuffer);
}
