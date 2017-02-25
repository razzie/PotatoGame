/*
 * Copyright (C) G�bor G�rzs�ny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <GL/Math/Vec3.hpp>
#include <GL/Util/Color.hpp>
#include "gfx/core/Mesh.hpp"

namespace gfx
{
namespace shape
{
	class WireShape
	{
	public:
		WireShape(GL::Vec3 start, GL::Vec3 end, size_t segments, float drop, float thickness = 0.125, GL::Color color = {});
		void generate(gfx::core::MeshBuffer<>& meshbuffer) const;

	private:
		GL::Vec3 m_start;
		GL::Vec3 m_end;
		size_t m_segments;
		float m_drop;
		float m_thickness;
		GL::Color m_color;
	};
}
}
