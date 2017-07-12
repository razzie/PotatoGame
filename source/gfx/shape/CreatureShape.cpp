/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <cmath>
#include <raz/random.hpp>
#include "common/PI.hpp"
#include "common/Point2D.hpp"
#include "common/bezier.hpp"
#include "gfx/shape/CreatureShape.hpp"

#pragma warning(push)
#pragma warning(disable: 4267) // possible loss of data

static void insertRingPoints(size_t edges, bool sharp_edges, float height, float radius, GL::Color color, gfx::core::MeshBuffer<>& meshbuffer)
{
	const float angle_step = static_cast<float>(common::PI * 2 / edges);
	float angle_rad = 0.f;

	for (size_t i = 0; i < edges; ++i)
	{
		float x, z;

		if (sharp_edges && i % 2)
		{
			x = std::sin(angle_rad - 0.5f * angle_step);
			z = std::cos(angle_rad - 0.5f * angle_step);
		}
		else
		{
			x = std::sin(angle_rad);
			z = std::cos(angle_rad);
		}

		gfx::core::Vertex v{ GL::Vec3(x * radius, height, z * radius), GL::Vec3(x, 0.f, z), color };
		meshbuffer.vertices.push_back(v);

		angle_rad += angle_step;
	}
}

static void insertFirstRing(size_t edges, bool sharp_edges, float height, float radius, GL::Color color, gfx::core::MeshBuffer<>& meshbuffer)
{
	uint16_t base_index = (uint16_t)meshbuffer.vertices.size();
	insertRingPoints(edges, sharp_edges, height, radius, color, meshbuffer);

	for (unsigned i = 1; i < edges - 1; ++i)
	{
		meshbuffer.indices.push_back(base_index);
		meshbuffer.indices.push_back(base_index + i + 1);
		meshbuffer.indices.push_back(base_index + i);
	}

	for (unsigned i = 0; i < edges; ++i)
	{
		uint16_t top1 = base_index + i;
		uint16_t top2 = base_index + ((i + 1) % edges);
		uint16_t bottom1 = base_index + i + edges;
		uint16_t bottom2 = base_index + ((i + 1) % edges) + edges;

		meshbuffer.indices.push_back(top1);
		meshbuffer.indices.push_back(top2);
		meshbuffer.indices.push_back(bottom1);

		meshbuffer.indices.push_back(top2);
		meshbuffer.indices.push_back(bottom2);
		meshbuffer.indices.push_back(bottom1);
	}
}

static void insertRing(size_t edges, bool sharp_edges, float height, float radius, GL::Color color, gfx::core::MeshBuffer<>& meshbuffer)
{
	uint16_t base_index = (uint16_t)meshbuffer.vertices.size();
	insertRingPoints(edges, sharp_edges, height, radius, color, meshbuffer);

	for (unsigned i = 0; i < edges; ++i)
	{
		uint16_t top1 = base_index + i;
		uint16_t top2 = base_index + ((i + 1) % edges);
		uint16_t bottom1 = base_index + i + edges;
		uint16_t bottom2 = base_index + ((i + 1) % edges) + edges;

		meshbuffer.indices.push_back(top1);
		meshbuffer.indices.push_back(top2);
		meshbuffer.indices.push_back(bottom1);

		meshbuffer.indices.push_back(top2);
		meshbuffer.indices.push_back(bottom2);
		meshbuffer.indices.push_back(bottom1);
	}
}

static void insertLastRing(size_t edges, bool sharp_edges, float height, float radius, GL::Color color, gfx::core::MeshBuffer<>& meshbuffer)
{
	uint16_t base_index = (uint16_t)meshbuffer.vertices.size();
	insertRingPoints(edges, sharp_edges, height, radius, color, meshbuffer);

	for (unsigned i = 1; i < edges - 1; ++i)
	{
		meshbuffer.indices.push_back(base_index);
		meshbuffer.indices.push_back(base_index + i);
		meshbuffer.indices.push_back(base_index + i + 1);
	}
}

#pragma warning(pop)


gfx::shape::CreatureShape::CreatureShape(uint64_t seed)
{
	raz::Random random(seed);

	m_control_points_count = random(5u, MAX_HEIGHT);
	m_shade = (uint8_t)random(160u, 255u);
	m_edge_mode = random(0u, 2u);

	m_control_points[0] = { 0.0625f, 0.f };
	for (size_t i = 0; i < m_control_points_count; ++i)
	{
		float r = 0.125f * random(1, 4);
		float h = 0.25f * i;
		m_control_points[i + 1] = { r, h };
	}
	m_control_points[m_control_points_count + 1] = { 0.0625f, 0.25f * (m_control_points_count - 1) };
}

void gfx::shape::CreatureShape::generate(gfx::core::MeshBuffer<>& meshbuffer) const
{
	const GL::Color color(m_shade, m_shade, m_shade);
	const size_t detail = m_control_points.size() * 2;
	unsigned edges;
	bool sharp_edges;

	if (m_edge_mode == 1)
	{
		edges = 6;
		sharp_edges = true;
	}
	else if (m_edge_mode == 2)
	{
		edges = 8;
		sharp_edges = true;
	}
	else
	{
		edges = 12;
		sharp_edges = false;
	}

	auto pfirst = common::bezier(m_control_points, m_control_points_count + 2, 0.f);
	insertFirstRing(edges, false, pfirst.y, pfirst.x, color, meshbuffer);

	for (size_t i = 1; i < detail; ++i)
	{
		float t = (float)i / detail;
		auto p = common::bezier(m_control_points, m_control_points_count + 2, t);
		insertRing(edges, sharp_edges, p.y, p.x, color, meshbuffer);
	}

	auto plast = common::bezier(m_control_points, m_control_points_count + 2, 1.f);
	insertLastRing(edges, false, plast.y, plast.x, color, meshbuffer);
}
