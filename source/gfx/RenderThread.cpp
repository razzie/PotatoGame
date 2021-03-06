/*
 * Copyright (C) G�bor G�rzs�ny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "Potato.hpp"
#include "gfx/RenderThread.hpp"

gfx::RenderThread::RenderThread(Potato& potato, raz::IMemoryPool* memory) :
	m_potato(potato),
	m_window(potato.getSettings().screen_width, potato.getSettings().screen_height, "Potato", potato.getSettings().fullscreen ? GL::WindowStyle::Fullscreen : GL::WindowStyle::Base | GL::WindowStyle::Close),
	m_gl(m_window.GetContext(32, 0, 0, 0)),
	m_memory(memory),
	m_shader_loader(memory),
	m_scene(*this),
	m_gui(*this)
{
	ShowCursor(FALSE);

	glClearDepth(1.0);
	m_gl.ClearColor(GL::Color(255, 255, 255));
	m_gl.Enable(GL::Capability::CullFace);

	glDepthRange(0.0, 1.0);
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

float gfx::RenderThread::getAspectRatio() const
{
	GL::Window& window = const_cast<GL::Window&>(m_window);
	return ((float)window.GetWidth() / (float)window.GetHeight());
}

float gfx::RenderThread::getRenderDistance() const
{
	return m_potato.getSettings().render_distance;
}

raz::IMemoryPool* gfx::RenderThread::getMemoryPool()
{
	return m_memory;
}

const common::InputHelper& gfx::RenderThread::getInputHelper() const
{
	return m_input;
}

resource::ShaderLoader& gfx::RenderThread::getShaderLoader()
{
	return m_shader_loader;
}

gfx::scene::Scene& gfx::RenderThread::getScene()
{
	return m_scene;
}

gfx::gui::GUI& gfx::RenderThread::getGUI()
{
	return m_gui;
}

void gfx::RenderThread::operator()()
{
	if (m_window.IsOpen())
	{
		GL::Event ev;
		while (m_window.GetEvent(ev))
		{
			m_input.feed(ev);

			if (ev.Type == GL::Event::KeyUp && ev.Key.Code == GL::Key::Escape)
			{
				m_window.Close();
				m_potato.exit(0);
				return;
			}

			if (m_gui.feed(ev))
				continue;
			else if (m_scene.feed(ev))
				continue;
		}

		m_gui.update();

		m_scene.render();
		m_gui.render();

		m_window.Present();
	}
	else
	{
		m_potato.exit(0);
	}
}

void gfx::RenderThread::operator()(std::exception& e)
{
	m_potato.exit(-1, e.what());
}

void gfx::RenderThread::operator()(game::event::AddHubEvent ev)
{
	auto& data = ev.get<0>();
	m_scene.addHub(data.id, data.seed, data.size, data.position);
}

void gfx::RenderThread::operator()(game::event::AddTransportEvent ev)
{
	auto& data = ev.get<0>();
	m_scene.addTransport(data.id, data.position1.hub_id, data.position1.platform_id, data.position2.hub_id, data.position2.platform_id);
}

void gfx::RenderThread::operator()(game::event::AddChargeEvent ev)
{
	auto& data = ev.get<0>();
	m_scene.addCharge(data.id, data.position.hub_id, data.position.platform_id);
}

void gfx::RenderThread::operator()(game::event::AddResourceEvent ev)
{
	auto& data = ev.get<0>();
	m_scene.addResource(data.id, data.value, data.position.hub_id, data.position.platform_id);
}

void gfx::RenderThread::operator()(game::event::AddTraceEvent ev)
{
	auto& data = ev.get<0>();
	m_scene.addTrace(data.id, data.color, data.position.hub_id, data.position.platform_id);
}

void gfx::RenderThread::operator()(game::event::AddSpawnEvent ev)
{
	auto& data = ev.get<0>();
	m_scene.addSpawn(data.id, data.color, data.position.hub_id, data.position.platform_id);
}

void gfx::RenderThread::operator()(game::event::AddPortalEvent ev)
{
	auto& data = ev.get<0>();
	m_scene.addPortal(data.id, data.position.hub_id, data.position.platform_id);
}

void gfx::RenderThread::operator()(game::event::AddTrapEvent ev)
{
	auto& data = ev.get<0>();
	m_scene.addTrap(data.id, data.color, data.position.hub_id, data.position.platform_id);
}

void gfx::RenderThread::operator()(game::event::AddCreatureEvent ev)
{
	auto& data = ev.get<0>();
	m_scene.addCreature(data.id, data.seed, data.color, data.position.hub_id, data.position.platform_id);
}

void gfx::RenderThread::operator()(game::event::RemoveChargeEvent ev)
{
	auto& data = ev.get<0>();
	m_scene.removeCharge(data.id);
}

void gfx::RenderThread::operator()(game::event::RemoveResourceEvent ev)
{
	auto& data = ev.get<0>();
	m_scene.removeResource(data.id);
}

void gfx::RenderThread::operator()(game::event::RemoveTraceEvent ev)
{
	auto& data = ev.get<0>();
	m_scene.removeTrace(data.id);
}

void gfx::RenderThread::operator()(game::event::RemoveTrapEvent ev)
{
	auto& data = ev.get<0>();
	m_scene.removeTrap(data.id);
}

void gfx::RenderThread::operator()(game::event::RemoveCreatureEvent ev)
{
	auto& data = ev.get<0>();
	m_scene.removeCreature(data.id);
}

void gfx::RenderThread::operator()(game::event::ChangeHubColorEvent ev)
{
	auto& data = ev.get<0>();
	m_scene.changeHubColor(data.id, data.color);
}

void gfx::RenderThread::operator()(game::event::ChangeSpawnColorEvent ev)
{
	auto& data = ev.get<0>();
	m_scene.changeSpawnColor(data.id, data.color);
}

void gfx::RenderThread::operator()(game::event::ChangeCreatureColorEvent ev)
{
	auto& data = ev.get<0>();
	m_scene.changeCreatureColor(data.id, data.color);
}

void gfx::RenderThread::operator()(game::event::MoveCreatureEvent ev)
{
	auto& data = ev.get<0>();
	m_scene.moveCreature(data.id, data.position.hub_id, data.position.platform_id);
}
