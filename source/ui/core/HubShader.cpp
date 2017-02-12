/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "ui/core/HubShader.hpp"

ui::core::HubShader::HubShader()
{
	GL::Shader vert(GL::ShaderType::Vertex, GLSL(
		in vec3 position;
		in vec3 normal;
		in vec4 color;
		out vec3 Position;
		out vec3 Normal;
		out vec4 Color;
		uniform mat4 world_mat;
		uniform mat4 normal_mat;
		uniform mat4 screen_mat;
		void main() {
			Position = (world_mat * vec4(position, 1.0)).xyz;
			Normal = (normal_mat * vec4(normal, 1.0)).xyz;
			Color = vec4(color.r / 255.0, color.g / 255.0, color.b / 255.0, color.a / 255.0);
			gl_Position = screen_mat * vec4(position, 1.0);
		}
	));
	GL::Shader frag(GL::ShaderType::Fragment, GLSL(
		in vec3 Position;
		in vec3 Normal;
		in vec4 Color;
		uniform vec3 light_source;
		out vec4 outColor;
		void main() {
			float diffuse = clamp(dot(normalize(Normal), normalize(light_source - Position)), 0.0, 1.0) * 0.2 + 0.8;
			outColor = Color * diffuse;
		}
	));
	m_program = GL::Program(vert, frag);
}

const GL::Program& ui::core::HubShader::getProgram() const
{
	return m_program;
}
