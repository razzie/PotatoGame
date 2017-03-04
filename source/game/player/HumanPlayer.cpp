/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "gfx/RenderThread.hpp"
#include "game/player/HumanPlayer.hpp"

game::player::HumanPlayer::HumanPlayer(gfx::RenderThread& render_thread) :
	m_render_thread(render_thread)
{
}

game::player::HumanPlayer::~HumanPlayer()
{
}

bool game::player::HumanPlayer::feed(const GL::Event& ev)
{
	return false;
}

void game::player::HumanPlayer::update()
{
}
