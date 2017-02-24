/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <ctime>
#include <GL/Math/Util.hpp>
#include "ui/core/SimpleShader.hpp"
#include "ui/core/HubShader.hpp"
#include "ui/scene/Scene.hpp"
#include "ui/scene/model/HubModel.hpp"

ui::scene::Scene::Scene(GL::Context& gl) :
	m_gl(gl),
	m_cam(1024.f / 768.f),
	m_current_shader(nullptr)
{
	m_shaders.emplace("simple"_shader, core::SimpleShader().getProgram());
	m_shaders.emplace("hub"_shader, core::HubShader().getProgram());

	m_hubs.emplace_back(*this, 0, std::time(NULL), 6, 6);
	m_creatures.emplace_back(*this, 0, std::time(NULL), GL::Color(255, 240, 240));
}

ui::scene::Scene::~Scene()
{
}

GL::Context& ui::scene::Scene::getContext()
{
	return m_gl;
}

raz::IMemoryPool* ui::scene::Scene::getMemoryPool()
{
	return nullptr;
}

ui::scene::Camera& ui::scene::Scene::getCamera()
{
	return m_cam;
}

const ui::scene::Camera& ui::scene::Scene::getCamera() const
{
	return m_cam;
}

const GL::Mat4& ui::scene::Scene::getCameraMatrix() const
{
	return m_cam.getMatrix();
}

GL::Program& ui::scene::Scene::getShader(uint32_t shader)
{
	auto it = m_shaders.find(shader);
	if (it == m_shaders.end())
		throw std::runtime_error("no such shader exists");

	return it->second;
}

GL::Program& ui::scene::Scene::getCurrentShader()
{
	return *m_current_shader;
}

void ui::scene::Scene::render()
{
	m_current_shader = &getShader("hub"_shader);
	m_gl.UseProgram(*m_current_shader);

	for (auto& hub : m_hubs)
		hub.render(*this);

	for (auto& creature : m_creatures)
		creature.render(*this);
}

ui::scene::model::HubModel* ui::scene::Scene::getHub(uint32_t id)
{
	for (auto& hub : m_hubs)
	{
		if (hub.getID() == id)
			return &hub;
	}

	return nullptr;
}

ui::scene::model::CreatureModel* ui::scene::Scene::getCreature(uint32_t id)
{
	for (auto& creature : m_creatures)
	{
		if (creature.getID() == id)
			return &creature;
	}

	return nullptr;
}
