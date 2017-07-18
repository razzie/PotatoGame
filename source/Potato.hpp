/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <raz/thread.hpp>
#include "game/GameThread.hpp"
#include "gfx/RenderThread.hpp"

class Potato
{
public:
	struct Settings
	{
		Settings(int argc, char** argv);

		unsigned screen_width;
		unsigned screen_height;
		bool fullscreen;
		float render_distance;
	};

	Potato(int argc, char** argv);
	~Potato();
	const Settings& getSettings() const;
	raz::Thread<game::GameThread>& getGameThread();
	raz::Thread<gfx::RenderThread>& getRenderThread();
	int run();
	void exit(int code, const char* msg = nullptr);

private:
	Settings m_settings;
	std::promise<int> m_exit_code;
	raz::Thread<game::GameThread> m_game_thread;
	raz::Thread<gfx::RenderThread> m_render_thread;

	void superviseThread(std::future<void> future);
};
