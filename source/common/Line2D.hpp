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
	struct Line2D
	{
		Point2D<T> start;
		Point2D<T> end;

		T getLengthSq() const
		{
			return start.getDistanceFromSq(end);
		}

		float getLength() const
		{
			return start.getDistanceFrom(end);
		}

		Point2D<T> lerp(float t) const
		{
			return lerp(start, end, t);
		}

		bool isRight(const Point2D<T>& point) const
		{
			Point2D<T> direction{ end.x - start.x, end.y - start.y };
			T v = (direction.y * (point.x - start.x)) + (direction.x * (start.y - point.y));
			return (v <= 0);
		}

		bool insersects(const Line2D<T>& line, Point2D<T>* intersection = nullptr, bool segment_only = true) const
		{
			const float commonDenominator =
				(float)(line.end.y - line.start.y)*(end.x - start.x) - (line.end.x - line.start.x)*(end.y - start.y);

			const float numeratorA =
				(float)(line.end.x - line.start.x)*(start.y - line.start.y) - (line.end.y - line.start.y)*(start.x - line.start.x);

			const float numeratorB =
				(float)(end.x - start.x)*(start.y - line.start.y) - (end.y - start.y)*(start.x - line.start.x);

			//if (equals(commonDenominator, 0.f))
			if (commonDenominator > -0.000001f && commonDenominator < 0.000001f)
				return false; // parallel or coincident (let's just not handle the latter now)

			const float uA = numeratorA / commonDenominator;
			if (segment_only && (uA < 0.f || uA > 1.f))
				return false; // Outside the line segment

			const float uB = numeratorB / commonDenominator;
			if (segment_only && (uB < 0.f || uB > 1.f))
				return false; // Outside the line segment

			if (intersection)
			{
				// Calculate the intersection point.
				intersection->x = (T)(start.x + uA * (end.x - start.x));
				intersection->y = (T)(start.y + uA * (end.y - start.y));
			}

			return true;
		}
	};
}
