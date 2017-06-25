/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "gfx/shape/SpawnShape.hpp"
#include "gfx/scene/Scene.hpp"
#include "gfx/scene/model/SpawnModel.hpp"

gfx::scene::model::SpawnModel::SpawnModel(Scene& scene, uint32_t id, GL::Color color, uint32_t hub_id, uint32_t platform_id) :
	Model(id)
{
	gfx::shape::PlatformShape platform;
	if (!scene.getPlatform(hub_id, platform_id, platform))
		return;

	core::MeshBuffer<> meshbuffer(scene.getMemoryPool());

	gfx::shape::SpawnShape shape(GL::Vec3(), platform.size * 0.75f, (float)platform.seed);
	shape.generate(meshbuffer);

	meshbuffer.recalculateNormals();

	auto& mesh = getMesh();
	mesh = meshbuffer.createMesh();

	setPosition(platform.center);
	setColor(color);
}
