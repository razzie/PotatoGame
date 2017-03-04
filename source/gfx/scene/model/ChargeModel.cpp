/*
 * Copyright (C) G�bor G�rzs�ny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "gfx/scene/Scene.hpp"
#include "gfx/scene/model/ChargeModel.hpp"

gfx::scene::model::ChargeModel::ChargeModel(Scene& scene, uint32_t id, uint32_t hub_id, uint32_t platform_id) :
	Model(id)
{
	core::MeshBuffer<> meshbuffer(scene.getMemoryPool());



	meshbuffer.recalculateNormals();

	auto& mesh = getMesh();
	mesh = meshbuffer.createMesh();
	mesh.bindShader(scene.getTransportShader());

	GL::Vec3 position;
	scene.getHubPlatformPosition(hub_id, platform_id, position);
	setPosition(position);
}

void gfx::scene::model::ChargeModel::render(Scene& scene)
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