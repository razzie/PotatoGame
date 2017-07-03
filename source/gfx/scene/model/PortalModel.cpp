/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <cmath>
#include "common/PI.hpp"
#include "gfx/scene/Scene.hpp"
#include "gfx/scene/model/PortalModel.hpp"

gfx::scene::model::PortalModel::PortalModel(Scene& scene, uint32_t id, uint32_t hub_id, uint32_t platform_id) :
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

	meshbuffer.vertices.push_back(gfx::core::Vertex{ GL::Vec3(0.f, 2.f, 0.f), GL::Vec3(), GL::Color(255, 255, 255) });

	for (unsigned i = 0; i < edges; ++i)
	{
		float x = 0.25f * std::sin(angle_rad);
		float z = 0.25f * -std::cos(angle_rad);

		gfx::core::Vertex v{ GL::Vec3(x, 0.f, z), GL::Vec3(), GL::Color(255, 255, 255) };
		meshbuffer.vertices.push_back(v);

		angle_rad += angle_step;

		meshbuffer.indices.push_back(base_index);
		meshbuffer.indices.push_back(base_index + 1 + ((i + 1) % edges));
		meshbuffer.indices.push_back(base_index + 1 + i);
	}

	//meshbuffer.recalculateNormals();
	getMesh() = meshbuffer;

	setPosition(platform.center);
	setColor(GL::Color(128, 128, 128));
}
