/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

namespace common
{
	inline float lerp(float a, float b, float t)
	{
		return (1.f - t) * a + t * b;
	}
}
