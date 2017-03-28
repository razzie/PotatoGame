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
	class HubModel : public Model
	{
	public:
		typedef gfx::shape::PlatformRingShape::Platform Platform;

		HubModel(scene::Scene& scene, uint32_t id, uint64_t seed, uint32_t size, GL::Vec2 position);
		uint64_t getSeed() const;
		const gfx::shape::PlatformRingShape::Platform* getPlatform(size_t id);
		void changeColor(GL::Color color);
		virtual void render(scene::Scene& scene);

	private:
		uint64_t m_seed;
		gfx::shape::PlatformRingShape::PlatformVector m_platforms;
		GL::Color m_color;
	};
}
}
}
