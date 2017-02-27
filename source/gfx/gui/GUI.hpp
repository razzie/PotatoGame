/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <GL/Window/Window.hpp>
#include <GL/Window/Event.hpp>
#include <GL/GL/Context.hpp>
#include "gfx/core/ShaderTable.hpp"
#include "gfx/gui/RocketFileInterface.hpp"
#include "gfx/gui/RocketSystemInterface.hpp"
#include "gfx/gui/RocketRenderInterface.hpp"

namespace gfx
{
namespace gui
{
	class GUI
	{
	public:
		GUI(GL::Window& window, GL::Context& gl, gfx::core::ShaderTable& shader_table);
		~GUI();
		bool feed(GL::Event& ev);
		void render();

	private:
		GL::Window* m_window;
		GL::Context* m_gl;
		Rocket::Core::Context* m_context;
		RocketFileInterface m_file_if;
		RocketSystemInterface m_system_if;
		RocketRenderInterface m_render_if;
	};
}
}
