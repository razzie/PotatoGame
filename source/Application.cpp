/*
 * Copyright (C) G�bor G�rzs�ny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <raz/timer.hpp>
#include "Application.hpp"
#include "ui/menu/Menu.hpp"
#include "ui/scene/Scene.hpp"

Application::Application(int argc, char** argv) :
	m_window(1024, 768, "OpenGL Window", GL::WindowStyle::Close),
	m_gl(m_window.GetContext(32, 24, 8, 4))
{
	m_gl.Enable(GL::Capability::DepthTest);
	m_gl.Enable(GL::Capability::CullFace);

	m_gl.Clear(GL::Buffer::Depth | GL::Buffer::Color);
	m_gl.ClearColor(GL::Color(255, 255, 255));
	m_window.Present();

	//GL::Event ev;
	//while (m_window.GetEvent(ev));

	m_gl.Clear(GL::Buffer::Depth | GL::Buffer::Color);
	m_gl.ClearColor(GL::Color(255, 255, 255));
	m_window.Present();
}

Application::~Application()
{
}

int Application::run()
{
	ui::menu::Menu menu(m_window, m_gl);
	ui::scene::Scene m_scene(m_gl);

	GL::Event ev;
	raz::Timer timer;
	bool mouse_down = false;
	int last_mouse_x;
	int last_mouse_y;

	m_scene.getCamera().setPosition({ -8, 8, -8 });

	while (m_window.IsOpen())
	{
		while (m_window.GetEvent(ev))
		{
			if (ev.Type == GL::Event::KeyUp && ev.Key.Code == GL::Key::Escape)
			{
				m_window.Close();
			}
			else if (ev.Type == GL::Event::KeyDown)
			{
				float speed = 5.0f;

				switch (ev.Key.Code)
				{
				case GL::Key::W:
					m_scene.getCamera().move(speed, 0.f);
					break;
				case GL::Key::S:
					m_scene.getCamera().move(-speed, 0.f);
					break;
				case GL::Key::A:
					m_scene.getCamera().move(0.f, -speed);
					break;
				case GL::Key::D:
					m_scene.getCamera().move(0.f, speed);
					break;
				}
			}
			else if (ev.Type == GL::Event::MouseDown)
			{
				mouse_down = true;
			}
			else if (ev.Type == GL::Event::MouseUp)
			{
				mouse_down = false;
			}
			else if (ev.Type == GL::Event::MouseMove)
			{
				if (mouse_down)
				{
					int delta_x = ev.Mouse.X - last_mouse_x;
					int delta_y = ev.Mouse.Y - last_mouse_y;
					m_scene.getCamera().rotate((float)-delta_x, (float)delta_y);
				}

				last_mouse_x = ev.Mouse.X;
				last_mouse_y = ev.Mouse.Y;
			}
			else if (ev.Type == GL::Event::MouseWheel)
			{
				m_scene.getCamera().zoom(ev.Mouse.Delta > 0 ? 0.8f : -1.2f);
			}
		}

		m_gl.Clear(GL::Buffer::Depth | GL::Buffer::Color);
		m_gl.ClearColor(GL::Color(255, 255, 255));

		m_scene.render();
		menu.render();

		m_window.Present();
	}

	return 0;
}
