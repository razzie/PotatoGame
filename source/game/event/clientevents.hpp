/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <GL/Util/Color.hpp>
#include <raz/event.hpp>

namespace game
{
namespace event
{
	using namespace raz::literal;

	struct PlayerConnectionData
	{

	};

	struct PlayerDisconnectionData
	{

	};

	struct PlayerSkillUseData
	{

	};

	typedef raz::Event<"PlayerConnection"_event, PlayerConnectionData> PlayerConnectionEvent;
	typedef raz::Event<"PlayerDisconnection"_event, PlayerDisconnectionData> PlayerDisconnectionEvent;
	typedef raz::Event<"PlayerSkillUse"_event, PlayerSkillUseData> PlayerSkillUseEvent;

	typedef raz::EventQueueSystem<
		PlayerConnectionEvent,
		PlayerDisconnectionEvent,
		PlayerSkillUseEvent
	> ClientEventQueue;
}
}
