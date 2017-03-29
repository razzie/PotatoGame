/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <cmath>
#include "common/PI.hpp"
#include "gfx/shape/SphereShape.hpp"

gfx::shape::SphereShape::SphereShape(GL::Vec3 center, float radius, unsigned detail, GL::Color color) :
	m_center(center),
	m_radius(radius),
	m_detail(detail),
	m_color(color)
{
}

void gfx::shape::SphereShape::generate(gfx::core::MeshBuffer<>& meshbuffer) const
{
	insertFirstRing(meshbuffer, (float)common::PI / m_detail);

	for (unsigned i = 2; i < m_detail; ++i)
	{
		float a = (float)common::PI * i / m_detail;
		insertRing(meshbuffer, a);
	}

	insertLastRing(meshbuffer);
}

#pragma warning(push)
#pragma warning(disable: 4267) // possible loss of data

void gfx::shape::SphereShape::insertRingPoints(gfx::core::MeshBuffer<>& meshbuffer, float a) const
{
	const unsigned edges = m_detail;
	const float angle_step = static_cast<float>(common::PI * 2 / edges);
	float angle_rad = 0.f;

	for (unsigned i = 0; i < edges; ++i)
	{
		float r = -std::sin(a) * m_radius;
		float x = std::sin(angle_rad);
		float z = std::cos(angle_rad);
		float y = std::cos(a);
		GL::Vec3 p(x * r, y * -m_radius, z * r);

		gfx::core::Vertex v{ m_center + p, p.Normal(), m_color };
		meshbuffer.vertices.push_back(v);

		angle_rad += angle_step;
	}
}

void gfx::shape::SphereShape::insertFirstRing(gfx::core::MeshBuffer<>& meshbuffer, float a) const
{
	const unsigned edges = m_detail;
	uint16_t center_index = (uint16_t)meshbuffer.vertices.size();
	gfx::core::Vertex v{ m_center + GL::Vec3(0.f, -m_radius, 0.f), GL::Vec3(0.f, -1.f, 0.f), m_color };

	meshbuffer.vertices.push_back(v);
	insertRingPoints(meshbuffer, a);

	for (unsigned i = 0; i < edges; ++i)
	{
		uint16_t bottom1 = center_index + 1 + i;
		uint16_t bottom2 = center_index + 1 + ((i + 1) % edges);

		meshbuffer.indices.push_back(center_index);
		meshbuffer.indices.push_back(bottom2);
		meshbuffer.indices.push_back(bottom1);
	}
}

void gfx::shape::SphereShape::insertRing(gfx::core::MeshBuffer<>& meshbuffer, float a) const
{
	const unsigned edges = m_detail;
	uint16_t base_index = (uint16_t)meshbuffer.vertices.size() - edges;

	insertRingPoints(meshbuffer, a);

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

void gfx::shape::SphereShape::insertLastRing(gfx::core::MeshBuffer<>& meshbuffer) const
{
	const unsigned edges = m_detail;
	uint16_t center_index = (uint16_t)meshbuffer.vertices.size();
	gfx::core::Vertex v{ m_center + GL::Vec3(0.f, m_radius, 0.f), GL::Vec3(0.f, 1.f, 0.f), m_color };

	meshbuffer.vertices.push_back(v);

	for (unsigned i = 0; i < edges; ++i)
	{
		uint16_t top1 = center_index - 1 - i;
		uint16_t top2 = center_index - 1 - ((i + 1) % edges);

		meshbuffer.indices.push_back(center_index);
		meshbuffer.indices.push_back(top2);
		meshbuffer.indices.push_back(top1);
	}
}

#pragma warning(pop)
