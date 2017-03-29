/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
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
	class SphereShape
	{
	public:
		SphereShape(GL::Vec3 center, float radius, unsigned detail, GL::Color color);
		void generate(gfx::core::MeshBuffer<>& meshbuffer) const;

	private:
		GL::Vec3 m_center;
		float m_radius;
		unsigned m_detail;
		GL::Color m_color;

		void insertRingPoints(gfx::core::MeshBuffer<>& meshbuffer, float a) const;
		void insertFirstRing(gfx::core::MeshBuffer<>& meshbuffer, float a) const;
		void insertRing(gfx::core::MeshBuffer<>& meshbuffer, float a) const;
		void insertLastRing(gfx::core::MeshBuffer<>& meshbuffer) const;
	};
}
}
