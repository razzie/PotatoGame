/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <cmath>
#include <GL/Math/Vec3.hpp>

namespace common
{
	inline float lerp(float a, float b, float t)
	{
		return (1.f - t) * a + t * b;
	}

	inline GL::Vec3 lerp(GL::Vec3 a, GL::Vec3 b, float t)
	{
		return GL::Vec3(lerp(a.X, b.X, t), lerp(a.Y, b.Y, t), lerp(a.Z, b.Z, t));
	}

	inline GL::Vec3 interpolate(GL::Vec3 a_pos, GL::Vec3 b_pos, float a_val, float b_val)
	{
		if (std::abs(a_val) < 0.00001)
			return a_pos;
		else if (std::abs(b_val) < 0.00001)
			return b_pos;
		else if (std::abs(a_val - b_val) < 0.00001)
			return a_pos;

		GL::Vec3 p;
		float d = -a_val / (b_val - a_val);
		return GL::Vec3(
			(b_pos.X + ((a_pos.X - b_pos.X) * d)),
			(b_pos.Y + ((a_pos.Y - b_pos.Y) * d)),
			(b_pos.Z + ((a_pos.Z - b_pos.Z) * d))
			);
	}
}
