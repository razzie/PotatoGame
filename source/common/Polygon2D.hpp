/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <cmath>
#include <vector>
#include <raz/memory.hpp>
#include "common/Point2D.hpp"
#include "common/Line2D.hpp"
#include "common/Triangle2D.hpp"
#include "common/BoundingBox2D.hpp"

namespace common
{
	constexpr double PI = 3.14159265358979323846;

	template<class T>
	struct Polygon2D
	{
		struct IntersectionData
		{
			size_t edge_n;
			Point2D<T> point;
		};

		std::vector<Point2D<T>, raz::Allocator<Point2D<T>>> points;

		void initNgon(T radius, unsigned edges, float angle_deg, Point2D<T> position)
		{
			float angle_rad = static_cast<float>((angle_deg * PI) / 180.f);
			float angle_step = static_cast<float>(PI * 2 / edges);

			for (unsigned i = 0; i < edges; ++i)
			{
				float x = std::sin(angle_rad) * radius;
				float y = -std::cos(angle_rad) * radius;
				points.push_back(Point2D<T>{ (T)x + position.x, (T)y + position.y });
				angle_rad += angle_step;
			}
		}

		T getArea() const
		{
			T area = 0;

			for (size_t i = 0, len = points.size(); i < len; ++i)
			{
				auto edge = getEdge(i);
				area += (edge.start.x + edge.end.x) * (edge.start.y - edge.end.y);
			}

			return (area / -2);
		}

		Line2D<T> getEdge(size_t n) const
		{
			return{ points[n], points[(n + 1) % points.size()] };
		}

		Point2D<T> getCenter() const
		{
			Point2D<T> center = { (T)0, (T)0 };

			for (auto& p : points)
			{
				center.x += p.x;
				center.y += p.y;
			}

			center.x /= points.size();
			center.y /= points.size();

			return center;
		}

		BoundingBox2D<T> getBoundingBox() const
		{
			BoundingBox2D<T> bbox;

			for (auto p : points)
				bbox.update(p);

			return bbox;
		}

		bool isCW() const
		{
			return getArea() > (T)0;
		}

		bool isCCW() const
		{
			return getArea() < (T)0;
		}

		bool contains_fast(const Point2D<T>& point) const // only works for convex polygons!
		{
			for (size_t i = 0, len = points.size(); i != len; ++i)
			{
				Line2D<T> edge = { points[i], points[(i + 1) % len] };
				if (!edge.isRight(point))
					return false;
			}
			return true;
		}

		bool contains(const Point2D<T>& point) const
		{
			std::vector<Point2D<T>, raz::Allocator<Point2D<T>> intersections(points.get_allocator());

			BoundingBox2D<T> bbox = getBoundingBox();
			Line2D<T> test_line { { bbox.min_x, point.y },{ bbox.max_x, point.y } };

			for (size_t i = 0, len = points.size(); i < len; ++i)
			{
				Point2D<T> intersection;
				if (getEdge(i).insersects(test_line, &intersection))
					intersections.push_back(intersection);
			}

			if (intersections.size() % 2)
				return false;

			std::sort(intersections.begin(), intersections.end(),
				[](const Point2D<T>& p1, const Point2D<T>& p2) -> bool { return p1.x < p2.x; });

			for (size_t i = 0, len = intersections.size(); i < len; ++i)
			{
				if (point.x < intersections[i].x)
				{
					if (i % 2)
						return true;
					else
						return false;
				}
			}

			return false;
		}

		template<class Allocator>
		void getIntersections(const Line2D<float>& line, std::vector<IntersectionData, Allocator>& out) const
		{
			// getting intersection points
			for (size_t i = 0, len = points.size(); i < len; ++i)
			{
				Line2D<T> edge = getEdge(i);
				Point2D<T> intersection;

				if (edge.insersects(line, &intersection))
					out.push_back({ i, intersection });
			}

			if (out.size() < 2)
				return;

			// sorting points
			std::sort(out.begin(), out.end(),
				[line](const IntersectionData& p1, const IntersectionData& p2) -> bool
				{
					return p1.point.getDistanceFromSq(line.start) < p2.point.getDistanceFromSq(line.start);
				});
		}

		void intersect(const Polygon2D<T>& convex, Polygon2D<T>& out) const
		{
			std::vector<IntersectionData, raz::Allocator<IntersectionData>> intersections(points.get_allocator());
			int first_ingoing_intersection = -1;
			int last_outgoing_intersection = -1;
			bool inside = contains(convex.points.front());

			for (size_t i = 0, len = convex.points.size(); i < len; ++i)
			{
				Line2D<T> line = convex.getEdge(i);

				intersections.clear();
				getIntersections(line, intersections);

				if (inside)
					out.points.push_back(line.start);

				for (auto& intersection : intersections)
				{
					if (inside) // we are going out, let's save the currently intersected edge
					{
						last_outgoing_intersection = intersection.edge_n;
					}
					else // when going back in, let's check if we left out some edges
					{
						if (first_ingoing_intersection == -1)
						{
							first_ingoing_intersection = intersection.edge_n;
						}

						if (last_outgoing_intersection != -1)
						{
							for (size_t j = last_outgoing_intersection;
							j != intersection.edge_n;
								j = ((j + 1) % points.size()))
							{
								out.points.push_back(getEdge(j).end);
							}
						}
					}

					inside = !inside;

					out.points.push_back(intersection.point);
				}
			}

			if (first_ingoing_intersection != -1 && !inside)
			{
				for (size_t j = last_outgoing_intersection;
					j != first_ingoing_intersection;
					j = ((j + 1) % points.size()))
				{
					out.points.push_back(getEdge(j).end);
				}
			}
		}

		template<class IndexType, class Allocator>
		bool triangulate(std::vector<IndexType, Allocator>& indices, IndexType base_index = 0) const
		{
			auto snips = [this](int u, int v, int w, int n, const int *V) -> bool
			{
				Triangle2D<float> triangle = { points[V[u]], points[V[v]], points[V[w]] };

				for (int p = 0; p < n; ++p)
				{
					if ((p == u) || (p == v) || (p == w)) continue;

					if (triangle.contains(points[V[p]]))
						return false;
				}

				return true;
			};

			/* allocate and initialize list of Vertices in polygon */

			const int n = points.size();
			if (n < 3) return false;

			raz::Allocator<int> allocator = points.get_allocator();
			int *V = allocator.allocate(n);

			/* we want a counter-clockwise polygon in V */

			if (0.0f < getArea())
				for (int v = 0; v<n; v++) V[v] = v;
			else
				for (int v = 0; v<n; v++) V[v] = (n - 1) - v;

			int nv = n;

			/*  remove nv-2 Vertices, creating 1 triangle every time */
			int count = 2 * nv;   /* error detection */

			for (int m = 0, v = nv - 1; nv>2;)
			{
				/* if we loop, it is probably a non-simple polygon */
				if (0 >= (count--))
				{
					//** Triangulate: ERROR - probable bad polygon!
					return false;
				}

				/* three consecutive vertices in current polygon, <u,v,w> */
				int u = v; if (nv <= u) u = 0;     /* previous */
				v = u + 1; if (nv <= v) v = 0;     /* new v    */
				int w = v + 1; if (nv <= w) w = 0;     /* next     */

				if (snips(u, v, w, nv, V))
				{
					int a, b, c, s, t;

					/* true names of the vertices */
					a = V[u]; b = V[v]; c = V[w];

					/* output Triangle */
					indices.push_back(c + base_index);
					indices.push_back(b + base_index);
					indices.push_back(a + base_index);

					m++;

					/* remove v from remaining polygon */
					for (s = v, t = v + 1; t<nv; s++, t++) V[s] = V[t]; nv--;

					/* reset error detection counter */
					count = 2 * nv;
				}
			}

			allocator.deallocate(V, n);

			return true;
		}
	};
}
