/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <GL/Platform.hpp>
#include <GL/Window/Event.hpp>
#include "game/player/Player.hpp"

namespace gfx
{
	class RenderThread;
}

namespace game
{
namespace player
{
	class HumanPlayer : public Player
	{
	public:
		HumanPlayer(gfx::RenderThread& render_thread);
		~HumanPlayer();
		bool feed(const GL::Event& ev);
		void update();

	private:
		gfx::RenderThread& m_render_thread;
	};
}
}
