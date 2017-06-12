/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <Windows.h>
#include "Potato.hpp"
#include "Demo.hpp"

Potato::Settings::Settings(int argc, char** argv) :
	screen_width(1366),
	screen_height(768),
	fullscreen(false),
	render_distance(200.f)
{
}

Potato::Potato(int argc, char** argv) :
	m_settings(argc, argv)
{
}

Potato::~Potato()
{
}

const Potato::Settings& Potato::getSettings() const
{
	return m_settings;
}

raz::Thread<game::GameThread>& Potato::getGameThread()
{
	return m_game_thread;
}

raz::Thread<gfx::RenderThread>& Potato::getRenderThread()
{
	return m_render_thread;
}

int Potato::run()
{
	auto exit_code_future = m_exit_code.get_future();

	m_game_thread.start(std::ref(*this), nullptr);
	m_render_thread.start(std::ref(*this), nullptr);

	raz::Thread<Demo> demo_thread;
	demo_thread.start(std::ref(*this));

	int exit_code = exit_code_future.get();

	m_render_thread.stop();
	m_game_thread.stop();

	return exit_code;
}

void Potato::exit(int code, const char* msg)
{
	if (msg)
	{
		MessageBoxA(NULL, msg, "Exit message", MB_OK);
	}

	m_exit_code.set_value(code);
}
