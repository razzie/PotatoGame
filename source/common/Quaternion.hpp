 /*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <cmath>
#include <GL/Math/Vec3.hpp>
#include <GL/Math/Mat4.hpp>

namespace common
{
	struct Quaternion
	{
		float x = 0.f;
		float y = 0.f;
		float z = 0.f;
		float w = 1.f;

		Quaternion& fromAngleAxis(float angle, const GL::Vec3& axis)
		{
			const float half_angle = 0.5f * angle;
			const float r = sinf(half_angle);
			w = cosf(half_angle);
			x = r * axis.X;
			y = r * axis.Y;
			z = r * axis.Z;
			return *this;
		}

		void getMatrix(GL::Mat4 &dest, const GL::Vec3& center) const
		{
			dest.m[0] = 1.0f - 2.0f * y * y - 2.0f * z * z;
			dest.m[1] = 2.0f * x * y + 2.0f * z * w;
			dest.m[2] = 2.0f * x * z - 2.0f * y * w;
			dest.m[3] = 0.0f;

			dest.m[4] = 2.0f * x * y - 2.0f * z * w;
			dest.m[5] = 1.0f - 2.0f * x * x - 2.0f * z * z;
			dest.m[6] = 2.0f * z * y + 2.0f * x * w;
			dest.m[7] = 0.0f;

			dest.m[8] = 2.0f * x * z + 2.0f * y * w;
			dest.m[9] = 2.0f * z * y - 2.0f * x * w;
			dest.m[10] = 1.0f - 2.0f * x * x - 2.0f * y * y;
			dest.m[11] = 0.0f;

			dest.m[12] = center.X;
			dest.m[13] = center.Y;
			dest.m[14] = center.Z;
			dest.m[15] = 1.f;
		}
	};

	inline void rotateVectorAroundAxis(GL::Vec3& vec, const GL::Vec3& axis, float radians)
	{
		Quaternion q;
		GL::Mat4 m;
		q.fromAngleAxis(radians, axis);
		q.getMatrix(m, GL::Vec3(0, 0, 0));
		vec = m * vec;
	}
}
