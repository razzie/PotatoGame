/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "gfx/scene/Scene.hpp"
#include "gfx/model/HubModel.hpp"
#include "gfx/shape/CreatureShape.hpp"
#include "gfx/shape/VoronoiRocksShape.hpp"

gfx::model::HubModel::HubModel(scene::Scene& scene, uint32_t id, uint64_t seed, uint32_t size, GL::Vec2 position) :
	Model(id),
	m_platforms(scene.getMemoryPool())
{
	raz::Random random(seed);
	const unsigned complexity = size + random(-1, 2);

	gfx::shape::PlatformRingShape platforms(size, complexity);
	platforms.generate(seed, m_platforms);

	m_async_mesh = std::async(std::launch::async, &HubModel::generate, seed, size, complexity);

	setPosition(GL::Vec3(position.X, 0.f, position.Y));
	setColor(GL::Color(224, 224, 224));
}

bool gfx::model::HubModel::getPlatform(size_t platform_id, gfx::shape::PlatformShape& platform) const
{
	if (platform_id < m_platforms.size())
	{
		platform = m_platforms[platform_id];
		return true;
	}

	return false;
}

void gfx::model::HubModel::render(MaterialType& material, GL::Context& gl)
{
	auto& mesh = getMesh();
	if (mesh)
	{
		Model::render(material, gl);
	}
	else
	{
		auto status = m_async_mesh.wait_for(std::chrono::milliseconds(1));
		if (status == std::future_status::ready)
		{
			auto& mesh = getMesh();
			mesh = m_async_mesh.get();
			mesh.bindShader(material.shader);
		}
	}
}

gfx::core::MeshBuffer<> gfx::model::HubModel::generate(uint64_t seed, unsigned size, unsigned complexity)
{
	core::MeshBuffer<> meshbuffer;
	raz::Random random(seed);

	gfx::shape::CreatureShape creature(random);
	creature.generate(meshbuffer);
	GL::Mat4 mat;
	mat.Scale({ (float)size, (float)size, (float)size });
	meshbuffer.transform(mat, "position");

	gfx::shape::VoronoiRocksShape pillar((float)size, complexity);
	pillar.generate(random, meshbuffer);

	gfx::shape::PlatformRingShape platformring(size, complexity);
	gfx::shape::Platforms platforms;
	platformring.generate(seed, platforms);
	platformring.generate(platforms, meshbuffer);

	meshbuffer.recalculateNormals();

	return std::move(meshbuffer);
}
