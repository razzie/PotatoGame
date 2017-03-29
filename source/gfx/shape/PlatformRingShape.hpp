/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <vector>
#include <GL/Math/Vec3.hpp>
#include <GL/Util/Color.hpp>
#include <raz/memory.hpp>
#include <raz/random.hpp>
#include "gfx/core/Mesh.hpp"

namespace gfx
{
namespace shape
{
	class PlatformRingShape
	{
	public:
		struct Platform
		{
			GL::Vec3 center;
			GL::Vec3 inner1;
			GL::Vec3 inner2;
			GL::Vec3 outer1;
			GL::Vec3 outer2;

			GL::Vec3 getPosition(float x, float y) const;
		};

		typedef std::vector<Platform, raz::Allocator<Platform>> PlatformVector;

		PlatformRingShape(unsigned radius, unsigned complexity);
		void generate(raz::Random& random, PlatformVector& platforms, gfx::core::MeshBuffer<>& meshbuffer) const;

	private:
		unsigned m_radius;
		unsigned m_complexity;
	};
}
}
