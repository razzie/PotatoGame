/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "gfx/shape/CreatureShape.hpp"
#include "gfx/scene/Scene.hpp"
#include "gfx/scene/model/CreatureModel.hpp"

gfx::scene::model::CreatureModel::CreatureModel(scene::Scene& scene, uint32_t id, uint64_t seed, GL::Color color, uint32_t hub_id, uint32_t platform_id) :
	Model(id)
{
	gfx::shape::PlatformShape platform;
	if (!scene.getPlatform(hub_id, platform_id, platform))
		return;

	raz::Random random(seed);
	gfx::core::MeshBuffer<> meshbuffer(scene.getMemoryPool());

	gfx::shape::CreatureShape shape(random);
	shape.generate(meshbuffer);

	meshbuffer.recalculateNormals();
	getMesh() = meshbuffer;

	setPosition(platform.center);
	setColor(color);
}
