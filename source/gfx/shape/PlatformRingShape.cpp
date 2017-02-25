/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "common/PI.hpp"
#include "gfx/shape/WireShape.hpp"
#include "gfx/shape/PlatformRingShape.hpp"

static void createPlatforms(gfx::shape::PlatformRingShape::PlatformVector& platforms, raz::Random& random, unsigned radius)
{
	const unsigned inner_platform_count = radius * 3;
	unsigned platform_count = inner_platform_count;
	float angle_step = static_cast<float>(common::PI * 2 / inner_platform_count);
	float angle_rad = 0.f;
	float starting_radius = (float)radius;
	float current_radius = 1.5f;

	auto randomize = [&random](GL::Vec3 v) -> GL::Vec3
	{
		float scale = random(0.99f, 1.01f);
		return GL::Vec3(v.X * scale, v.Y + random(-0.0625f, 0.0625f), v.Z * scale);
	};

	auto tighten = [](gfx::shape::PlatformRingShape::Platform& platform)
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

	for (unsigned i = 0; i < 2; ++i)
	{
		for (unsigned j = 0; j < platform_count; ++j)
		{
			float x1 = std::sin(angle_rad);
			float z1 = -std::cos(angle_rad);
			float x2 = std::sin(angle_rad + angle_step);
			float z2 = -std::cos(angle_rad + angle_step);
			float height = random(0.f, 0.25f);

			gfx::shape::PlatformRingShape::Platform platform;
			platform.inner1 = randomize(GL::Vec3(x1 * starting_radius, -0.25f * i + height, z1 * starting_radius));
			platform.inner2 = randomize(GL::Vec3(x2 * starting_radius, -0.25f * i + height, z2 * starting_radius));
			platform.outer1 = randomize(GL::Vec3(x1 * (starting_radius + current_radius), -0.25f * i + height, z1 * (starting_radius + current_radius)));
			platform.outer2 = randomize(GL::Vec3(x2 * (starting_radius + current_radius), -0.25f * i + height, z2 * (starting_radius + current_radius)));
			platform.center = (platform.inner1 + platform.inner2 + platform.outer1 + platform.outer2) / 4.f;

			tighten(platform);
			platforms.push_back(platform);

			angle_rad += angle_step;
		}

		angle_step *= 0.5f;
		angle_rad = 0.5f * angle_step;
		platform_count *= 2;
		starting_radius += current_radius;
		current_radius *= 0.5f;
	}
}

static void insertPlatforms(const gfx::shape::PlatformRingShape::PlatformVector& platforms, raz::Random& random, gfx::core::MeshBuffer<>& meshbuffer)
{
	for (auto& platform : platforms)
	{
		GL::uchar color = random(224, 255);
		float height = random(1.f, 2.f);

		gfx::core::Vertex inner1{ platform.inner1, GL::Vec3(0.f, 1.f, 0.f), GL::Color(color, color, color) };
		gfx::core::Vertex inner2{ platform.inner2, GL::Vec3(0.f, 1.f, 0.f), GL::Color(color, color, color) };
		gfx::core::Vertex outer1{ platform.outer1, GL::Vec3(0.f, 1.f, 0.f), GL::Color(color, color, color) };
		gfx::core::Vertex outer2{ platform.outer2, GL::Vec3(0.f, 1.f, 0.f), GL::Color(color, color, color) };

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
		gfx::core::Vertex center{ platform.center, GL::Vec3(0.f, -1.f, 0.f), GL::Color() };
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

static void insertWires(const gfx::shape::PlatformRingShape::PlatformVector& platforms, raz::Random& random, unsigned radius, unsigned complexity, gfx::core::MeshBuffer<>& meshbuffer)
{
	const unsigned wires = complexity * 2;
	const unsigned max_platform = platforms.size() - 1;

	const float min_distance = 0.5f * radius;
	const float max_distance = 1.5f * radius;

	for (unsigned i = 0; i < wires; ++i)
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
		} while (distance < min_distance || distance > max_distance);

		p1.Y -= 0.75f;
		p2.Y -= 0.75f;

		gfx::shape::WireShape wire(p1, p2, 8, 0.25f * distance);
		wire.generate(meshbuffer);
	}
}

gfx::shape::PlatformRingShape::PlatformRingShape(unsigned radius, unsigned complexity) :
	m_radius(radius),
	m_complexity(complexity)
{
}

void gfx::shape::PlatformRingShape::generate(raz::Random& random, PlatformVector& platforms, gfx::core::MeshBuffer<>& meshbuffer) const
{
	createPlatforms(platforms, random, m_radius);
	insertPlatforms(platforms, random, meshbuffer);
	insertWires(platforms, random, m_radius, m_complexity, meshbuffer);
}
