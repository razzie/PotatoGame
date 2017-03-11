/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "gfx/scene/Scene.hpp"
#include "gfx/shape/WireShape.hpp"
#include "gfx/scene/model/TransportModel.hpp"

gfx::scene::model::TransportModel::TransportModel(Scene& scene, uint32_t id, uint32_t hub1_id, uint32_t hub1_platform_id, uint32_t hub2_id, uint32_t hub2_platform_id) :
	Model(id)
{
	core::MeshBuffer<> meshbuffer(scene.getMemoryPool());



	meshbuffer.recalculateNormals();

	auto& mesh = getMesh();
	mesh = meshbuffer.createMesh();
	mesh.bindShader(scene.getTransportShader());
}

void gfx::scene::model::TransportModel::render(Scene& scene)
{
	GL::Mat4 world;
	GL::Mat4 normal;
	getMatrices(world, normal);

	auto& program = scene.getCurrentShader();
	program.SetUniform("world_mat", world);
	program.SetUniform("normal_mat", normal);
	program.SetUniform("screen_mat", scene.getCameraMatrix() * world);
	program.SetUniform("light_source", scene.getCamera().getPosition());
	program.SetUniform("diffuse_color", GL::Color(255, 255, 255));

	GL::Context& gl = scene.getContext();
	getMesh().render(gl);
}
