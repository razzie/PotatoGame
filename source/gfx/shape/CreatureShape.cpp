/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <cmath>
#include "common/PI.hpp"
#include "common/Point2D.hpp"
#include "common/bezier.hpp"
#include "gfx/shape/CreatureShape.hpp"

#pragma warning(push)
#pragma warning(disable: 4267) // possible loss of data

static void insertRingPoints(size_t edges, float height, float radius, GL::Color color, gfx::core::MeshBuffer<>& meshbuffer)
{
	const float angle_step = static_cast<float>(common::PI * 2 / edges);
	float angle_rad = 0.f;

	for (size_t i = 0; i < edges; ++i)
	{
		float x = std::sin(angle_rad);
		float z = std::cos(angle_rad);

		gfx::core::Vertex v{ GL::Vec3(x * radius, height, z * radius), GL::Vec3(x, 0.f, z), color };
		meshbuffer.vertices.push_back(v);

		angle_rad += angle_step;
	}
}

static void insertFirstRing(size_t edges, float height, float radius, GL::Color color, gfx::core::MeshBuffer<>& meshbuffer)
{
	uint16_t base_index = (uint16_t)meshbuffer.vertices.size();
	insertRingPoints(edges, height, radius, color, meshbuffer);

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

static void insertRing(size_t edges, float height, float radius, GL::Color color, gfx::core::MeshBuffer<>& meshbuffer)
{
	uint16_t base_index = (uint16_t)meshbuffer.vertices.size();
	insertRingPoints(edges, height, radius, color, meshbuffer);

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

static void insertLastRing(size_t edges, float height, float radius, GL::Color color, gfx::core::MeshBuffer<>& meshbuffer)
{
	uint16_t base_index = (uint16_t)meshbuffer.vertices.size();
	insertRingPoints(edges, height, radius, color, meshbuffer);

	for (unsigned i = 1; i < edges - 1; ++i)
	{
		meshbuffer.indices.push_back(base_index);
		meshbuffer.indices.push_back(base_index + i);
		meshbuffer.indices.push_back(base_index + i + 1);
	}
}

#pragma warning(pop)


gfx::shape::CreatureShape::CreatureShape(raz::Random& random, GL::Color color, raz::IMemoryPool* memory) :
	m_control_points(memory),
	m_edges(random(3, 5)),
	m_color(color)
{
	if (m_edges == 5)
		m_edges = 8;

	const size_t parts = random(3, 8);

	m_control_points.push_back({ 0.f, 0.f });
	for (size_t i = 0; i < parts; ++i)
	{
		float r = 0.125f * random(1, 5);
		float h = 0.25f * i;
		m_control_points.push_back({ r, h });
	}
	m_control_points.push_back({ 0.f, 0.25f * (parts - 1) });
}

gfx::shape::CreatureShape::CreatureShape(const Dimensions& dimensions, unsigned edges, GL::Color color) :
	m_control_points(dimensions.get_allocator()),
	m_edges(edges),
	m_color(color)
{
	m_control_points.push_back({ 0.f, 0.f });
	for (size_t i = 0; i < dimensions.size(); ++i)
	{
		float r = 0.125f * dimensions[i];
		float h = 0.25f * i;
		m_control_points.push_back({ r, h });
	}
	m_control_points.push_back({ 0.f, 0.25f * (dimensions.size() - 1) });
}

void gfx::shape::CreatureShape::generate(gfx::core::MeshBuffer<>& meshbuffer) const
{
	const size_t detail = m_control_points.size() * 2;

	auto pfirst = common::bezier(m_control_points, 0.f);
	insertFirstRing(m_edges, pfirst.y, pfirst.x, m_color, meshbuffer);

	for (size_t i = 1; i < detail; ++i)
	{
		float t = (float)i / detail;
		auto p = common::bezier(m_control_points, t);
		insertRing(m_edges, p.y, p.x, m_color, meshbuffer);
	}

	auto plast = common::bezier(m_control_points, 1.f);
	insertLastRing(m_edges, plast.y, plast.x, m_color, meshbuffer);
}
