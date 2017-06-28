/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <cstdint>
#include <vector>
#include <GL/Math/Vec3.hpp>
#include <GL/Util/Color.hpp>
#include <raz/memory.hpp>
#include "gfx/core/Mesh.hpp"
#include "gfx/shape/PlatformShape.hpp"

namespace gfx
{
namespace shape
{
	typedef std::vector<PlatformShape, raz::Allocator<PlatformShape>> Platforms;

	class PlatformRingShape
	{
	public:
		PlatformRingShape(unsigned radius, unsigned complexity);
		void generate(uint64_t seed, Platforms& platforms) const;
		void generate(const Platforms& platforms, gfx::core::MeshBuffer<>& meshbuffer) const;

	private:
		unsigned m_radius;
		unsigned m_complexity;
	};
}
}
