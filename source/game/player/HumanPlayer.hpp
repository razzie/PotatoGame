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

		void handle(event::TickEvent& ev);

		void handle(event::AddHubEvent& ev);
		void handle(event::AddTransportEvent& ev);
		void handle(event::AddChargeEvent& ev);
		void handle(event::AddResourceEvent& ev);
		void handle(event::AddTraceEvent& ev);
		void handle(event::AddSpawnEvent& ev);
		void handle(event::AddPortalEvent& ev);
		void handle(event::AddTrapEvent& ev);
		void handle(event::AddCreatureEvent& ev);

		void handle(event::RemoveChargeEvent& ev);
		void handle(event::RemoveResourceEvent& ev);
		void handle(event::RemoveTraceEvent& ev);
		void handle(event::RemoveTrapEvent& ev);
		void handle(event::RemoveCreatureEvent& ev);

		void handle(event::ChangeHubColorEvent& ev);
		void handle(event::ChangeSpawnColorEvent& ev);
		void handle(event::ChangeCreatureColorEvent& ev);

		void handle(event::MoveCreatureEvent& ev);

	private:
		gfx::RenderThread& m_render_thread;
	};
}
}
