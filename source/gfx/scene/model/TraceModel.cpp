/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <cmath>
#include "common/PI.hpp"
#include "gfx/scene/Scene.hpp"
#include "gfx/scene/model/TraceModel.hpp"

gfx::scene::model::TraceModel::TraceModel(Scene& scene, uint32_t id, GL::Color color, uint32_t hub_id, uint32_t platform_id) :
	Model(id),
	m_color(color)
{
	HubModel* hub;
	const HubModel::Platform* platform;

	if (!scene.getHubPlatform(hub_id, platform_id, hub, platform))
		return;

	core::MeshBuffer<> meshbuffer(scene.getMemoryPool());

	const unsigned edges = 12;
	const float angle_step = static_cast<float>(common::PI * 2 / edges);
	float angle_rad = 0.f;
	uint16_t base_index = (uint16_t)meshbuffer.vertices.size();

	for (unsigned i = 0; i < edges; ++i)
	{
		float x = 0.5f + 0.125f * std::sin(angle_rad);
		float y = 0.5f + 0.125f * std::cos(angle_rad);

		GL::Vec3 pos = platform->getPosition(x, y);
		pos.Y += 0.025f;
		gfx::core::Vertex v{ pos, GL::Vec3(0.f, 1.f, 0.f), GL::Color(224, 224, 224) };
		meshbuffer.vertices.push_back(v);

		angle_rad += angle_step;
	}

	for (unsigned i = 1; i < edges - 1; ++i)
	{
		meshbuffer.indices.push_back(base_index);
		meshbuffer.indices.push_back(base_index + i + 1);
		meshbuffer.indices.push_back(base_index + i);
	}

	meshbuffer.recalculateNormals();

	auto& mesh = getMesh();
	mesh = meshbuffer.createMesh();
	mesh.bindShader(scene.getTraceShader());

	setPosition(platform->center + hub->getPosition());
}

void gfx::scene::model::TraceModel::render(Scene& scene)
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
