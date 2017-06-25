/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "gfx/shape/SpawnShape.hpp"

#define LIGHT(x, y, z) gfx::core::Vertex{GL::Vec3(x, y, z), GL::Vec3(), GL::Color(224, 224, 224)}
#define DARK(x, y, z) gfx::core::Vertex{GL::Vec3(x, y, z), GL::Vec3(), GL::Color(64, 64, 64)}

static gfx::core::Vertex vertices[] = {
	LIGHT(-0.25f, 0.05f, -0.25f),
	LIGHT( 0.25f, 0.05f, -0.25f),
	LIGHT( 0.25f, 0.05f,  0.25f),
	LIGHT(-0.25f, 0.05f,  0.25f),

	LIGHT(-0.25f, 0.0f, -1.0f),
	LIGHT( 0.25f, 0.0f, -1.0f),
	LIGHT( 1.0f,  0.0f, -0.25f),
	LIGHT( 1.0f,  0.0f,  0.25f),
	LIGHT( 0.25f, 0.0f,  1.0f),
	LIGHT(-0.25f, 0.0f,  1.0f),
	LIGHT(-1.0f,  0.0f,  0.25f),
	LIGHT(-1.0f,  0.0f, -0.25f),

	DARK(-0.25f, 0.05f, -0.25f),
	DARK(-0.25f, 0.0f,  -1.0f),
	DARK(-0.25f, 0.0f,  -0.25f),
	DARK(-1.0f,  0.0f,  -0.25f),

	DARK(0.25f, 0.05f, -0.25f),
	DARK(1.0f,  0.0f,  -0.25f),
	DARK(0.25f, 0.0f,  -0.25f),
	DARK(0.25f, 0.0f,  -1.0f),

	DARK(0.25f, 0.05f, 0.25f),
	DARK(0.25f, 0.0f,  1.0f),
	DARK(0.25f, 0.0f,  0.25f),
	DARK(1.0f,  0.0f,  0.25f),

	DARK(-0.25f, 0.05f, 0.25f),
	DARK(-1.0f,  0.0f,  0.25f),
	DARK(-0.25f, 0.0f,  0.25f),
	DARK(-0.25f, 0.0f,  1.0f),
};

#undef LIGHT
#undef DARK

static uint16_t indices[] = {
	1, 0, 3,
	1, 3, 2,

	5, 4, 0,
	5, 0, 1,
	6, 1, 2,
	6, 2, 7,
	2, 3, 9,
	2, 9, 8,
	0, 11, 10,
	0, 10, 3,

	12, 13, 14,
	12, 14, 15,
	16, 17, 18,
	16, 18, 19,
	20, 21, 22,
	20, 22, 23,
	24, 25, 26,
	24, 26, 27,
};

gfx::shape::SpawnShape::SpawnShape(GL::Vec3 position, float radius, float angle) :
	m_position(position),
	m_radius(radius),
	m_angle(angle)
{
}

void gfx::shape::SpawnShape::generate(gfx::core::MeshBuffer<>& meshbuffer) const
{
	const uint16_t base_index = (uint16_t)meshbuffer.vertices.size();

	GL::Mat4 mat;
	mat.Translate(m_position);
	mat.RotateY(m_angle);
	mat.Scale(GL::Vec3(m_radius, 1.f, m_radius));

	for (size_t i = 0; i < sizeof(vertices) / sizeof(gfx::core::Vertex); ++i)
	{
		gfx::core::Vertex v = vertices[i];
		v.position = mat * v.position;
		meshbuffer.vertices.push_back(v);
	}

	for (size_t i = 0; i < sizeof(indices) / sizeof(uint16_t); ++i)
	{
		uint16_t index = indices[i] + base_index;
		meshbuffer.indices.push_back(index);
	}
}
