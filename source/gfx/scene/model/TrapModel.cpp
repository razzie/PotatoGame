/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "gfx/scene/Scene.hpp"
#include "gfx/scene/model/TrapModel.hpp"

static void addSpike(GL::Vec3 position, float scale, gfx::core::MeshBuffer<>& meshbuffer)
{
	const GL::Color color(224, 224, 224);
	uint16_t base_index = (uint16_t)meshbuffer.vertices.size();

	gfx::core::Vertex top{ position + GL::Vec3(0.f, 4.f * scale, 0.f), GL::Vec3(), color };
	gfx::core::Vertex bottom1{ position + GL::Vec3(scale, 0.f, scale), GL::Vec3(), color };
	gfx::core::Vertex bottom2{ position + GL::Vec3(scale, 0.f, -scale), GL::Vec3(), color };
	gfx::core::Vertex bottom3{ position + GL::Vec3(-scale, 0.f, -scale), GL::Vec3(), color };
	gfx::core::Vertex bottom4{ position + GL::Vec3(-scale, 0.f, scale), GL::Vec3(), color };

	meshbuffer.vertices.push_back(top);
	meshbuffer.vertices.push_back(bottom1);
	meshbuffer.vertices.push_back(bottom2);
	meshbuffer.vertices.push_back(bottom3);
	meshbuffer.vertices.push_back(bottom4);

	uint16_t top_index = base_index;
	uint16_t bottom1_index = base_index + 1;
	uint16_t bottom2_index = base_index + 2;
	uint16_t bottom3_index = base_index + 3;
	uint16_t bottom4_index = base_index + 4;

	meshbuffer.indices.push_back(top_index);
	meshbuffer.indices.push_back(bottom1_index);
	meshbuffer.indices.push_back(bottom2_index);

	meshbuffer.indices.push_back(top_index);
	meshbuffer.indices.push_back(bottom2_index);
	meshbuffer.indices.push_back(bottom3_index);

	meshbuffer.indices.push_back(top_index);
	meshbuffer.indices.push_back(bottom3_index);
	meshbuffer.indices.push_back(bottom4_index);

	meshbuffer.indices.push_back(top_index);
	meshbuffer.indices.push_back(bottom4_index);
	meshbuffer.indices.push_back(bottom1_index);
}

gfx::scene::model::TrapModel::TrapModel(Scene& scene, uint32_t id, GL::Color color, uint32_t hub_id, uint32_t platform_id) :
	Model(id)
{
	gfx::shape::PlatformShape platform;
	if (!scene.getPlatform(hub_id, platform_id, platform))
		return;

	core::MeshBuffer<> meshbuffer(scene.getMemoryPool());
	raz::Random random(platform.seed);

	for (int i = 0, spikes = random(3u, 5u); i < spikes; ++i)
	{
		GL::Vec3 pos = platform.getRandomPosition(random) - platform.center;
		addSpike(pos, random(3, 5) * 0.025f, meshbuffer);
	}

	meshbuffer.recalculateNormals();

	auto& mesh = getMesh();
	mesh = meshbuffer.createMesh();

	setPosition(platform.center);
	setColor(color);
}
