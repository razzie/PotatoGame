/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <GL/Math/Vec3.hpp>

namespace common
{
	inline bool equals(const float a, const float b, const float tolerance = 0.000001f)
	{
		return (a + tolerance >= b) && (a - tolerance <= b);
	}

	inline bool equals(const GL::Vec3 a, const GL::Vec3 b, const float tolerance = 0.000001f)
	{
		return equals(a.X, b.X, tolerance) && equals(a.Y, b.Y, tolerance) && equals(a.Z, b.Z, tolerance);
	}
}
