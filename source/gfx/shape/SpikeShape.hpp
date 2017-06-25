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
	class SpikeShape
	{
	public:
		SpikeShape(GL::Vec3 position, float scale);
		void generate(gfx::core::MeshBuffer<>& meshbuffer) const;

	private:
		GL::Vec3 m_position;
		float m_scale;
	};
}
}
