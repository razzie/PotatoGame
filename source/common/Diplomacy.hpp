/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <cstdint>

namespace common
{
	enum Diplomacy : uint32_t
	{
		NEUTRAL = 1 << 0,
		OWN     = 1 << 1,
		ALLY    = 1 << 2,
		ENEMY   = 1 << 3
	};
}
