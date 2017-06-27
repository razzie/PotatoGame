/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "gfx/shape/SpikeShape.hpp"

gfx::shape::SpikeShape::SpikeShape(GL::Vec3 position, float scale) :
	m_position(position),
	m_scale(scale)
{
}

void gfx::shape::SpikeShape::generate(gfx::core::MeshBuffer<>& meshbuffer) const
{
	const GL::Color color(224, 224, 224);
	uint16_t base_index = (uint16_t)meshbuffer.vertices.size();

	gfx::core::Vertex top{ m_position + GL::Vec3(0.f, 4.f * m_scale, 0.f), GL::Vec3(), color };
	gfx::core::Vertex bottom1{ m_position + GL::Vec3(m_scale, 0.f, m_scale), GL::Vec3(), GL::Color() };
	gfx::core::Vertex bottom2{ m_position + GL::Vec3(m_scale, 0.f, -m_scale), GL::Vec3(), GL::Color() };
	gfx::core::Vertex bottom3{ m_position + GL::Vec3(-m_scale, 0.f, -m_scale), GL::Vec3(), GL::Color() };
	gfx::core::Vertex bottom4{ m_position + GL::Vec3(-m_scale, 0.f, m_scale), GL::Vec3(), GL::Color() };

	meshbuffer.vertices.push_back(top);
	meshbuffer.vertices.push_back(bottom1);
	meshbuffer.vertices.push_back(bottom2);
	meshbuffer.vertices.push_back(bottom3);
	meshbuffer.vertices.push_back(bottom4);

	uint16_t top_index = base_index;
	uint16_t bottom1_index = base_index + 1;
	uint16_t bottom2_index = base_index + 2;
	uint16_t bottom3_index = base_index + 3;
	uint16_t bottom4_index = base_index + 4;

	meshbuffer.indices.push_back(top_index);
	meshbuffer.indices.push_back(bottom1_index);
	meshbuffer.indices.push_back(bottom2_index);

	meshbuffer.indices.push_back(top_index);
	meshbuffer.indices.push_back(bottom2_index);
	meshbuffer.indices.push_back(bottom3_index);

	meshbuffer.indices.push_back(top_index);
	meshbuffer.indices.push_back(bottom3_index);
	meshbuffer.indices.push_back(bottom4_index);

	meshbuffer.indices.push_back(top_index);
	meshbuffer.indices.push_back(bottom4_index);
	meshbuffer.indices.push_back(bottom1_index);

	meshbuffer.indices.push_back(bottom1_index);
	meshbuffer.indices.push_back(bottom3_index);
	meshbuffer.indices.push_back(bottom2_index);
	meshbuffer.indices.push_back(bottom1_index);
	meshbuffer.indices.push_back(bottom4_index);
	meshbuffer.indices.push_back(bottom3_index);
}
