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
	class TransportModel : public Model
	{
	public:
		TransportModel(Scene& scene, uint32_t id, uint32_t hub1_id, uint32_t hub1_platform_id, uint32_t hub2_id, uint32_t hub2_platform_id);
		virtual void render(Scene& scene);
	};
}
}
}
