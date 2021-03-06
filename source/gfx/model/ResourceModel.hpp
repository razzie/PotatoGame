/*
 * Copyright (C) G�bor G�rzs�ny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include "gfx/model/Model.hpp"

namespace gfx
{
namespace model
{
	class ResourceModel : public Model<>
	{
	public:
		ResourceModel(gfx::scene::Scene& scene, uint32_t id, uint32_t value, uint32_t hub_id, uint32_t platform_id);
	};
}
}
