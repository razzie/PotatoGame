/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "gfx/core/HubShader.hpp"

gfx::core::HubShader::HubShader()
{
	GL::Shader vert(GL::ShaderType::Vertex, GLSL(
		in vec3 position;
		in vec3 normal;
		in vec4 color;
		out vec3 frag_position;
		out vec3 frag_normal;
		out vec4 frag_color;
		uniform mat4 world_mat;
		uniform mat4 normal_mat;
		uniform mat4 screen_mat;
		void main() {
			frag_position = (world_mat * vec4(position, 1.0)).xyz;
			frag_normal = (normal_mat * vec4(normal, 1.0)).xyz;
			frag_color = vec4(color.r / 255.0, color.g / 255.0, color.b / 255.0, color.a / 255.0);
			gl_Position = screen_mat * vec4(position, 1.0);
		}
	));
	GL::Shader frag(GL::ShaderType::Fragment, GLSL(
		in vec3 frag_position;
		in vec3 frag_normal;
		in vec4 frag_color;
		out vec4 out_color;
		uniform vec3 light_source;
		void main() {
			float light_dot = dot(normalize(frag_normal), normalize(light_source - frag_position));
			float light = clamp(light_dot, 0.0, 1.0) * 0.2 + 0.8;
			out_color = vec4(frag_color.rgb * light, 1.0);
		}
	));
	m_program = GL::Program(vert, frag);
}

const GL::Program& gfx::core::HubShader::getProgram() const
{
	return m_program;
}
