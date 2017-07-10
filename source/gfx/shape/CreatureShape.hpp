/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <array>
#include <cstdint>
#include <GL/Math/Vec3.hpp>
#include <GL/Util/Color.hpp>
#include "common/Point2D.hpp"
#include "gfx/core/Mesh.hpp"

namespace gfx
{
namespace shape
{
	class CreatureShape
	{
	public:
		static constexpr size_t MAX_HEIGHT = 7;

		CreatureShape(uint64_t seed);
		void generate(gfx::core::MeshBuffer<>& meshbuffer) const;

	private:
		std::array<common::Point2D<float>, MAX_HEIGHT + 2> m_control_points;
		size_t m_control_points_count;
		uint8_t m_shade;
		unsigned m_edge_mode;
	};
}
}
