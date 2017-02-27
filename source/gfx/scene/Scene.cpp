/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <ctime>
#include <GL/Math/Util.hpp>
#include "gfx/scene/Scene.hpp"
#include "gfx/scene/model/HubModel.hpp"

gfx::scene::Scene::Scene(GL::Context& gl, gfx::core::ShaderTable& shader_table) :
	m_gl(gl),
	m_shader_table(shader_table),
	m_cam(1024.f / 768.f),
	m_current_shader(nullptr)
{
	m_hubs.emplace_back(*this, 0, std::time(NULL), 6, 6);
	m_creatures.emplace_back(*this, 0, std::time(NULL), GL::Color(255, 240, 240));
}

gfx::scene::Scene::~Scene()
{
}

GL::Context& gfx::scene::Scene::getContext()
{
	return m_gl;
}

raz::IMemoryPool* gfx::scene::Scene::getMemoryPool()
{
	return nullptr;
}

gfx::scene::Camera& gfx::scene::Scene::getCamera()
{
	return m_cam;
}

const gfx::scene::Camera& gfx::scene::Scene::getCamera() const
{
	return m_cam;
}

const GL::Mat4& gfx::scene::Scene::getCameraMatrix() const
{
	return m_cam.getMatrix();
}

GL::Program& gfx::scene::Scene::getCurrentShader()
{
	return *m_current_shader;
}

void gfx::scene::Scene::render()
{
	m_current_shader = &m_shader_table.getHubShader();
	m_gl.UseProgram(*m_current_shader);

	for (auto& hub : m_hubs)
		hub.render(*this);

	for (auto& creature : m_creatures)
		creature.render(*this);
}


GL::Program& gfx::scene::Scene::getHubShader()
{
	return m_shader_table.getHubShader();
}

gfx::scene::model::HubModel* gfx::scene::Scene::getHub(uint32_t id)
{
	for (auto& hub : m_hubs)
	{
		if (hub.getID() == id)
			return &hub;
	}

	return nullptr;
}


GL::Program& gfx::scene::Scene::getCreatureShader()
{
	return m_shader_table.getHubShader();
}

gfx::scene::model::CreatureModel* gfx::scene::Scene::getCreature(uint32_t id)
{
	for (auto& creature : m_creatures)
	{
		if (creature.getID() == id)
			return &creature;
	}

	return nullptr;
}
