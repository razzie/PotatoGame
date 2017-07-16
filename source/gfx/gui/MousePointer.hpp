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
#include "common/InputHelper.hpp"

namespace gfx
{
namespace gui
{
	class GUI;

	class MousePointer
	{
	public:
		MousePointer(GUI& gui, GL::Window& window);
		void update(const common::InputHelper& input);
		void render();

	private:
		GL::Context& m_gl;
		GL::Texture m_texture;
		GL::Program m_shader;
		GL::VertexBuffer m_vbo;
		GL::VertexArray m_vao;
		GL::Mat4 m_proj;
		GL::Mat4 m_transform;
		GL::Vec2 m_mouse_back_pos;
		float m_size;
	};
}
}
