/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <raz/event.hpp>

namespace game
{
namespace event
{
	using namespace raz::literal;

	typedef raz::Event<"Tick"_event> TickEvent;

	typedef raz::EventQueueSystem<TickEvent> GameEventQueue;
}
}
