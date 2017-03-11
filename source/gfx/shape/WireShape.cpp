/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <cmath>
#include <GL/Math/Mat4.hpp>
#include "common/PI.hpp"
#include "common/GLlerp.hpp"
#include "gfx/shape/WireShape.hpp"

gfx::shape::WireShape::WireShape(GL::Vec3 start, GL::Vec3 end, size_t segments, float drop, float thickness, GL::Color color) :
	m_start(start),
	m_end(end),
	m_segments(segments),
	m_drop(drop),
	m_thickness(thickness),
	m_color(color)
{
}

void gfx::shape::WireShape::generate(gfx::core::MeshBuffer<>& meshbuffer) const
{
	// triangle points
	const GL::Vec3 p1 = GL::Vec3(0.f, 0.f, 1.f) * m_thickness;
	const GL::Vec3 p2 = GL::Vec3(0.86602540378f, 0.f, -0.5f) * m_thickness;
	const GL::Vec3 p3 = GL::Vec3(-0.86602540378f, 0.f, -0.5f) * m_thickness;

	uint16_t base_index = (uint16_t)meshbuffer.vertices.size();

	// inserting vertices
	for (size_t i = 0; i <= m_segments; ++i)
	{
		float t = (float)i / m_segments;
		float tnext = (float)(i + 1) / m_segments;
		float tdrop = -(float)std::sin(common::PI * t) * m_drop;

		GL::Vec3 pdrop(0.f, tdrop, 0.f);
		GL::Vec3 p = common::lerp(m_start, m_end, t) + pdrop;
		GL::Vec3 pnext = common::lerp(m_start, m_end, tnext) + pdrop;

		GL::Vec3 direction = (pnext - p).Normal();
		float pitch = acos(direction.Y);
		float yaw = atan2(direction.Z, direction.X);

		GL::Mat4 mat;
		mat.Translate(p);
		mat.RotateX(pitch);
		mat.RotateY(yaw);

		gfx::core::Vertex v1{ mat * p1, GL::Vec3(), m_color };
		gfx::core::Vertex v2{ mat * p2, GL::Vec3(), m_color };
		gfx::core::Vertex v3{ mat * p3, GL::Vec3(), m_color };

		v1.normal = v1.position.Normal();
		v2.normal = v2.position.Normal();
		v3.normal = v3.position.Normal();

		meshbuffer.vertices.push_back(v1);
		meshbuffer.vertices.push_back(v2);
		meshbuffer.vertices.push_back(v3);
	}

	// indexing
#pragma warning(push)
#pragma warning(disable: 4267) // possible loss of data
	meshbuffer.indices.push_back(base_index + 0);
	meshbuffer.indices.push_back(base_index + 2);
	meshbuffer.indices.push_back(base_index + 1);

	for (size_t i = 0; i < m_segments; ++i)
	{
		// side 1
		meshbuffer.indices.push_back(base_index + 0 + (i * 3));
		meshbuffer.indices.push_back(base_index + 1 + (i * 3));
		meshbuffer.indices.push_back(base_index + 4 + (i * 3));
		meshbuffer.indices.push_back(base_index + 0 + (i * 3));
		meshbuffer.indices.push_back(base_index + 4 + (i * 3));
		meshbuffer.indices.push_back(base_index + 3 + (i * 3));

		// side 2
		meshbuffer.indices.push_back(base_index + 1 + (i * 3));
		meshbuffer.indices.push_back(base_index + 2 + (i * 3));
		meshbuffer.indices.push_back(base_index + 5 + (i * 3));
		meshbuffer.indices.push_back(base_index + 1 + (i * 3));
		meshbuffer.indices.push_back(base_index + 5 + (i * 3));
		meshbuffer.indices.push_back(base_index + 4 + (i * 3));

		// side 3
		meshbuffer.indices.push_back(base_index + 2 + (i * 3));
		meshbuffer.indices.push_back(base_index + 0 + (i * 3));
		meshbuffer.indices.push_back(base_index + 3 + (i * 3));
		meshbuffer.indices.push_back(base_index + 2 + (i * 3));
		meshbuffer.indices.push_back(base_index + 3 + (i * 3));
		meshbuffer.indices.push_back(base_index + 5 + (i * 3));
	}

	meshbuffer.indices.push_back(base_index + 0 + (m_segments * 3));
	meshbuffer.indices.push_back(base_index + 1 + (m_segments * 3));
	meshbuffer.indices.push_back(base_index + 2 + (m_segments * 3));
#pragma warning(pop)
}
