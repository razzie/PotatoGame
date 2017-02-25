/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "gfx/scene/Scene.hpp"
#include "gfx/scene/model/HubModel.hpp"
#include "gfx/shape/VoronoiPillarShape.hpp"

gfx::scene::model::HubModel::HubModel(scene::Scene& scene, uint32_t id, uint64_t seed, unsigned size, unsigned complexity) :
	Model(id)
{
	core::MeshBuffer<> meshbuffer(scene.getMemoryPool());
	raz::Random random(seed);

	gfx::shape::VoronoiPillarShape pillar((float)size, complexity);
	pillar.generate(random, meshbuffer);

	gfx::shape::PlatformRingShape platforms(size, complexity);
	platforms.generate(random, m_platforms, meshbuffer);

	meshbuffer.recalculateNormals();

	auto& mesh = getMesh();
	mesh = meshbuffer.createMesh();
	mesh.bindShader(scene.getShader("hub"_shader));
}

void gfx::scene::model::HubModel::render(scene::Scene& scene)
{
	GL::Mat4 world;
	GL::Mat4 normal;
	getMatrices(world, normal);

	auto& program = scene.getCurrentShader();
	program.SetUniform("world_mat", world);
	program.SetUniform("normal_mat", normal);
	program.SetUniform("screen_mat", scene.getCameraMatrix() * world);
	program.SetUniform("light_source", scene.getCamera().getPosition());

	GL::Context& gl = scene.getContext();
	getMesh().render(gl);
}

const gfx::shape::PlatformRingShape::Platform& gfx::scene::model::HubModel::getPlatform(size_t id)
{
	return m_platforms[id];
}
