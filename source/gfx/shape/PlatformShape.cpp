/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <cmath>
#include "common/PI.hpp"
#include "gfx/shape/PlatformShape.hpp"

static constexpr size_t MAX_EDGES = 8;

#pragma warning(push)
#pragma warning(disable: 4267) // possible loss of data
#pragma warning(disable: 4244)

GL::Vec3 gfx::shape::PlatformShape::getRandomPosition(raz::Random& random) const
{
	const double angle = random(-common::PI, common::PI);
	const float radius = std::round(random(0.f, size * 0.75f) * 4.f) / 4.f;
	float x = std::sin(angle) * radius;
	float z = -std::cos(angle) * radius;

	return (GL::Vec3(x, 0.f, z) + center);
}

void gfx::shape::PlatformShape::generate(gfx::core::MeshBuffer<>& meshbuffer) const
{
	raz::Random random(seed);

	GL::Vec3 edges[MAX_EDGES];
	size_t num_edges = random(5u, MAX_EDGES);
	uint8_t shade = (uint8_t)random(192u, 255u);
	GL::Color color(shade, shade, shade);

	const float angle_step = static_cast<float>(common::PI * 2 / num_edges);
	float angle_rad = 0.f;

	for (size_t i = 0; i < num_edges; ++i)
	{
		float x = std::sin(angle_rad) * (size + random(0.f, 0.25f));
		float z = -std::cos(angle_rad) * (size + random(0.f, 0.25f));

		edges[i] = GL::Vec3(x, 0.f, z);

		angle_rad += angle_step;
	}


	// adding platform surface
	uint16_t base_index = (uint16_t)meshbuffer.vertices.size();
	for (size_t i = 0; i < num_edges; ++i)
	{
		gfx::core::Vertex v{ edges[i] + center, GL::Vec3(0.f, 1.f, 0.f), color };
		meshbuffer.vertices.push_back(v);
	}
	for (size_t i = 1; i < num_edges - 1; ++i)
	{
		meshbuffer.indices.push_back(base_index);
		meshbuffer.indices.push_back(base_index + i + 1);
		meshbuffer.indices.push_back(base_index + i);
	}
	for (size_t i = 0; i < num_edges; ++i)
	{
		GL::Vec3 pos = edges[i] * 1.1f;
		pos.Y -= random(0.25f, 0.5f);
		gfx::core::Vertex v{ pos + center, GL::Vec3(0.f, 1.f, 0.f), color };
		meshbuffer.vertices.push_back(v);
	//}
	//for (size_t i = 0; i < num_edges; ++i)
	//{
		uint16_t top1 = base_index + i;
		uint16_t top2 = base_index + ((i + 1) % num_edges);
		uint16_t bottom1 = base_index + i + num_edges;
		uint16_t bottom2 = base_index + ((i + 1) % num_edges) + num_edges;

		meshbuffer.indices.push_back(top1);
		meshbuffer.indices.push_back(top2);
		meshbuffer.indices.push_back(bottom1);

		meshbuffer.indices.push_back(top2);
		meshbuffer.indices.push_back(bottom2);
		meshbuffer.indices.push_back(bottom1);
	}

	// adding platform body
	color = GL::Color(128, 128, 128);
	for (size_t level = 0, levels = random(3u, 4u); level < levels; ++level)
	{
		base_index = (uint16_t)meshbuffer.vertices.size() - num_edges;

		for (size_t i = 0; i < num_edges; ++i)
		{
			gfx::core::Vertex v{ edges[i] + center, GL::Vec3(0.f, 1.f, 0.f), color };
			meshbuffer.vertices.push_back(v);

			if (level > 0)
			{
				uint16_t top1 = base_index + i;
				uint16_t top2 = base_index + ((i + 1) % num_edges);
				uint16_t bottom1 = base_index + i + num_edges;
				uint16_t bottom2 = base_index + ((i + 1) % num_edges) + num_edges;

				meshbuffer.indices.push_back(top1);
				meshbuffer.indices.push_back(top2);
				meshbuffer.indices.push_back(bottom1);

				meshbuffer.indices.push_back(top2);
				meshbuffer.indices.push_back(bottom2);
				meshbuffer.indices.push_back(bottom1);

				edges[i] = edges[i] * random(0.5f, 0.75f);
				edges[i].Y -= random(0.75f, 0.9f);
			}
		}
	}
}

#pragma warning(pop)
