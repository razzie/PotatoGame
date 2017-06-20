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
	Model(id)
{
	gfx::shape::PlatformShape platform;
	if (!scene.getPlatform(hub_id, platform_id, platform))
		return;

	core::MeshBuffer<> meshbuffer(scene.getMemoryPool());

	const unsigned edges = 12;
	const float angle_step = static_cast<float>(common::PI * 2 / edges);
	float angle_rad = 0.f;
	uint16_t base_index = (uint16_t)meshbuffer.vertices.size();

	for (unsigned i = 0; i < edges; ++i)
	{
		float x = 0.125f * std::sin(angle_rad);
		float z = 0.125f * -std::cos(angle_rad);

		gfx::core::Vertex v{ GL::Vec3(x, 0.025f, z), GL::Vec3(0.f, 1.f, 0.f), GL::Color(224, 224, 224) };
		meshbuffer.vertices.push_back(v);

		angle_rad += angle_step;
	}

	for (unsigned i = 1; i < edges - 1; ++i)
	{
		meshbuffer.indices.push_back(base_index);
		meshbuffer.indices.push_back(base_index + i + 1);
		meshbuffer.indices.push_back(base_index + i);
	}

	//meshbuffer.recalculateNormals();

	auto& mesh = getMesh();
	mesh = meshbuffer.createMesh();

	setPosition(platform.center);
	setColor(color);
}
