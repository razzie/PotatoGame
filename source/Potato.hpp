/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include "game/GameThread.hpp"
#include "gfx/RenderThread.hpp"

class Potato
{
public:
	struct Settings
	{
		Settings(int argc, char** argv);

		unsigned screen_width = 1366;
		unsigned screen_height = 768;
		bool fullscreen = false;
	};

	Potato(int argc, char** argv);
	~Potato();
	Settings& getSettings();
	game::GameThread& getGameThread();
	gfx::RenderThread& getRenderThread();
	int run();

private:
	Settings m_settings;
	game::GameThread m_game;
	gfx::RenderThread m_render;
};
