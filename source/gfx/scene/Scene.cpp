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
	m_memory(render_thread.getMemoryPool()),
	m_shader_table(render_thread.getShaderTable()),
	m_current_shader(nullptr),
	m_cam(render_thread.getAspectRatio()),
	m_horizon(render_thread.getShaderTable().getHorizonShader()),
	m_hubs(m_memory),
	m_transports(m_memory),
	m_charges(m_memory),
	m_resources(m_memory),
	m_traces(m_memory),
	m_spawns(m_memory),
	m_portals(m_memory),
	m_traps(m_memory),
	m_creatures(m_memory)
{
	m_cam.setPosition({ -8, 8, -8 });

	addHub(0, std::time(NULL), 6, GL::Vec3());
	addCreature(0, std::time(NULL), GL::Color(255, 128, 128), 0, 0);
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
	return m_memory;
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

float gfx::scene::Scene::getElapsedTime() const
{
	return m_time;
}

bool gfx::scene::Scene::getHubPlatformPosition(uint32_t hub_id, uint32_t platform_id, GL::Vec3& position)
{
	auto* hub = getHub(hub_id);
	if (!hub)
		return false;

	auto* platform = hub->getPlatform(platform_id);
	if (!platform)
		return false;

	position = platform->center + hub->getPosition();
	return true;
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

template<class Model>
Model* getModel(std::vector<Model, raz::Allocator<Model>>& models, uint32_t id)
{
	for (auto& model : models)
	{
		if (model.getID() == id)
			return &model;
	}

	return nullptr;
}

template<class Model>
void removeModel(std::vector<Model, raz::Allocator<Model>>& models, uint32_t id)
{
	for (auto it = models.begin(), end = models.end(); it != end; ++it)
	{
		if (it->getID() == id)
		{
			models.erase(it);
			return;
		}
	}
}

template<class Model>
void renderModels(std::vector<Model, raz::Allocator<Model>>& models, gfx::scene::Scene& scene)
{
	if (!models.empty())
	{
		scene.getContext().UseProgram(scene.getCurrentShader());

		for (auto& model : models)
			model.render(scene);
	}
}

void gfx::scene::Scene::render()
{
	m_time = 0.001f * m_timer.peekElapsed();

	m_horizon.render(*this);

	m_current_shader = &getHubShader();
	renderModels(m_hubs, *this);

	m_current_shader = &getTransportShader();
	renderModels(m_transports, *this);

	m_current_shader = &getChargeShader();
	renderModels(m_charges, *this);

	m_current_shader = &getResourceShader();
	renderModels(m_resources, *this);

	m_current_shader = &getTraceShader();
	renderModels(m_traces, *this);

	m_current_shader = &getSpawnShader();
	renderModels(m_spawns, *this);

	m_current_shader = &getPortalShader();
	renderModels(m_portals, *this);

	m_current_shader = &getTrapShader();
	renderModels(m_traps, *this);

	m_current_shader = &getCreatureShader();
	renderModels(m_creatures, *this);
}

void gfx::scene::Scene::reset()
{
	// TODO: CLEAR ANIMATORS TOO

	m_hubs.clear();
	m_transports.clear();
	m_charges.clear();
	m_resources.clear();
	m_traces.clear();
	m_spawns.clear();
	m_portals.clear();
	m_traps.clear();
	m_creatures.clear();
}


GL::Program& gfx::scene::Scene::getHubShader()
{
	return m_shader_table.getHubShader();
}

gfx::scene::model::HubModel* gfx::scene::Scene::addHub(uint32_t id, uint64_t seed, uint32_t size, GL::Vec3 position)
{
	m_hubs.emplace_back(*this, id, seed, size, position);
	return &m_hubs.back();
}

gfx::scene::model::HubModel* gfx::scene::Scene::getHub(uint32_t id)
{
	return getModel(m_hubs, id);
}


GL::Program& gfx::scene::Scene::getTransportShader()
{
	return m_shader_table.getHubShader();
}

gfx::scene::model::TransportModel* gfx::scene::Scene::addTransport(uint32_t id, uint32_t hub1_id, uint32_t hub1_platform_id, uint32_t hub2_id, uint32_t hub2_platform_id)
{
	m_transports.emplace_back(*this, id, hub1_id, hub1_platform_id, hub2_id, hub2_platform_id);
	return &m_transports.back();
}

gfx::scene::model::TransportModel* gfx::scene::Scene::getTransport(uint32_t id)
{
	return getModel(m_transports, id);
}


GL::Program& gfx::scene::Scene::getChargeShader()
{
	return m_shader_table.getHubShader();
}

gfx::scene::model::ChargeModel* gfx::scene::Scene::addCharge(uint32_t id, uint32_t hub_id, uint32_t platform_id)
{
	m_charges.emplace_back(*this, id, hub_id, platform_id);
	return &m_charges.back();
}

gfx::scene::model::ChargeModel* gfx::scene::Scene::getCharge(uint32_t id)
{
	return getModel(m_charges, id);
}

void gfx::scene::Scene::removeCharge(uint32_t id)
{
	removeModel(m_charges, id);
}


GL::Program& gfx::scene::Scene::getResourceShader()
{
	return m_shader_table.getHubShader();
}

gfx::scene::model::ResourceModel* gfx::scene::Scene::addResource(uint32_t id, uint32_t value, uint32_t hub_id, uint32_t platform_id)
{
	m_resources.emplace_back(*this, id, value, hub_id, platform_id);
	return &m_resources.back();
}

gfx::scene::model::ResourceModel* gfx::scene::Scene::getResource(uint32_t id)
{
	return getModel(m_resources, id);
}

void gfx::scene::Scene::removeResource(uint32_t id)
{
	removeModel(m_resources, id);
}


GL::Program& gfx::scene::Scene::getTraceShader()
{
	return m_shader_table.getHubShader();
}

gfx::scene::model::TraceModel* gfx::scene::Scene::addTrace(uint32_t id, GL::Color color, uint32_t hub_id, uint32_t platform_id)
{
	m_traces.emplace_back(*this, id, color, hub_id, platform_id);
	return &m_traces.back();
}

gfx::scene::model::TraceModel* gfx::scene::Scene::getTrace(uint32_t id)
{
	return getModel(m_traces, id);
}

void gfx::scene::Scene::removeTrace(uint32_t id)
{
	removeModel(m_traces, id);
}


GL::Program& gfx::scene::Scene::getSpawnShader()
{
	return m_shader_table.getHubShader();
}

gfx::scene::model::SpawnModel* gfx::scene::Scene::addSpawn(uint32_t id, GL::Color color, uint32_t hub_id, uint32_t platform_id)
{
	m_spawns.emplace_back(*this, id, color, hub_id, platform_id);
	return &m_spawns.back();
}

gfx::scene::model::SpawnModel* gfx::scene::Scene::getSpawn(uint32_t id)
{
	return getModel(m_spawns, id);
}

void gfx::scene::Scene::resetSpawnColor(uint32_t id, GL::Color color)
{
	auto* spawn = getSpawn(id);
	if (spawn)
		spawn->resetColor(color);
}


GL::Program& gfx::scene::Scene::getPortalShader()
{
	return m_shader_table.getHubShader();
}

gfx::scene::model::PortalModel* gfx::scene::Scene::addPortal(uint32_t id, uint32_t hub_id, uint32_t platform_id)
{
	m_portals.emplace_back(*this, id, hub_id, platform_id);
	return &m_portals.back();
}

gfx::scene::model::PortalModel* gfx::scene::Scene::getPortal(uint32_t id)
{
	return getModel(m_portals, id);
}


GL::Program& gfx::scene::Scene::getTrapShader()
{
	return m_shader_table.getHubShader();
}

gfx::scene::model::TrapModel* gfx::scene::Scene::addTrap(uint32_t id, GL::Color color, uint32_t hub_id, uint32_t platform_id)
{
	m_traps.emplace_back(*this, id, color, hub_id, platform_id);
	return &m_traps.back();
}

gfx::scene::model::TrapModel* gfx::scene::Scene::getTrap(uint32_t id)
{
	return getModel(m_traps, id);
}

void gfx::scene::Scene::removeTrap(uint32_t id)
{
	removeModel(m_traps, id);
}


GL::Program& gfx::scene::Scene::getCreatureShader()
{
	return m_shader_table.getHubShader();
}

gfx::scene::model::CreatureModel* gfx::scene::Scene::addCreature(uint32_t id, uint64_t seed, GL::Color color, uint32_t hub_id, uint32_t platform_id)
{
	m_creatures.emplace_back(*this, id, seed, color, hub_id, platform_id);
	return &m_creatures.back();
}

gfx::scene::model::CreatureModel* gfx::scene::Scene::getCreature(uint32_t id)
{
	return getModel(m_creatures, id);
}

void gfx::scene::Scene::removeCreature(uint32_t id)
{
	removeModel(m_creatures, id);
}

void gfx::scene::Scene::moveCreature(uint32_t id, uint32_t target_hub_id, uint32_t target_platform_id)
{
	// TODO: ADD EITHER JUMP OR TRANSPORT ANIMATION
}
