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
	Potato(int argc, char** argv);
	~Potato();
	game::GameThread& getGameThread();
	gfx::RenderThread& getRenderThread();
	int run();

private:
	game::GameThread m_game;
	gfx::RenderThread m_render;
};
