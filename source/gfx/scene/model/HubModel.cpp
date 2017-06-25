/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "gfx/scene/Scene.hpp"
#include "gfx/scene/model/HubModel.hpp"
#include "gfx/shape/VoronoiPillarShape.hpp"

gfx::scene::model::HubModel::HubModel(scene::Scene& scene, uint32_t id, uint64_t seed, uint32_t size, GL::Vec2 position) :
	Model(id),
	m_seed(seed),
	m_platforms(scene.getMemoryPool())
{
	core::MeshBuffer<> meshbuffer(scene.getMemoryPool());
	raz::Random random(seed);

	const unsigned complexity = size + random(-1, 2);

	gfx::shape::VoronoiPillarShape pillar((float)size, complexity);
	pillar.generate(random, meshbuffer);

	gfx::shape::PlatformRingShape platforms(size, complexity);
	platforms.generate(random, m_platforms);
	platforms.generate(m_platforms, meshbuffer);

	meshbuffer.recalculateNormals();

	auto& mesh = getMesh();
	mesh = meshbuffer.createMesh();

	setPosition(GL::Vec3(position.X, 0.f, position.Y));
	setColor(GL::Color(224, 224, 224));
}

uint64_t gfx::scene::model::HubModel::getSeed() const
{
	return m_seed;
}

bool gfx::scene::model::HubModel::getPlatform(size_t platform_id, gfx::shape::PlatformShape& platform) const
{
	if (platform_id < m_platforms.size())
	{
		platform = m_platforms[platform_id];
		return true;
	}

	return false;
}
