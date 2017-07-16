/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <GL/Math/Vec4.hpp>
#include <GL/GL/Context.hpp>
#include "gfx/model/Horizon.hpp"

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

static const char* vert = GLSL(
uniform mat4 wvp_mat;
in vec4 position;
out vec4 frag_position;
void main()
{
	frag_position = position;
	gl_Position = wvp_mat * position;
}
);

static const char* frag = GLSL(
in vec4 frag_position;
out vec3 out_color;
out vec3 out_normal;
out vec3 out_position;
void main()
{
	out_color = vec3(1.0, 1.0, 1.0);
	out_normal = vec3(0.0, 1.0, 0.0);
	out_position = frag_position.xyz / frag_position.w;
}
);


gfx::model::Horizon::Horizon() :
	m_vertices(vertices, sizeof(vertices), GL::BufferUsage::StaticCopy),
	m_indices(indices, sizeof(indices), GL::BufferUsage::StaticCopy),
	m_shader(GL::Shader(GL::ShaderType::Vertex, vert), GL::Shader(GL::ShaderType::Fragment, frag))
{
	m_vertex_array.BindAttribute(m_shader.GetAttribute("position"), m_vertices, GL::Type::Float, 4, sizeof(float) * 4, 0);
	m_vertex_array.BindElements(m_indices);
}

void gfx::model::Horizon::render(GL::Context& gl, const GL::Mat4& wvp)
{
	gl.UseProgram(m_shader);
	m_shader.SetUniform("wvp_mat", wvp);
	gl.DrawElements(m_vertex_array, GL::Primitive::Triangles, 0, 12, GL::Type::UnsignedShort);
}
