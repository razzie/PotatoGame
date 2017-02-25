/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <GL/Math/Vec3.hpp>
#include <GL/Util/Color.hpp>
#include <raz/random.hpp>
#include "gfx/core/Mesh.hpp"

namespace gfx
{
namespace shape
{
	class VoronoiPillarShape
	{
	public:
		VoronoiPillarShape(float radius, unsigned complexity);
		void generate(raz::Random& random, gfx::core::MeshBuffer<>& meshbuffer) const;

	private:
		float m_radius;
		unsigned m_complexity;
	};
}
}
