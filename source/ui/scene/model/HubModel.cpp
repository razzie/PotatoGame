/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <cmath>
#include <boost/polygon/voronoi_builder.hpp>
#include <boost/polygon/voronoi_diagram.hpp>
#include <raz/random.hpp>
#include "common/Point2D.hpp"
#include "common/PI.hpp"
#include "ui/scene/Scene.hpp"
#include "ui/scene/model/HubModel.hpp"
#include "ui/scene/model/gen/Wire.hpp"

static constexpr size_t VORONOI_SCALE = 64;
typedef std::vector<ui::scene::model::HubModel::Platform, raz::Allocator<ui::scene::model::HubModel::Platform>> PlatformsVector;

static void createVoronoiDiagram(boost::polygon::voronoi_diagram<double>& diagram, raz::Random& random, size_t hub_size, size_t complexity)
{
	const float scale = (float)hub_size / complexity;
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

static GL::Vec3 getVoronoiCellPosition(const boost::polygon::voronoi_cell<double>& cell, size_t hub_size)
{
	float x = (float)cell.point0().x() / VORONOI_SCALE;
	float z = (float)cell.point0().y() / VORONOI_SCALE;

	float y = 0.5f * ((float)hub_size - common::Point2D<float>{x, z}.getDistanceFrom({ 0.f, 0.f }));

	return GL::Vec3(x, y, z);
}

static size_t getVoronoiCellPointCount(const boost::polygon::voronoi_cell<double>& cell, size_t hub_size)
{
	size_t valid_points = 0;

	auto* edge = cell.incident_edge();

	do
	{
		if (edge->is_primary())
		{
			auto point = getVoronoiEdgePoint(edge);
			float distance = point.getDistanceFrom({ 0.f, 0.f });

			if (distance < hub_size)
				++valid_points;
		}

		edge = edge->next();

	} while (edge != cell.incident_edge());

	return valid_points;
}

static void insertVoronoiCell(const boost::polygon::voronoi_cell<double>& cell, raz::Random& random, size_t hub_size, ui::core::MeshBuffer<>& meshbuffer)
{
	unsigned points_inserted = 0;
	float height = getVoronoiCellPosition(cell, hub_size).Y;
	auto* edge = cell.incident_edge();

	GL::uchar color = random(0, 1) ? 224 : 64;

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

static void createPlatforms(PlatformsVector& platforms, raz::Random& random, size_t hub_size)
{
	const size_t inner_platform_count = hub_size * 3;
	size_t platform_count = inner_platform_count;
	float angle_step = static_cast<float>(common::PI * 2 / inner_platform_count);
	float angle_rad = 0.f;
	float starting_radius = (float)hub_size;
	float radius = 1.5f;

	auto randomize = [&random](GL::Vec3 v) -> GL::Vec3
	{
		float scale = random(0.99f, 1.01f);
		return GL::Vec3(v.X * scale, v.Y + random(-0.0625f, 0.0625f), v.Z * scale);
	};

	auto tighten = [](ui::scene::model::HubModel::Platform& platform)
	{
		platform.inner1 -= platform.center;
		platform.inner1 = platform.inner1 * 0.9f;
		platform.inner1 += platform.center;

		platform.inner2 -= platform.center;
		platform.inner2 = platform.inner2 * 0.9f;
		platform.inner2 += platform.center;

		platform.outer1 -= platform.center;
		platform.outer1 = platform.outer1 * 0.9f;
		platform.outer1 += platform.center;

		platform.outer2 -= platform.center;
		platform.outer2 = platform.outer2 * 0.9f;
		platform.outer2 += platform.center;
	};

	for (size_t i = 0; i < 2; ++i)
	{
		for (size_t j = 0; j < platform_count; ++j)
		{
			float x1 = std::sin(angle_rad);
			float z1 = -std::cos(angle_rad);
			float x2 = std::sin(angle_rad + angle_step);
			float z2 = -std::cos(angle_rad + angle_step);
			float height = random(0.f, 0.25f);

			ui::scene::model::HubModel::Platform platform;
			platform.id = j;
			platform.inner1 = randomize(GL::Vec3(x1 * starting_radius, -0.25f * i + height, z1 * starting_radius));
			platform.inner2 = randomize(GL::Vec3(x2 * starting_radius, -0.25f * i + height, z2 * starting_radius));
			platform.outer1 = randomize(GL::Vec3(x1 * (starting_radius + radius), -0.25f * i + height, z1 * (starting_radius + radius)));
			platform.outer2 = randomize(GL::Vec3(x2 * (starting_radius + radius), -0.25f * i + height, z2 * (starting_radius + radius)));
			platform.center = (platform.inner1 + platform.inner2 + platform.outer1 + platform.outer2) / 4.f;

			tighten(platform);
			platforms.push_back(platform);

			angle_rad += angle_step;
		}

		angle_step *= 0.5f;
		angle_rad = 0.5f * angle_step;
		platform_count *= 2;
		starting_radius += radius;
		radius *= 0.5f;
	}
}

static void insertPlatforms(const PlatformsVector& platforms, raz::Random& random, ui::core::MeshBuffer<>& meshbuffer)
{
	for (auto& platform : platforms)
	{
		GL::uchar color = random(224, 255);
		float height = random(1.f, 2.f);

		ui::core::Vertex inner1 { platform.inner1, GL::Vec3(0.f, 1.f, 0.f), GL::Color(color, color, color) };
		ui::core::Vertex inner2 { platform.inner2, GL::Vec3(0.f, 1.f, 0.f), GL::Color(color, color, color) };
		ui::core::Vertex outer1 { platform.outer1, GL::Vec3(0.f, 1.f, 0.f), GL::Color(color, color, color) };
		ui::core::Vertex outer2 { platform.outer2, GL::Vec3(0.f, 1.f, 0.f), GL::Color(color, color, color) };

		uint16_t base_index = (uint16_t)meshbuffer.vertices.size();

		// insert top vertices
		meshbuffer.vertices.push_back(inner1);
		meshbuffer.vertices.push_back(inner2);
		meshbuffer.vertices.push_back(outer1);
		meshbuffer.vertices.push_back(outer2);

		inner1.position.Y -= 0.25f;
		inner2.position.Y -= 0.25f;
		outer1.position.Y -= 0.25f;
		outer2.position.Y -= 0.25f;
		ui::core::Vertex center { platform.center, GL::Vec3(0.f, -1.f, 0.f), GL::Color() };
		center.position.Y -= 1.f;

		// insert bottom vertices
		meshbuffer.vertices.push_back(inner1);
		meshbuffer.vertices.push_back(inner2);
		meshbuffer.vertices.push_back(outer1);
		meshbuffer.vertices.push_back(outer2);
		meshbuffer.vertices.push_back(center);

		// indexing top vertices
		meshbuffer.indices.push_back(base_index);
		meshbuffer.indices.push_back(base_index + 1);
		meshbuffer.indices.push_back(base_index + 3);
		meshbuffer.indices.push_back(base_index);
		meshbuffer.indices.push_back(base_index + 3);
		meshbuffer.indices.push_back(base_index + 2);

		// indexing front
		meshbuffer.indices.push_back(base_index + 2);
		meshbuffer.indices.push_back(base_index + 3);
		meshbuffer.indices.push_back(base_index + 7);
		meshbuffer.indices.push_back(base_index + 2);
		meshbuffer.indices.push_back(base_index + 7);
		meshbuffer.indices.push_back(base_index + 6);

		// indexing left
		meshbuffer.indices.push_back(base_index + 3);
		meshbuffer.indices.push_back(base_index + 1);
		meshbuffer.indices.push_back(base_index + 5);
		meshbuffer.indices.push_back(base_index + 3);
		meshbuffer.indices.push_back(base_index + 5);
		meshbuffer.indices.push_back(base_index + 7);

		// indexing right
		meshbuffer.indices.push_back(base_index);
		meshbuffer.indices.push_back(base_index + 2);
		meshbuffer.indices.push_back(base_index + 6);
		meshbuffer.indices.push_back(base_index);
		meshbuffer.indices.push_back(base_index + 6);
		meshbuffer.indices.push_back(base_index + 4);

		// indexing back
		meshbuffer.indices.push_back(base_index + 1);
		meshbuffer.indices.push_back(base_index);
		meshbuffer.indices.push_back(base_index + 4);
		meshbuffer.indices.push_back(base_index + 1);
		meshbuffer.indices.push_back(base_index + 4);
		meshbuffer.indices.push_back(base_index + 5);

		// indexing bottom
		meshbuffer.indices.push_back(base_index + 6);
		meshbuffer.indices.push_back(base_index + 7);
		meshbuffer.indices.push_back(base_index + 8);
		meshbuffer.indices.push_back(base_index + 7);
		meshbuffer.indices.push_back(base_index + 5);
		meshbuffer.indices.push_back(base_index + 8);
		meshbuffer.indices.push_back(base_index + 5);
		meshbuffer.indices.push_back(base_index + 4);
		meshbuffer.indices.push_back(base_index + 8);
		meshbuffer.indices.push_back(base_index + 4);
		meshbuffer.indices.push_back(base_index + 6);
		meshbuffer.indices.push_back(base_index + 8);
	}
}

static void insertUpperWires(const boost::polygon::voronoi_diagram<double>& diagram, raz::Random& random, size_t hub_size, size_t complexity, ui::core::MeshBuffer<>& meshbuffer)
{
	const size_t wires = complexity * 2;
	const boost::polygon::voronoi_cell<double> *cell1, *cell2;

	for (size_t i = 0; i < wires; ++i)
	{
		do
		{
			cell1 = &diagram.cells()[random(0u, diagram.cells().size() - 1)];
		} while (getVoronoiCellPointCount(*cell1, hub_size) <= 4);

		for (auto* edge = cell1->incident_edge(); ; edge = edge->next())
		{
			if (edge->is_primary() && edge->twin())
			{
				cell2 = edge->twin()->cell();
				if (cell2 && getVoronoiCellPointCount(*cell2, hub_size) > 4)
					break;
			}
		}

		auto p1 = getVoronoiCellPosition(*cell1, hub_size);
		auto p2 = getVoronoiCellPosition(*cell2, hub_size);
		float drop = -0.25f * hub_size + random(-0.5f, 0.5f);

		p1.X += random(-0.35f, 0.35f);
		p1.Y *= 1.125f;
		p1.Z += random(-0.35f, 0.35f);

		p2.X += random(-0.35f, 0.35f);
		p2.Y *= 1.125f;
		p2.Z += random(-0.35f, 0.35f);

		ui::scene::model::gen::Wire wire(p1, p2, 8, drop);
		wire.generate(meshbuffer);
	}
}

static void insertLowerWires(const PlatformsVector& platforms, raz::Random& random, size_t hub_size, size_t complexity, ui::core::MeshBuffer<>& meshbuffer)
{
	const size_t wires = complexity * 2;
	const size_t max_platform = platforms.size() - 1;

	const float min_distance = 0.5f * hub_size;
	const float max_distance = 1.5f * hub_size;

	for (size_t i = 0; i < wires; ++i)
	{
		size_t platform1, platform2;
		GL::Vec3 p1, p2;
		float distance;

		platform1 = random(0u, max_platform);

		do
		{
			platform2 = random(0u, max_platform);

			p1 = platforms[platform1].center;
			p2 = platforms[platform2].center;
			distance = p1.Distance(p2);
		}
		while (distance < min_distance || distance > max_distance);

		p1.Y -= 0.75f;
		p2.Y -= 0.75f;

		ui::scene::model::gen::Wire wire(p1, p2, 8, 0.25f * distance);
		wire.generate(meshbuffer);
	}
}


ui::scene::model::HubModel::HubModel(scene::Scene& scene)
{
	const uint64_t seed = 12345;
	const size_t hub_size = 6;
	const size_t complexity = 6;


	core::MeshBuffer<> meshbuffer;
	raz::Random random(seed);
	boost::polygon::voronoi_diagram<double> diagram;

	createVoronoiDiagram(diagram, random, hub_size, complexity);
	for (auto& cell : diagram.cells())
		insertVoronoiCell(cell, random, hub_size, meshbuffer);

	createPlatforms(m_platforms, random, hub_size);
	insertPlatforms(m_platforms, random, meshbuffer);

	insertUpperWires(diagram, random, hub_size, complexity, meshbuffer);
	insertLowerWires(m_platforms, random, hub_size, complexity, meshbuffer);

	meshbuffer.recalculateNormals();

	auto& mesh = getMesh();
	mesh = meshbuffer.createMesh();
	mesh.bindShader(scene.getShader("hub"_shader));
}

void ui::scene::model::HubModel::render(scene::Scene& scene)
{
	GL::Mat4 world;
	GL::Mat4 normal;
	getMatrices(world, normal);

	auto& program = scene.getCurrentShader();
	program.SetUniform("world_mat", world);
	program.SetUniform("normal_mat", normal);
	program.SetUniform("screen_mat", scene.getCameraMatrix() * world);
	program.SetUniform("light_source", scene.getCamera().getPosition());

	GL::Context& gl = scene.getContext();
	getMesh().render(gl);
}

const ui::scene::model::HubModel::Platform& ui::scene::model::HubModel::getPlatform(size_t id)
{
	return m_platforms[id];
}
