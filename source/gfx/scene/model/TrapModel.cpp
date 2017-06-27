/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "gfx/shape/SpikeShape.hpp"
#include "gfx/scene/Scene.hpp"
#include "gfx/scene/model/TrapModel.hpp"

gfx::scene::model::TrapModel::TrapModel(Scene& scene, uint32_t id, GL::Color color, uint32_t hub_id, uint32_t platform_id) :
	Model(id)
{
	gfx::shape::PlatformShape platform;
	if (!scene.getPlatform(hub_id, platform_id, platform))
		return;

	core::MeshBuffer<> meshbuffer(scene.getMemoryPool());
	raz::Random random(platform.seed);

	for (int i = 0, spikes = random(4u, 8u); i < spikes; ++i)
	{
		GL::Vec3 pos = platform.getRandomPosition(random) - platform.center;
		gfx::shape::SpikeShape shape(pos, random(3, 5) * 0.0125f);
		shape.generate(meshbuffer);
	}

	meshbuffer.recalculateNormals();
	getMesh() = meshbuffer;

	setPosition(platform.center);
	setColor(color);
}
