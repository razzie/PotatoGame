/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "gfx/shape/CreatureShape.hpp"
#include "gfx/scene/Scene.hpp"
#include "gfx/scene/model/CreatureModel.hpp"

gfx::scene::model::CreatureModel::CreatureModel(scene::Scene& scene, uint32_t id, uint64_t seed, GL::Color color, uint32_t hub_id, uint32_t platform_id) :
	Model(id),
	m_color(color)
{
	raz::Random random(seed);
	gfx::core::MeshBuffer<> meshbuffer(scene.getMemoryPool());

	gfx::shape::CreatureShape shape(random);
	shape.generate(meshbuffer);

	meshbuffer.recalculateNormals();

	auto& mesh = getMesh();
	mesh = meshbuffer.createMesh();
	mesh.bindShader(scene.getCreatureShader());

	GL::Vec3 position;
	scene.getHubPlatformPosition(hub_id, platform_id, position);
	setPosition(position);
}

void gfx::scene::model::CreatureModel::changeColor(GL::Color color)
{
	m_color = color;
}

void gfx::scene::model::CreatureModel::render(scene::Scene& scene)
{
	GL::Mat4 world;
	GL::Mat4 normal;
	getMatrices(world, normal);

	auto& program = scene.getCurrentShader();
	program.SetUniform("world_mat", world);
	program.SetUniform("normal_mat", normal);
	program.SetUniform("screen_mat", scene.getCameraMatrix() * world);
	program.SetUniform("diffuse_color", m_color);
	program.SetUniform("light_source", scene.getCamera().getPosition());
	program.SetUniform("time", scene.getElapsedTime());

	GL::Context& gl = scene.getContext();
	getMesh().render(gl);
}
