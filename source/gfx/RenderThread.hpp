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
#include "game/player/HumanPlayer.hpp"

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
		game::player::HumanPlayer& getPlayer();
		int run();

	private:
		Potato& m_potato;
		GL::Window m_window;
		GL::Context& m_gl;
		raz::IMemoryPool* m_memory;
		common::InputHelper m_input;
		gfx::core::ShaderTable m_shader_table;
		gfx::gui::GUI m_gui;
		gfx::scene::Scene m_scene;
		game::player::HumanPlayer m_player;
	};
}
