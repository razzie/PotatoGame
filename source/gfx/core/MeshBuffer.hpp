/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <cstdint>
#include <vector>
#include <GL/Math/Vec3.hpp>
#include <GL/Math/Mat4.hpp>
#include <raz/memory.hpp>
#include "gfx/core/Vertex.hpp"

namespace gfx
{
namespace core
{
	template<class VertexType = Vertex, class IndexType = uint16_t>
	struct MeshBuffer
	{
		std::vector<VertexType, raz::Allocator<VertexType>> vertices;
		std::vector<IndexType, raz::Allocator<IndexType>> indices;

		MeshBuffer(raz::IMemoryPool* memory = nullptr) :
			vertices(memory),
			indices(memory)
		{
		}

		MeshBuffer(MeshBuffer&& other) :
			vertices(std::move(other.vertices)),
			indices(std::move(other.indices))
		{
		}

		GL::Vec3* getVector(VertexType* vertex, const VertexAttribute* attrib)
		{
			if (attrib->type != GL::Type::Float || attrib->count != 3)
				return nullptr;

			char* vertex_mem = reinterpret_cast<char*>(vertex);
			return reinterpret_cast<GL::Vec3*>(vertex_mem + attrib->offset);
		}

		GL::Vec3* getVector(VertexType* vertex, const char* attrib_name)
		{
			const gx::VertexAttribute* attrib = getVertexAttributeByName<VertexType>(attrib_name);
			if (attrib == nullptr)
				return nullptr;

			return getVector(vertex, attrib);
		}

		bool transform(const GL::Mat4& matrix, const VertexAttribute* attrib)
		{
			for (auto& vertex : vertices)
			{
				GL::Vec3* v = getVector(&vertex, attrib);
				if (!v)
					return false;

				*v = matrix * (*v);
			}

			return true;
		}

		bool transform(const GL::Mat4& matrix, const char* attrib_name)
		{
			const gx::VertexAttribute* attrib = getVertexAttributeByName<VertexType>(attrib_name);
			if (attrib == nullptr)
				return nullptr;

			return transform(matrix, attrib);
		}

		bool recalculateNormals(const VertexAttribute* position_attrib, const VertexAttribute* normal_attrib)
		{
			if (indices.size() % 3)
				return false;

			for (size_t i = 0, max_i = vertices.size(); i < max_i; ++i)
			{
				int count = 0;
				GL::Vec3 normal;

				for (size_t j = 0, max_j = indices.size(); j < max_j; j += 3)
				{
					if (indices[j] == i || indices[j + 1] == i || indices[j + 2] == i)
					{
						GL::Vec3* a = getVector(&vertices[indices[j]], position_attrib);
						GL::Vec3* b = getVector(&vertices[indices[j + 1]], position_attrib);
						GL::Vec3* c = getVector(&vertices[indices[j + 2]], position_attrib);

						if (!a || !b || !c)
							return false;

						GL::Vec3 u = *b - *a;
						GL::Vec3 v = *c - *a;
						normal += u.Cross(v);
						++count;
					}
				}

				if (count)
				{
					GL::Vec3* normal_ptr = getVector(&vertices[i], normal_attrib);
					if (!normal_ptr)
						return false;

					*normal_ptr = normal.Normal();
				}
			}

			return true;
		}

		bool recalculateNormals(const char* position_name = "position", const char* normal_name = "normal")
		{
			const VertexAttribute* position_attrib = getVertexAttributeByName<VertexType>(position_name);
			const VertexAttribute* normal_attrib = getVertexAttributeByName<VertexType>(normal_name);
			if (!position_attrib || !normal_attrib)
				return false;

			return recalculateNormals(position_attrib, normal_attrib);
		}
	};
}
}
