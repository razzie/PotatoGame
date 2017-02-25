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
#include "common/Point2D.hpp"
#include "gfx/core/Mesh.hpp"

namespace gfx
{
namespace shape
{
	class CreatureShape
	{
	public:
		typedef std::vector<uint8_t, raz::Allocator<uint8_t>> Dimensions;
		typedef std::vector<common::Point2D<float>, raz::Allocator<common::Point2D<float>>> ControlPoints;

		CreatureShape(raz::Random& random, GL::Color color, raz::IMemoryPool* memory = nullptr);
		CreatureShape(const Dimensions& dimensions, unsigned edge_mode, GL::Color color);
		void generate(gfx::core::MeshBuffer<>& meshbuffer) const;

	private:
		ControlPoints m_control_points;
		unsigned m_edge_mode;
		GL::Color m_color;
	};
}
}
