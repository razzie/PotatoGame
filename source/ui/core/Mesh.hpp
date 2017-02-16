/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <cstdint>
#include <vector>
#include <GL/Math/Vec3.hpp>
#include <GL/GL/Context.hpp>
#include <GL/GL/Program.hpp>
#include <GL/GL/VertexBuffer.hpp>
#include <GL/GL/VertexArray.hpp>
#include <raz/memory.hpp>
#include "ui/core/Vertex.hpp"

namespace ui
{
namespace core
{
	struct Mesh
	{
		GL::Program program;
		GL::VertexBuffer vertices;
		GL::VertexBuffer indices;
		GL::VertexArray vertex_array;
		unsigned num_of_indices;
		GL::Type::type_t index_type;

		void render(GL::Context& gl, bool use_program = true) const
		{
			if (use_program)
				gl.UseProgram(program);

			gl.DrawElements(vertex_array, GL::Primitive::Triangles, 0, num_of_indices, index_type);
		}
	};

	template<class VertexType = Vertex, class IndexType = uint16_t>
	struct MeshBuffer
	{
		std::vector<VertexType, raz::Allocator<VertexType>> vertices;
		std::vector<IndexType, raz::Allocator<IndexType>> indices;

		MeshBuffer() = default;
		MeshBuffer(const MeshBuffer&) = default;

		explicit MeshBuffer(raz::IMemoryPool& memory) :
			vertices(memory),
			indices(memory)
		{
		}

		Mesh createMesh(GL::Program program) const
		{
			Mesh mesh;

			mesh.program = program;
			mesh.vertices = GL::VertexBuffer(vertices.data(), vertices.size() * sizeof(VertexType), GL::BufferUsage::StaticCopy);
			mesh.indices = GL::VertexBuffer(indices.data(), indices.size() * sizeof(IndexType), GL::BufferUsage::StaticCopy);
			mesh.num_of_indices = indices.size();
			mesh.index_type = (sizeof(IndexType) == 4) ? GL::Type::UnsignedInt : GL::Type::UnsignedShort;

			for (int i = 0, count = VertexType::getVertexAttributeCount(); i < count; ++i)
			{
				const VertexAttribute& attrib = VertexType::getVertexAttribute(i);
				mesh.vertex_array.BindAttribute(program.GetAttribute(attrib.name), mesh.vertices, attrib.type, attrib.count, attrib.stride, attrib.offset);
			}
			mesh.vertex_array.BindElements(mesh.indices);

			return mesh;
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
			const gx::VertexAttribute* attrib = VertexType::getVertexAttribute(attrib_name);
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
			const gx::VertexAttribute* attrib = VertexType::getVertexAttribute(attrib_name);
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
			const VertexAttribute* position_attrib = VertexType::getVertexAttribute(position_name);
			const VertexAttribute* normal_attrib = VertexType::getVertexAttribute(normal_name);
			if (!position_attrib || !normal_attrib)
				return false;

			return recalculateNormals(position_attrib, normal_attrib);
		}
	};
}
}
