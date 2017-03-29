/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <raz/random.hpp>
#include "gfx/shape/SphereShape.hpp"
#include "gfx/scene/Scene.hpp"
#include "gfx/scene/model/ResourceModel.hpp"

gfx::scene::model::ResourceModel::ResourceModel(Scene& scene, uint32_t id, uint32_t value, uint32_t hub_id, uint32_t platform_id) :
	Model(id)
{
	HubModel* hub;
	const HubModel::Platform* platform;

	if (!scene.getHubPlatform(hub_id, platform_id, hub, platform))
		return;

	core::MeshBuffer<> meshbuffer(scene.getMemoryPool());
	raz::Random random(hub->getSeed());

	for (uint32_t i = 0; i < value; ++i)
	{
		GL::Vec3 pos = platform->getPosition(random(0.25f, 0.75f), random(0.25f, 0.75f));
		GL::uchar color = (GL::uchar)random(64u, 128u);
		float radius = 0.1f + 0.0125f * i;

		pos.Y += radius;

		shape::SphereShape sphere(pos, radius, 8, GL::Color(color, color, color));
		sphere.generate(meshbuffer);
	}

	meshbuffer.recalculateNormals();

	auto& mesh = getMesh();
	mesh = meshbuffer.createMesh();
	mesh.bindShader(scene.getResourceShader());

	setPosition(platform->center + hub->getPosition());
}

void gfx::scene::model::ResourceModel::render(Scene& scene)
{
	GL::Mat4 world;
	GL::Mat4 normal;
	getMatrices(world, normal);

	auto& program = scene.getCurrentShader();
	program.SetUniform("world_mat", world);
	program.SetUniform("normal_mat", normal);
	program.SetUniform("screen_mat", scene.getCameraMatrix() * world);
	program.SetUniform("diffuse_color", GL::Color(255, 255, 255));
	program.SetUniform("light_source", scene.getCamera().getPosition());
	program.SetUniform("time", scene.getElapsedTime());

	GL::Context& gl = scene.getContext();
	getMesh().render(gl);
}
