/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <cmath>

namespace common
{
	template<class T>
	struct Point2D
	{
		T x;
		T y;

		T getDistanceFromSq(Point2D<T> p) const
		{
			return ((p.x - x) * (p.x - x)) + ((p.y - y) * (p.y - y));
		}

		auto getDistanceFrom(Point2D<T> p) const
		{
			return std::sqrt(getDistanceFromSq(p));
		}
	};

	template<class T>
	Point2D<T> lerp(Point2D<T> a, Point2D<T> b, float t)
	{
		Point2D<T> p;
		p.x = (1.f - t) * a.x + t * b.x;
		p.y = (1.f - t) * a.y + t * b.y;
		return p;
	}
}
