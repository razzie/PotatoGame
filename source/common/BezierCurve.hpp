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
	template<class T>
	class BezierCurve
	{
	public:
		BezierCurve() = default;

		BezierCurve(raz::IMemoryPool& memory) : m_points(memory)
		{
		}

		void addPoint(T p)
		{
			m_points.push_back(p);
		}

		void addPoints(
			typename std::vector<T, raz::Allocator<T>>::const_iterator begin,
			typename std::vector<T, raz::Allocator<T>>::const_iterator end)
		{
			m_points.insert(m_points.end(), begin, end);
		}

		T operator()(float t) const
		{
			if (m_points.empty())
				return {};
			else
				return get(m_points.begin(), m_points.end() - 1, t);
		}

	private:
		std::vector<T, raz::Allocator<T>> m_points;

		typedef typename std::vector<T, raz::Allocator<T>>::const_iterator Iterator;

		T get(Iterator begin, Iterator end, float t) const
		{
			//if (std::distance(begin, end) == 1)
			//{
			//	return lerp(*begin, *end, t);
			//}
			//else
			//{
			//	Iterator next = begin + 1;
			//	return lerp(lerp(*begin, *next, t), get(next, end, t), t);
			//}

			auto dist = std::distance(begin, end);
			switch (dist)
			{
			case 0:
				return m_points.front();

			case 1:
				return lerp(*begin, *end, t);

			case 2:
				return lerp(
					lerp(*begin, *(begin + 1), t),
					lerp(*(begin + 1), *end, t),
					t);

			default:
				{
					auto p1 = lerp(*begin, *(begin + 1), t);
					auto p2 = get(begin + 1, end - 1, t);
					auto p3 = lerp(*(end - 1), *end, t);

					auto p12 = lerp(p1, p2, t);
					auto p23 = lerp(p2, p3, t);

					return lerp(p12, p23, t);
				}
			}
		}
	};
}
