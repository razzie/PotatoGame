/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <vector>
#include <raz/memory.hpp>
#include "common/lerp.hpp"

namespace common
{
	template<class T, class Allocator>
	T bezier(const std::vector<T, Allocator>& control_points, float t)
	{
		if (control_points.empty())
			return {};

		std::vector<T, Allocator> temp(control_points);
		
		for (size_t count = temp.size(); count > 1; --count)
		{
			for (size_t i = 0; i < count - 1; ++i)
			{
				temp[i] = lerp(temp[i], temp[i + 1], t);
			}
		}

		return temp.front();
	}
}
