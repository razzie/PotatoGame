/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <raz/random.hpp>
#include "common/GLlerp.hpp"
#include "gfx/scene/Scene.hpp"
#include "gfx/shape/WireShape.hpp"
#include "gfx/scene/model/TransportModel.hpp"

gfx::scene::model::TransportModel::TransportModel(Scene& scene, uint32_t id, uint32_t hub1_id, uint32_t hub1_platform_id, uint32_t hub2_id, uint32_t hub2_platform_id) :
	Model(id)
{
	HubModel* hub1 = scene.getHub(hub1_id);
	HubModel* hub2 = scene.getHub(hub2_id);

	if (!hub1 || !hub2)
		return;

	const HubModel::Platform* platform1 = hub1->getPlatform(hub1_platform_id);
	const HubModel::Platform* platform2 = hub2->getPlatform(hub2_platform_id);

	if (!platform1 || !platform2)
		return;

	core::MeshBuffer<> meshbuffer(scene.getMemoryPool());
	raz::Random random(hub1->getSeed() + hub2->getSeed());

	//GL::Vec3 p1;
	//GL::Vec3 p2;
	//scene.getHubPlatformPosition(hub1_id, hub1_platform_id, p1);
	//scene.getHubPlatformPosition(hub2_id, hub2_platform_id, p2);

	//shape::WireShape wire(p1, p2, 8, 5.f);
	//wire.generate(meshbuffer);

	for (unsigned i = 0, count = random(1u, 3u); i < count; ++i)
	{
		GL::Vec3 p1 = common::lerp(platform1->outer1, platform1->outer2, random(0.25f, 0.75f)) + hub1->getPosition();
		GL::Vec3 p2 = common::lerp(platform2->outer1, platform2->outer2, random(0.25f, 0.75f)) + hub2->getPosition();
		p1.Y -= 0.25f;
		p2.Y -= 0.25f;

		shape::WireShape wire(p1, p2, 8, random(0.5f, 3.f));
		wire.generate(meshbuffer);
	}

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
	program.SetUniform("diffuse_color", GL::Color(255, 255, 255));
	program.SetUniform("light_source", scene.getCamera().getPosition());
	program.SetUniform("time", scene.getElapsedTime());

	GL::Context& gl = scene.getContext();
	getMesh().render(gl);
}
