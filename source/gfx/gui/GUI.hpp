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
#include "resource/ArchiveReader.hpp"
#include "gfx/gui/RocketFileInterface.hpp"
#include "gfx/gui/RocketSystemInterface.hpp"
#include "gfx/gui/RocketRenderInterface.hpp"
#include "gfx/gui/MousePointer.hpp"

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
		GL::Context& getContext();
		raz::IMemoryPool* getMemoryPool();
		GL::Program& getShader();
		resource::ArchiveReader& getArchive();
		bool feed(const GL::Event& ev);
		void update();
		void render();
		virtual void ProcessEvent(Rocket::Core::Event& ev);

	private:
		RenderThread& m_render_thread;
		GL::Program m_gui_shader;
		resource::ArchiveReader m_archive;
		Rocket::Core::Context* m_context;
		RocketFileInterface m_file_if;
		RocketSystemInterface m_system_if;
		RocketRenderInterface m_render_if;
		MousePointer m_mouse;
		bool m_mouse_event_consumed;

		int getKeyModifiers() const;
	};
}
}
