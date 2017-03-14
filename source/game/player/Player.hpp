/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#pragma warning(disable: 4307) // integral constant overflow

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
		event::ServerEventQueue& getServerEventQueue();
		event::EntityEventQueue& getEntityEventQueue();

	private:
		Type m_type;
		event::ServerEventQueue m_server_event_queue;
		event::EntityEventQueue m_entity_event_queue;
	};
}
}
