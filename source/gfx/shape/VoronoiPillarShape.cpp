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
#include "gfx/shape/WireShape.hpp"
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
	unsigned points_inserted = 0;
	float height = getVoronoiCellPosition(cell, radius).Y;
	auto* edge = cell.incident_edge();

	GL::uchar color = random(0, 1) ? 224 : 64;

	do
	{
		if (edge->is_primary())
		{
			auto point = getVoronoiEdgePoint(edge);
			float distance = point.getDistanceFrom({ 0.f, 0.f });

			if (distance < radius)
			{
				gfx::core::Vertex v{ GL::Vec3(point.x, height + 0.125f * (radius - distance), point.y), GL::Vec3(0.f, 1.f, 0.f), GL::Color(color, color, color) };
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
			gfx::core::Vertex v = meshbuffer.vertices[i];
			v.position.X = std::cbrt(v.position.X);
			v.position.Y *= -0.5f * v.position.Y;
			v.position.Z = std::cbrt(v.position.Z);
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

		// indexing bottom
		for (unsigned i = 1; i < points_inserted - 1; ++i)
		{
			meshbuffer.indices.push_back(base_index + points_inserted);
			meshbuffer.indices.push_back(base_index + points_inserted + i);
			meshbuffer.indices.push_back(base_index + points_inserted + i + 1);
		}
	}
}

static void insertWires(const boost::polygon::voronoi_diagram<double>& diagram, raz::Random& random, float radius, unsigned complexity, gfx::core::MeshBuffer<>& meshbuffer)
{
	const size_t wires = complexity * 2;
	const boost::polygon::voronoi_cell<double> *cell1, *cell2;

	for (size_t i = 0; i < wires; ++i)
	{
		do
		{
			cell1 = &diagram.cells()[random(0u, diagram.cells().size() - 1)];
		} while (getVoronoiCellPointCount(*cell1, radius) <= 4);

		for (auto* edge = cell1->incident_edge(); ; edge = edge->next())
		{
			if (edge->is_primary() && edge->twin())
			{
				cell2 = edge->twin()->cell();
				if (cell2 && getVoronoiCellPointCount(*cell2, radius) > 4)
					break;
			}
		}

		auto p1 = getVoronoiCellPosition(*cell1, radius);
		auto p2 = getVoronoiCellPosition(*cell2, radius);
		float drop = -0.25f * radius + random(-0.5f, 0.5f);

		p1.X += random(-0.35f, 0.35f);
		p1.Y *= 1.125f;
		p1.Z += random(-0.35f, 0.35f);

		p2.X += random(-0.35f, 0.35f);
		p2.Y *= 1.125f;
		p2.Z += random(-0.35f, 0.35f);

		gfx::shape::WireShape wire(p1, p2, 8, drop);
		wire.generate(meshbuffer);
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

	insertWires(diagram, random, m_radius, m_complexity, meshbuffer);
}
