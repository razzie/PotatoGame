/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <future>
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
		bool getPlatform(size_t platform_id, gfx::shape::PlatformShape& platform) const;
		void render(MaterialType& material, GL::Context& gl);

	private:
		gfx::shape::Platforms m_platforms;
		std::future<gfx::core::MeshBuffer<>> m_async_mesh;

		static gfx::core::MeshBuffer<> generate(uint64_t seed, unsigned size, unsigned complexity);
	};
}
}
}
