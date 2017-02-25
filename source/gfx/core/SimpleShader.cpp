/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "gfx/core/SimpleShader.hpp"

gfx::core::SimpleShader::SimpleShader()
{
	GL::Shader vert(GL::ShaderType::Vertex, GLSL(
		in vec3 position;
		in vec4 color;
		out vec4 frag_color;
		uniform mat4 screen_mat;
		void main() {
			frag_color = vec4(color.r / 255.0, color.g / 255.0, color.b / 255.0, color.a / 255.0);
			gl_Position = screen_mat * vec4(position, 1.0);
		}
	));
	GL::Shader frag(GL::ShaderType::Fragment, GLSL(
		in vec4 frag_color;
		out vec4 out_color;
		void main() {
			out_color = frag_color;
		}
	));
	m_program = GL::Program(vert, frag);
}

const GL::Program& gfx::core::SimpleShader::getProgram() const
{
	return m_program;
}
