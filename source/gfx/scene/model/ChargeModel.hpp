/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include "gfx/scene/model/Model.hpp"

namespace gfx
{
namespace scene
{
namespace model
{
	class ChargeModel : public Model<>
	{
	public:
		ChargeModel(Scene& scene, uint32_t id, uint32_t hub_id, uint32_t platform_id);
	};
}
}
}
