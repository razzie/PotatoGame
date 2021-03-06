/*
 * Copyright (C) G�bor G�rzs�ny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <raz/random.hpp>
#include "gfx/shape/SphereShape.hpp"
#include "gfx/scene/Scene.hpp"
#include "gfx/model/ResourceModel.hpp"

gfx::model::ResourceModel::ResourceModel(gfx::scene::Scene& scene, uint32_t id, uint32_t value, uint32_t hub_id, uint32_t platform_id) :
	Model(id)
{
	gfx::shape::PlatformShape platform;
	if (!scene.getPlatform(hub_id, platform_id, platform))
		return;

	core::MeshBuffer<> meshbuffer(scene.getMemoryPool());
	raz::Random random(platform.seed);

	for (uint32_t i = 0; i < value; ++i)
	{
		GL::Vec3 pos = platform.getRandomPosition(random) - platform.center;
		GL::uchar color = (GL::uchar)random(64u, 128u);
		float radius = 0.1f + 0.0125f * i;

		pos.Y += radius * 0.5f;

		shape::SphereShape sphere(pos, radius, random(3u, 6u), GL::Color(color, color, color));
		sphere.generate(meshbuffer);
	}

	meshbuffer.recalculateNormals();
	getMesh() = meshbuffer;

	setPosition(platform.center);
}
