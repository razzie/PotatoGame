/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include "gfx/model/Model.hpp"

namespace gfx
{
namespace model
{
	class PlatformModel : public Model<>
	{
	public:
		PlatformModel(uint64_t seed, float size);
	};
}
}
