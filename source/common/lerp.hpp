/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

namespace common
{
	template<class T>
	T lerp(T a, T b, float t)
	{
		return static_cast<T>((1.f - t) * a + t * b);
	}
}
