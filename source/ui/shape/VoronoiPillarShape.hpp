/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <GL/Math/Vec3.hpp>
#include <GL/Util/Color.hpp>
#include <raz/random.hpp>
#include "ui/core/Mesh.hpp"

namespace ui
{
namespace shape
{
	class VoronoiPillarShape
	{
	public:
		VoronoiPillarShape(float radius, unsigned complexity);
		void generate(raz::Random& random, ui::core::MeshBuffer<>& meshbuffer) const;

	private:
		float m_radius;
		unsigned m_complexity;
	};
}
}
