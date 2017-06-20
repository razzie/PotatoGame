/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <GL/Math/Vec2.hpp>
#include "gfx/scene/model/Model.hpp"
#include "gfx/shape/PlatformRingShape.hpp"

namespace gfx
{
namespace scene
{
namespace model
{
	class HubModel : public Model<>
	{
	public:
		HubModel(scene::Scene& scene, uint32_t id, uint64_t seed, uint32_t size, GL::Vec2 position);
		uint64_t getSeed() const;
		bool getPlatform(size_t platform_id, gfx::shape::PlatformShape& platform) const;

	private:
		uint64_t m_seed;
		gfx::shape::Platforms m_platforms;
	};
}
}
}
