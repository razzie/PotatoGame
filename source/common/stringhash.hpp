/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
*/

#pragma once

#include <cstdint>

namespace common
{
	static constexpr uint64_t stringhash(const char* str, const uint64_t h = 5381)
	{
		return (str[0] == 0) ? h : stringhash(&str[1], h * 33 + str[0]);
	}
}
