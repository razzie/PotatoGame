/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <cmath>
#include <GL/Math/Vec3.hpp>
#include <GL/Util/Color.hpp>
#include "common/lerp.hpp"

namespace common
{
	inline GL::Vec3 lerp(GL::Vec3 a, GL::Vec3 b, float t)
	{
		return GL::Vec3(
			lerp(a.X, b.X, t),
			lerp(a.Y, b.Y, t),
			lerp(a.Z, b.Z, t)
		);
	}

	inline GL::Color lerp(GL::Color a, GL::Color b, float t)
	{
		return GL::Color(
			(GL::uchar)lerp(a.R, b.R, t),
			(GL::uchar)lerp(a.G, b.G, t),
			(GL::uchar)lerp(a.B, b.B, t),
			(GL::uchar)lerp(a.A, b.A, t)
		);
	}
}
