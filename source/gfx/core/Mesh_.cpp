/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "gfx/core/Mesh.hpp"

gfx::core::Mesh::Mesh() :
	m_num_indices(0),
	m_orig_num_indices(0),
	m_shader_binder(nullptr)
{
}

//gfx::core::Mesh::Mesh(const Mesh& other) :
//	m_vertices(other.m_vertices),
//	m_indices(other.m_indices),
//	m_vertex_array(other.m_vertex_array),
//	m_num_indices(other.m_num_indices),
//	m_orig_num_indices(other.m_orig_num_indices),
//	m_index_type(other.m_index_type),
//	m_shader_binder(other.m_shader_binder)
//{
//}

gfx::core::Mesh::Mesh(Mesh&& other) :
	m_vertices(std::move(other.m_vertices)),
	m_indices(std::move(other.m_indices)),
	m_vertex_array(std::move(other.m_vertex_array)),
	m_num_indices(other.m_num_indices),
	m_orig_num_indices(other.m_orig_num_indices),
	m_index_type(other.m_index_type),
	m_shader_binder(other.m_shader_binder)
{
}

gfx::core::Mesh& gfx::core::Mesh::operator=(Mesh&& other)
{
	m_vertices = std::move(other.m_vertices);
	m_indices = std::move(other.m_indices);
	m_vertex_array = std::move(other.m_vertex_array);
	m_num_indices = other.m_num_indices;
	m_orig_num_indices = other.m_orig_num_indices;
	m_index_type = other.m_index_type;
	m_shader_binder = other.m_shader_binder;
	return *this;
}

void gfx::core::Mesh::bindShader(GL::Program& program)
{
	if (m_shader_binder)
		m_shader_binder(*this, program);
}

void gfx::core::Mesh::render(GL::Context& gl) const
{
	gl.DrawElements(m_vertex_array, GL::Primitive::Triangles, 0, m_num_indices, m_index_type);
}

void gfx::core::Mesh::setCompleteness(float t)
{
	unsigned num_faces = m_orig_num_indices / 3;
	unsigned show_faces = common::lerp(0u, num_faces, t);
	m_num_indices = show_faces * 3;
}

gfx::core::Mesh::operator bool() const
{
	return (m_shader_binder != nullptr);
}
