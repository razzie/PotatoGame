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
	class ChargeModel : public Model<>
	{
	public:
		ChargeModel(gfx::scene::Scene& scene, uint32_t id, uint32_t hub_id, uint32_t platform_id);
	};
}
}
