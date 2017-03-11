/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <GL/Math/Vec4.hpp>
#include <GL/GL/Context.hpp>
#include "gfx/scene/Scene.hpp"
#include "gfx/scene/Horizon.hpp"

static const GL::Vec4 vertices[] = {
	GL::Vec4( 0.f, 0.f,  0.f, 1.f),
	GL::Vec4( 0.f, 0.f,  1.f, 0.f),
	GL::Vec4( 1.f, 0.f,  0.f, 0.f),
	GL::Vec4( 0.f, 0.f, -1.f, 0.f),
	GL::Vec4(-1.f, 0.f,  0.f, 0.f)
};

static const GL::ushort indices[] = {
	0, 1, 2,
	0, 2, 3,
	0, 3, 4,
	0, 4, 1
};


gfx::scene::Horizon::Horizon(GL::Program& shader) :
	m_vertices(vertices, sizeof(vertices), GL::BufferUsage::StaticCopy),
	m_indices(indices, sizeof(indices), GL::BufferUsage::StaticCopy),
	m_shader(shader)
{
	m_vertex_array.BindAttribute(shader.GetAttribute("position"), m_vertices, GL::Type::Float, 4, sizeof(float) * 4, 0);
	m_vertex_array.BindElements(m_indices);
}

void gfx::scene::Horizon::render(Scene& scene)
{
	GL::Context& gl = scene.getContext();
	gl.UseProgram(m_shader);

	m_shader.SetUniform("screen_mat", scene.getCameraMatrix());
	m_shader.SetUniform("light_source", scene.getCamera().getPosition());
	m_shader.SetUniform("time", scene.getElapsedTime());

	gl.DrawElements(m_vertex_array, GL::Primitive::Triangles, 0, 12, GL::Type::UnsignedShort);
}
