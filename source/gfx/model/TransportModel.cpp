/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <raz/random.hpp>
#include "gfx/scene/Scene.hpp"
#include "gfx/shape/WireShape.hpp"
#include "gfx/model/TransportModel.hpp"

gfx::model::TransportModel::TransportModel(gfx::scene::Scene& scene, uint32_t id, uint32_t hub1_id, uint32_t hub1_platform_id, uint32_t hub2_id, uint32_t hub2_platform_id) :
	Model(id)
{
	gfx::shape::PlatformShape platform1, platform2;
	if (!scene.getPlatform(hub1_id, hub1_platform_id, platform1) || !scene.getPlatform(hub2_id, hub2_platform_id, platform2))
		return;

	m_start_pos = platform1.center;
	m_end_pos = platform2.center;

	core::MeshBuffer<> meshbuffer(scene.getMemoryPool());
	raz::Random random(platform1.seed + platform2.seed);

	for (size_t i = 0, wires = random() % 2 + 1; i < wires; ++i)
	{
		GL::Vec3 p1 = platform1.getRandomPosition(random);
		GL::Vec3 p2 = platform2.getRandomPosition(random);
		p1.Y -= 0.25f;
		p2.Y -= 0.25f;

		shape::WireShape wire(p1, p2, 16, random(0.5f, 3.f), random(0.0625f, 0.125f));
		wire.generate(meshbuffer);
	}

	meshbuffer.recalculateNormals();
	getMesh() = meshbuffer;
}

void gfx::model::TransportModel::render(MaterialType& material, GL::Context& gl)
{
	material.start_pos = m_start_pos;
	material.end_pos = m_end_pos;

	Model::render(material, gl);
}
