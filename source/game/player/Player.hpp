/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#pragma warning(disable: 4307) // integral constant overflow

#include <raz/memory.hpp>
#include "game/event/serverevents.hpp"
#include "game/event/entityevents.hpp"

namespace game
{
namespace player
{
	class Player
	{
	public:
		enum Type
		{
			HUMAN,
			AI,
			NETWORK
		};

		Player(Type type, raz::IMemoryPool* memory = nullptr);
		virtual ~Player();
		Type getType() const;

		virtual void handle(event::PlayerAcceptedEvent&& ev) = 0;
		virtual void handle(event::PlayerRejectedEvent&& ev) = 0;
		virtual void handle(event::PlayerUpdateEvent&& ev) = 0;

		virtual void handle(event::AddHubEvent&& ev) = 0;
		virtual void handle(event::AddTransportEvent&& ev) = 0;
		virtual void handle(event::AddChargeEvent&& ev) = 0;
		virtual void handle(event::AddResourceEvent&& ev) = 0;
		virtual void handle(event::AddTraceEvent&& ev) = 0;
		virtual void handle(event::AddSpawnEvent&& ev) = 0;
		virtual void handle(event::AddPortalEvent&& ev) = 0;
		virtual void handle(event::AddTrapEvent&& ev) = 0;
		virtual void handle(event::AddCreatureEvent&& ev) = 0;
		virtual void handle(event::RemoveChargeEvent&& ev) = 0;
		virtual void handle(event::RemoveResourceEvent&& ev) = 0;
		virtual void handle(event::RemoveTraceEvent&& ev) = 0;
		virtual void handle(event::RemoveTrapEvent&& ev) = 0;
		virtual void handle(event::RemoveCreatureEvent&& ev) = 0;
		virtual void handle(event::ChangeHubColorEvent&& ev) = 0;
		virtual void handle(event::ChangeSpawnColorEvent&& ev) = 0;
		virtual void handle(event::ChangeCreatureColorEvent&& ev) = 0;
		virtual void handle(event::MoveCreatureEvent&& ev) = 0;

	private:
		Type m_type;
	};
}
}
