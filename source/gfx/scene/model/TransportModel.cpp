/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <raz/random.hpp>
#include "gfx/scene/Scene.hpp"
#include "gfx/shape/WireShape.hpp"
#include "gfx/scene/model/TransportModel.hpp"

gfx::scene::model::TransportModel::TransportModel(Scene& scene, uint32_t id, uint32_t hub1_id, uint32_t hub1_platform_id, uint32_t hub2_id, uint32_t hub2_platform_id) :
	Model(id)
{
	gfx::shape::PlatformShape platform1, platform2;
	if (!scene.getPlatform(hub1_id, hub1_platform_id, platform1) || !scene.getPlatform(hub2_id, hub2_platform_id, platform2))
		return;

	core::MeshBuffer<> meshbuffer(scene.getMemoryPool());
	raz::Random random(platform1.seed + platform2.seed);

	for (size_t i = 0, wires = random(1u, 3u); i < wires; ++i)
	{
		GL::Vec3 p1 = platform1.getRandomPosition(random);
		GL::Vec3 p2 = platform2.getRandomPosition(random);
		p1.Y -= 0.25f;
		p2.Y -= 0.25f;

		shape::WireShape wire(p1, p2, 8, random(0.5f, 3.f));
		wire.generate(meshbuffer);
	}

	meshbuffer.recalculateNormals();
	getMesh() = meshbuffer;
}
