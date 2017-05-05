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

	struct PlayerAcceptedData
	{

	};

	struct PlayerRejectedData
	{

	};

	struct PlayerUpdateData
	{

	};

	typedef raz::Event<"PlayerAccepted"_event, PlayerAcceptedData> PlayerAcceptedEvent;
	typedef raz::Event<"PlayerRejectedEvent"_event, PlayerRejectedData> PlayerRejectedEvent;
	typedef raz::Event<"PlayerUpdate"_event, PlayerUpdateData> PlayerUpdateEvent;
}
}
