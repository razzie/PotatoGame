/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <vector>
#include <raz/memory.hpp>
#include "ui/scene/model/Model.hpp"
#include "ui/shape/PlatformRingShape.hpp"

namespace ui
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
		const ui::shape::PlatformRingShape::Platform& getPlatform(size_t id);

	private:
		ui::shape::PlatformRingShape::PlatformVector m_platforms;
	};
}
}
}
