/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <cstdint>
#include <GL/Math/Vec3.hpp>
#include <raz/event.hpp>

namespace ui
{
namespace event
{
	using namespace raz::literal;

	struct HubCreateParams
	{
		uint32_t hub_id;
		GL::Vec3 position;
	};

	typedef raz::Event<"HubCreate"_event, HubCreateParams> HubCreate;
}
}
