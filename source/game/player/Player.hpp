/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#pragma warning(disable: 4307) // integral constant overflow

#include "game/event/entityevents.hpp"

namespace game
{
namespace player
{
	class Player
	{
	public:
		event::EntityEventQueue& getEntityEventQueue();

	private:
		event::EntityEventQueue m_entity_event_queue;
	};
}
}
