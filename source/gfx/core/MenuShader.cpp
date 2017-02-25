/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "gfx/core/MenuShader.hpp"

gfx::core::MenuShader::MenuShader()
{
	GL::Shader vert(GL::ShaderType::Vertex, GLSL(
		in vec2 position;
		in vec4 color;
		in vec2 tcoords;
		out vec4 frag_color;
		out vec2 frag_tcoords;
		uniform mat4 transform;
		void main() {
			frag_color = vec4(color.r / 255.0, color.g / 255.0, color.b / 255.0, color.a / 255.0);
			frag_tcoords = tcoords;
			gl_Position = transform * vec4(position, 0.0, 1.0);
		}
		));
		GL::Shader frag(GL::ShaderType::Fragment, GLSL(
			in vec4 frag_color;
			in vec2 frag_tcoords;
			out vec4 out_color;
			uniform sampler2D texture;
			uniform int use_texture;
			void main() {
				if (bool(use_texture))
					out_color = texture2D(texture, frag_tcoords) * frag_color;
				else
					out_color = frag_color;
			}
	));
	m_program = GL::Program(vert, frag);
}

const GL::Program& gfx::core::MenuShader::getProgram() const
{
	return m_program;
}
