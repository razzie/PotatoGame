/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <GL/Window/Window.hpp>
#include <GL/GL/Context.hpp>
#include <raz/memory.hpp>
#include "common/InputHelper.hpp"
#include "gfx/core/ShaderTable.hpp"
#include "gfx/gui/GUI.hpp"
#include "gfx/scene/Scene.hpp"
#include "game/event/entityevents.hpp"

class Potato;

namespace gfx
{
	class RenderThread
	{
	public:
		RenderThread(Potato& potato, unsigned width, unsigned height, bool fullscreen, raz::IMemoryPool* memory = nullptr);
		~RenderThread();
		GL::Window& getWindow();
		GL::Context& getContext();
		float getAspectRatio();
		raz::IMemoryPool* getMemoryPool();
		const common::InputHelper& getInputHelper() const;
		gfx::core::ShaderTable& getShaderTable();
		gfx::gui::GUI& getGUI();
		gfx::scene::Scene& getScene();

		// raz::Thread compatibility:
		void operator()();
		void operator()(std::exception& e);
		void operator()(game::event::AddHubEvent ev);
		void operator()(game::event::AddTransportEvent ev);
		void operator()(game::event::AddChargeEvent ev);
		void operator()(game::event::AddResourceEvent ev);
		void operator()(game::event::AddTraceEvent ev);
		void operator()(game::event::AddSpawnEvent ev);
		void operator()(game::event::AddPortalEvent ev);
		void operator()(game::event::AddTrapEvent ev);
		void operator()(game::event::AddCreatureEvent ev);
		void operator()(game::event::RemoveChargeEvent ev);
		void operator()(game::event::RemoveResourceEvent ev);
		void operator()(game::event::RemoveTraceEvent ev);
		void operator()(game::event::RemoveTrapEvent ev);
		void operator()(game::event::RemoveCreatureEvent ev);
		void operator()(game::event::ChangeHubColorEvent ev);
		void operator()(game::event::ChangeSpawnColorEvent ev);
		void operator()(game::event::ChangeCreatureColorEvent ev);
		void operator()(game::event::MoveCreatureEvent ev);

	private:
		Potato& m_potato;
		GL::Window m_window;
		GL::Context& m_gl;
		raz::IMemoryPool* m_memory;
		common::InputHelper m_input;
		gfx::core::ShaderTable m_shader_table;
		gfx::gui::GUI m_gui;
		gfx::scene::Scene m_scene;
	};
}
