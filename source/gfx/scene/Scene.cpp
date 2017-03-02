/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <ctime>
#include <GL/Math/Util.hpp>
#include "gfx/RenderThread.hpp"
#include "gfx/scene/Scene.hpp"
#include "gfx/scene/model/HubModel.hpp"

gfx::scene::Scene::Scene(RenderThread& render_thread) :
	m_render_thread(render_thread),
	m_gl(render_thread.getContext()),
	m_shader_table(render_thread.getShaderTable()),
	m_cam(render_thread.getAspectRatio()),
	m_current_shader(nullptr)
{
	m_cam.setPosition({ -8, 8, -8 });

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

bool gfx::scene::Scene::feed(const GL::Event& ev)
{
	auto& helper = m_render_thread.getInputHelper();

	if (ev.Type == GL::Event::KeyDown)
	{
		float speed = 5.0f;

		switch (ev.Key.Code)
		{
		case GL::Key::W:
			m_cam.move(speed, 0.f);
			return true;
		case GL::Key::S:
			m_cam.move(-speed, 0.f);
			return true;
		case GL::Key::A:
			m_cam.move(0.f, -speed);
			return true;
		case GL::Key::D:
			m_cam.move(0.f, speed);
			return true;
		}
	}
	else if (ev.Type == GL::Event::MouseMove)
	{
		if (helper.isLeftMouseButtonDown() || helper.isRightMouseButtonDown())
		{
			auto delta = helper.getMouseDelta();
			m_cam.rotate((float)-delta.x, (float)delta.y);
			return true;
		}
	}
	else if (ev.Type == GL::Event::MouseWheel)
	{
		m_cam.zoom(ev.Mouse.Delta > 0 ? 0.8f : -1.2f);
		return true;
	}

	return false;
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
