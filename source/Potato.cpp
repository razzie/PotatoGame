/*
 * Copyright (C) G�bor G�rzs�ny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <Windows.h>
#include "Potato.hpp"
#include "Demo.hpp"

using namespace raz::literal;

static raz::MemoryPool<100_MB> render_thread_memory;

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

	//superviseThread( m_game_thread.start(std::ref(*this), nullptr) );
	superviseThread( m_render_thread.start(std::ref(*this), &render_thread_memory) );

	raz::Thread<Demo> demo_thread;
	superviseThread( demo_thread.start(std::ref(*this)) );

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

void Potato::superviseThread(std::future<void> future)
{
	auto supervisor = [](Potato* potato, std::shared_future<void> future) -> void
	{
		try
		{
			future.get();
		}
		catch (std::future_error&)
		{
		}
		catch (std::exception& e)
		{
			potato->exit(-1, e.what());
			return;
		}

		//potato->exit(0, nullptr);
	};

	std::thread t(supervisor, this, std::move(future));
	t.detach();
}
