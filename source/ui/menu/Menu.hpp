/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <GL/Window/Window.hpp>
#include <GL/Window/Event.hpp>
#include <GL/GL/Context.hpp>
#include "ui/menu/RocketFileInterface.hpp"
#include "ui/menu/RocketSystemInterface.hpp"
#include "ui/menu/RocketRenderInterface.hpp"

namespace ui
{
namespace menu
{
	class Menu
	{
	public:
		Menu(GL::Window& window, GL::Context& gl);
		~Menu();
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
