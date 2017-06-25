/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include "gfx/core/Mesh.hpp"

namespace gfx
{
namespace shape
{
	class SpawnShape
	{
	public:
		SpawnShape(GL::Vec3 position, float radius, float angle);
		void generate(gfx::core::MeshBuffer<>& meshbuffer) const;

	private:
		GL::Vec3 m_position;
		float m_radius;
		float m_angle;
	};
}
}
