/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "gfx/shape/SphereShape.hpp"
#include "gfx/scene/Scene.hpp"
#include "gfx/scene/model/ChargeModel.hpp"

gfx::scene::model::ChargeModel::ChargeModel(Scene& scene, uint32_t id, uint32_t hub_id, uint32_t platform_id) :
	Model(id)
{
	gfx::shape::PlatformShape platform;
	if (!scene.getPlatform(hub_id, platform_id, platform))
		return;

	core::MeshBuffer<> meshbuffer(scene.getMemoryPool());

	shape::SphereShape sphere(GL::Vec3(0.f, 0.2f, 0.f), 0.2f, 8, GL::Color(240, 240, 240));
	sphere.generate(meshbuffer);

	meshbuffer.recalculateNormals();
	getMesh() = meshbuffer;

	setPosition(platform.center);
}
