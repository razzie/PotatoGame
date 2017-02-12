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
	struct BoundingBox2D
	{
		T min_x = 1;
		T min_y = 1;
		T max_x = 0;
		T max_y = 0;

		void update(const Point2D<T>& point)
		{
			if (min_x > max_x) // first point
			{
				min_x = max_x = point.x;
				min_y = max_y = point.y;
			}
			else
			{
				if (point.x < min_x) min_x = point.x;
				else if (point.x > max_x) max_x = point.x;

				if (point.y < min_y) min_y = point.y;
				else if (point.y > max_y) max_y = point.y;
			}
		}

		T getWidth() const
		{
			return max_x - min_x;
		}

		T getHeight() const
		{
			return max_y - min_y;
		}

		Point2D<T> getUpperLeftCorner() const
		{
			return { min_x, min_y };
		}

		Point2D<T> getLowerRightCorner() const
		{
			return { max_x, max_y };
		}

		Point2D<T> getCenter() const
		{
			return { (min_x + max_x) / 2.f, (min_y + max_y) / 2.f };
		}
	};
}
