/*
 * Copyright (C) G�bor G�rzs�ny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <vector>
#include <raz/memory.hpp>
#include "gfx/scene/model/Model.hpp"
#include "gfx/shape/PlatformRingShape.hpp"

namespace gfx
{
namespace scene
{
namespace model
{
	class HubModel : public Model
	{
	public:
		HubModel(scene::Scene& scene, uint32_t id, uint64_t seed, unsigned size, unsigned complexity);
		virtual void render(scene::Scene& scene);
		const gfx::shape::PlatformRingShape::Platform& getPlatform(size_t id);

	private:
		gfx::shape::PlatformRingShape::PlatformVector m_platforms;
	};
}
}
}