/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <raz/random.hpp>
#include "common/PI.hpp"
#include "common/GLlerp.hpp"
#include "gfx/shape/WireShape.hpp"
#include "gfx/shape/PlatformRingShape.hpp"

static void insertWires(const gfx::shape::Platforms& platforms, raz::Random& random, unsigned radius, unsigned complexity, gfx::core::MeshBuffer<>& meshbuffer)
{
	const unsigned max_platform = platforms.size() - 1;	
	const float min_distance = 0.5f * radius;
	const float max_distance = 1.5f * radius;
	
	for (unsigned i = 0; i < complexity; ++i)
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
	
		p1.Y -= 0.25f;
		p2.Y -= 0.25f;
	
		gfx::shape::WireShape wire(p1, p2, 8, 0.25f * distance);
		wire.generate(meshbuffer);
	}
	
	for (unsigned i = 0; i < complexity; ++i)
	{
		auto& platform = platforms[random(0u, max_platform)];
		GL::Vec3 p1 = platform.center;
		GL::Vec3 p2 { 0.f, random(0.f, 0.25f * radius), 0.f };
	
		p1.Y -= 0.75f;
	
		gfx::shape::WireShape wire(p1, p2, 8, 0.25f * radius, 0.125f, GL::Color(128, 128, 128));
		wire.generate(meshbuffer);
	}
}

gfx::shape::PlatformRingShape::PlatformRingShape(unsigned radius, unsigned complexity) :
	m_radius(radius),
	m_complexity(complexity)
{
}

void gfx::shape::PlatformRingShape::generate(uint64_t seed, Platforms& platforms) const
{
	raz::Random random(seed);
	float global_height = 0.75f * m_radius;
	const unsigned inner_platform_count = m_radius * 3;
	unsigned platform_count = inner_platform_count;
	float angle_step = static_cast<float>(common::PI * 2 / inner_platform_count);
	float angle_rad = 0.f;
	float starting_radius = (float)m_radius;
	float current_radius = 0.8f;
	
	auto randomize = [&random](GL::Vec3 v) -> GL::Vec3
	{
		float scale = random(0.99f, 1.01f);
		return GL::Vec3(v.X * scale, v.Y + random(-0.0625f, 0.0625f), v.Z * scale);
	};
	
	for (unsigned i = 0; i < 2; ++i)
	{
		for (unsigned j = 0; j < platform_count; ++j)
		{
			float x = std::sin(angle_rad) * starting_radius;
			float z = -std::cos(angle_rad) * starting_radius;
			float y = global_height + random(0.f, 0.5f);
	
			gfx::shape::PlatformShape platform;
			platform.center = randomize(GL::Vec3(x, y, z));
			platform.size = current_radius;
			platform.seed = random();
			platforms.push_back(platform);
	
			angle_rad += angle_step;
		}
	
		angle_step *= 0.5f;
		angle_rad = 0.5f * angle_step;
		platform_count *= 2;
		starting_radius += current_radius * 2;
		current_radius *= 0.6f;
		global_height -= 0.5f;
	}
}

void gfx::shape::PlatformRingShape::generate(const Platforms& platforms, gfx::core::MeshBuffer<>& meshbuffer) const
{
	if (platforms.empty())
		return;

	for (auto& platform : platforms)
		platform.generate(meshbuffer);

	raz::Random random(platforms[0].seed);
	insertWires(platforms, random, m_radius, m_complexity, meshbuffer);
}
