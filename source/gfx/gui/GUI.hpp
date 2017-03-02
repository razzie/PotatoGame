/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <GL/Platform.hpp>
#include <GL/GL/Program.hpp>
#include <GL/Window/Event.hpp>
#include <Rocket/Core/EventListener.h>
#include "gfx/gui/RocketFileInterface.hpp"
#include "gfx/gui/RocketSystemInterface.hpp"
#include "gfx/gui/RocketRenderInterface.hpp"

namespace gfx
{
class RenderThread;

namespace gui
{
	class GUI : public Rocket::Core::EventListener
	{
	public:
		GUI(RenderThread& render_thread);
		~GUI();
		bool feed(const GL::Event& ev);
		void render();
		virtual void ProcessEvent(Rocket::Core::Event& ev);

	private:
		RenderThread& m_render_thread;
		GL::Program& m_gui_shader;
		Rocket::Core::Context* m_context;
		RocketFileInterface m_file_if;
		RocketSystemInterface m_system_if;
		RocketRenderInterface m_render_if;
		bool m_mouse_event_consumed;

		int getKeyModifiers() const;
	};
}
}
