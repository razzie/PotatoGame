/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <GL/Math/Vec3.hpp>
#include <GL/Util/Color.hpp>
#include "ui/core/Mesh.hpp"

namespace ui
{
namespace scene
{
namespace model
{
namespace gen
{
	class Wire
	{
	public:
		Wire(GL::Vec3 start, GL::Vec3 end, size_t segments, float drop, float thickness = 0.125, GL::Color color = {});
		void generate(ui::core::MeshBuffer<>& meshbuffer) const;

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
}
}
