/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include "common/Point2D.hpp"

namespace common
{
	template<class T>
	struct Circle2D
	{
		Point2D<T> center;
		T radius;

		bool contains(const Point2D<T>& point)
		{
			return (point.getDistanceFromSq(center) <= (radius * radius));
		}
	};
}
