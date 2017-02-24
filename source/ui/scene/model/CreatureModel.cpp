/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "ui/shape/CreatureShape.hpp"
#include "ui/scene/Scene.hpp"
#include "ui/scene/model/CreatureModel.hpp"

ui::scene::model::CreatureModel::CreatureModel(scene::Scene& scene, uint32_t id, uint64_t seed, GL::Color color) :
	Model(id)
{
	raz::Random random(seed);
	ui::core::MeshBuffer<> meshbuffer(scene.getMemoryPool());

	ui::shape::CreatureShape shape(random, color);
	shape.generate(meshbuffer);

	meshbuffer.recalculateNormals();

	auto& mesh = getMesh();
	mesh = meshbuffer.createMesh();
	mesh.bindShader(scene.getShader("hub"_shader));

	setPosition({ 10.f, 0.f, 0.f });
}

void ui::scene::model::CreatureModel::render(scene::Scene& scene)
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
