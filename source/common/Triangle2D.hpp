/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include "common/Point2D.hpp"
#include "common/Circle2D.hpp"

namespace common
{
	template<class T>
	struct Triangle2D
	{
		Point2D<T> point1;
		Point2D<T> point2;
		Point2D<T> point3;

		Point2D<T> getCenter() const
		{
			return { (point1.x + point2.x + point3.x) / (T)3, (point1.y + point2.y + point3.y) / (T)3 };
		}

		Circle2D<T> getCircumCircle() const
		{
			Circle2D<T> circle;

			T dot1 = (point1.x * point1.x) + (point1.y * point1.y);
			T dot2 = (point2.x * point2.x) + (point2.y * point2.y);
			T dot3 = (point3.x * point3.x) + (point3.y * point3.y);

			circle.center.x = (dot1 * (point3.y - point2.y) + dot2 * (point1.y - point3.y) + dot3 * (point2.y - point1.y))
				/ (point1.x * (point3.y - point2.y) + point2.x * (point1.y - point3.y) + point3.x * (point2.y - point1.y))
				/ 2.f;
			circle.center.y = (dot1 * (point3.x - point2.x) + dot2 * (point1.x - point3.x) + dot3 * (point2.x - point1.x))
				/ (point1.y * (point3.x - point2.x) + point2.y * (point1.x - point3.x) + point3.y * (point2.x - point1.x))
				/ 2.f;
			circle.radius = (T)sqrt(((point1.x - circum_x) * (point1.x - circum_x)) + ((point1.y - circum_y) * (point1.y - circum_y)));

			return circle;
		}

		bool contains(const Point2D<T>& point)
		{
			Line2D<T> edge1 = { point1, point2 };
			Line2D<T> edge2 = { point2, point3 };
			Line2D<T> edge3 = { point3, point1 };
			return (edge1.isRight(point) && edge2.isRight(point) && edge3.isRight(point));
		}

		bool contains(const Line2D<T>& line)
		{
			return (contains(line.start) && contains(line.end));
		}
	};
}
