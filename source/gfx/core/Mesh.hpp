/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <GL/GL/Context.hpp>
#include <GL/GL/Program.hpp>
#include <GL/GL/VertexBuffer.hpp>
#include <GL/GL/VertexArray.hpp>
#include "common/lerp.hpp"
#include "gfx/core/MeshBuffer.hpp"

namespace gfx
{
namespace core
{
	class Mesh
	{
	public:
		Mesh();
		Mesh(Mesh&& other);
		Mesh& operator=(Mesh&& other);
		void bindShader(GL::Program& program);
		void render(GL::Context& gl) const;
		void setCompleteness(float t);
		operator bool() const;

		template<class VertexType, class IndexType>
		Mesh& operator=(const MeshBuffer<VertexType, IndexType>& meshbuffer)
		{
			m_vertices = GL::VertexBuffer(meshbuffer.vertices.data(), meshbuffer.vertices.size() * sizeof(VertexType), GL::BufferUsage::StaticCopy);
			m_indices = GL::VertexBuffer(meshbuffer.indices.data(), meshbuffer.indices.size() * sizeof(IndexType), GL::BufferUsage::StaticCopy);
			m_orig_num_indices = m_num_indices = meshbuffer.indices.size();
			m_index_type = (sizeof(IndexType) == 4) ? GL::Type::UnsignedInt : GL::Type::UnsignedShort;
			m_vertex_array.BindElements(m_indices);

			m_shader_binder = [](Mesh& mesh, GL::Program& program) -> void
			{
				for (int i = 0, count = VertexType::getVertexAttributeCount(); i < count; ++i)
				{
					const VertexAttribute* attrib = VertexType::getVertexAttribute(i);
					mesh.m_vertex_array.BindAttribute(program.GetAttribute(attrib->name), mesh.m_vertices, attrib->type, attrib->count, attrib->stride, attrib->offset);
				}
			};

			return *this;
		}

	private:
		typedef void(*ShaderBinderFunc)(Mesh&, GL::Program&);

		GL::VertexBuffer m_vertices;
		GL::VertexBuffer m_indices;
		GL::VertexArray m_vertex_array;
		unsigned m_num_indices;
		unsigned m_orig_num_indices;
		GL::Type::type_t m_index_type;
		ShaderBinderFunc m_shader_binder;
	};
}
}
