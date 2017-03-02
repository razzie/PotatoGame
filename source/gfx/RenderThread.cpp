/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "Potato.hpp"
#include "gfx/RenderThread.hpp"

gfx::RenderThread::RenderThread(Potato& potato, unsigned width, unsigned height, bool fullscreen, raz::IMemoryPool* memory) :
	m_potato(potato),
	m_window(width, height, "OpenGL Window", fullscreen ? GL::WindowStyle::Fullscreen : GL::WindowStyle::Base | GL::WindowStyle::Close),
	m_gl(m_window.GetContext(32, 24, 8, 4)),
	m_memory(memory),
	m_shader_table(memory),
	m_gui(*this),
	m_scene(*this),
	m_player(*this)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_gl.Enable(GL::Capability::DepthTest);
	m_gl.Enable(GL::Capability::CullFace);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

gfx::RenderThread::~RenderThread()
{
}

GL::Window& gfx::RenderThread::getWindow()
{
	return m_window;
}

GL::Context& gfx::RenderThread::getContext()
{
	return m_gl;
}

float gfx::RenderThread::getAspectRatio()
{
	return ((float)m_window.GetWidth() / (float)m_window.GetHeight());
}

raz::IMemoryPool* gfx::RenderThread::getMemoryPool()
{
	return m_memory;
}

const common::InputHelper& gfx::RenderThread::getInputHelper() const
{
	return m_input;
}

gfx::core::ShaderTable& gfx::RenderThread::getShaderTable()
{
	return m_shader_table;
}

gfx::gui::GUI& gfx::RenderThread::getGUI()
{
	return m_gui;
}

gfx::scene::Scene& gfx::RenderThread::getScene()
{
	return m_scene;
}

game::player::HumanPlayer& gfx::RenderThread::getPlayer()
{
	return m_player;
}

int gfx::RenderThread::run()
{
	GL::Event ev;

	while (m_window.IsOpen())
	{
		while (m_window.GetEvent(ev))
		{
			m_input.feed(ev);
			
			//if (ev.Type == GL::Event::KeyUp && ev.Key.Code == GL::Key::Escape)
			//{
			//	m_window.Close();
			//	return 0;
			//}

			if (m_gui.feed(ev))
				continue;
			else if (m_player.feed(ev))
				continue;
			else if (m_scene.feed(ev))
				continue;
		}

		m_gl.Clear(GL::Buffer::Depth | GL::Buffer::Color);
		m_gl.ClearColor(GL::Color(255, 255, 255));

		m_scene.render();
		m_gui.render();

		m_window.Present();
	}


	return 0;
}
