/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "ui/core/MenuShader.hpp"

ui::core::MenuShader::MenuShader()
{
	GL::Shader vert(GL::ShaderType::Vertex, GLSL(
		in vec2 position;
		in vec4 color;
		in vec2 tcoords;
		out vec4 Color;
		out vec2 Tcoords;
		void main() {
			Color = vec4(color.r / 255.0, color.g / 255.0, color.b / 255.0, color.a / 255.0);
			gl_Position = vec4(position, 0.0, 1.0);
		}
		));
		GL::Shader frag(GL::ShaderType::Fragment, GLSL(
			in vec4 Color;
			in vec2 Tcoords;
			uniform sampler2D texture;
			void main() {
				gl_FragColor = texture2D(texture, Tcoords) * Color;
			}
	));
	m_program = GL::Program(vert, frag);
}

const GL::Program& ui::core::MenuShader::getProgram() const
{
	return m_program;
}
