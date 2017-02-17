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
		return GL::Vec3(lerp(a.X, b.X, t), lerp(a.Y, b.Y, t), lerp(a.Z, b.Z, t));
	}

	inline GL::Vec3 interpolate(GL::Vec3 a_pos, GL::Vec3 b_pos, float a_val, float b_val)
	{
		if (std::abs(a_val) < 0.00001)
			return a_pos;
		else if (std::abs(b_val) < 0.00001)
			return b_pos;
		else if (std::abs(a_val - b_val) < 0.00001)
			return a_pos;

		GL::Vec3 p;
		float d = -a_val / (b_val - a_val);
		return GL::Vec3(
			(b_pos.X + ((a_pos.X - b_pos.X) * d)),
			(b_pos.Y + ((a_pos.Y - b_pos.Y) * d)),
			(b_pos.Z + ((a_pos.Z - b_pos.Z) * d))
			);
	}

	struct GLVec3Serializer
	{
		GL::Vec3& vec;

		GLVec3Serializer(GL::Vec3& v) : vec(v)
		{
		}

		template<class Serializer>
		void operator()(Serializer& serializer)
		{
			serializer(vec.X)(vec.Y)(vec.Z);
		}
	};

	struct GLColorSerializer
	{
		GL::Color& color;

		GLColorSerializer(GL::Color& c) : color(c)
		{
		}

		template<class Serializer>
		void operator()(Serializer& serializer)
		{
			serializer(color.R)(color.G)(color.B)(color.A);
		}
	};
}
