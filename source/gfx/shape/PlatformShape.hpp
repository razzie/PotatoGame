/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <cstdint>
#include <GL/Math/Vec3.hpp>
#include <raz/random.hpp>
#include "gfx/core/Mesh.hpp"

namespace gfx
{
namespace shape
{
	struct PlatformShape
	{
		GL::Vec3 center;
		uint64_t seed;
		float size;

		GL::Vec3 getRandomPosition(raz::Random& random) const;
		void generate(gfx::core::MeshBuffer<>& meshbuffer) const;
	};
}
}
