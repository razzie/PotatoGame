/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <ctime>
#include <GL/Math/Util.hpp>
#include "common/ColorGenerator.hpp"
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
	m_creatures(m_memory),
	m_appear_anims(m_memory)
{
	m_cam.setPosition({ -8, 8, -8 });

	raz::Random random((uint64_t)std::time(NULL));
	common::ColorGenerator color_gen;
	GL::Color color = color_gen[random(0u, 23u)];

	addHub(0, random(), 6, GL::Vec2());
	addHub(1, random(), 8, GL::Vec2(30.f, 0.f));
	//changeHubColor(0, color);

	addCreature(0, random(), color, 0, 0);
	addCreature(1, random(), color, 0, 1);
	addCreature(2, random(), color, 0, 2);

	addCharge(0, 0, 3);
	addResource(0, 5, 0, 4);
	addTrap(0, color, 0, 5);

	addTransport(0, 0, 25, 1, 60);

	m_timer.reset();
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

bool gfx::scene::Scene::getHubPlatform(uint32_t hub_id, uint32_t platform_id, model::HubModel*& hub, const model::HubModel::Platform*& platform)
{
	hub = getHub(hub_id);
	if (!hub)
		return false;

	platform = hub->getPlatform(platform_id);
	if (!platform)
		return false;

	return true;
}

bool gfx::scene::Scene::getHubPlatformPosition(uint32_t hub_id, uint32_t platform_id, GL::Vec3& position)
{
	//auto* hub = getHub(hub_id);
	//if (!hub)
	//	return false;

	//auto* platform = hub->getPlatform(platform_id);
	//if (!platform)
	//	return false;

	model::HubModel* hub;
	const model::HubModel::Platform* platform;

	if (!getHubPlatform(hub_id, platform_id, hub, platform))
		return false;

	position = platform->center + hub->getPosition();
	return true;
}

bool gfx::scene::Scene::feed(const GL::Event& ev)
{
	auto& helper = m_render_thread.getInputHelper();

	if (m_cam_mgr.feed(ev, helper))
	{
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

	m_cam_mgr.update(*this);

	for (auto& anim : m_appear_anims)
		anim.update(m_time);

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

gfx::scene::model::HubModel* gfx::scene::Scene::addHub(uint32_t id, uint64_t seed, uint32_t size, GL::Vec2 position)
{
	m_hubs.emplace_back(*this, id, seed, size, position);
	auto* hub = &m_hubs.back();

	m_appear_anims.push_back(hub);

	return hub;
}

gfx::scene::model::HubModel* gfx::scene::Scene::getHub(uint32_t id)
{
	return getModel(m_hubs, id);
}

void gfx::scene::Scene::changeHubColor(uint32_t id, GL::Color color)
{
	auto* hub = getHub(id);
	if (hub)
		hub->changeColor(color);
}


GL::Program& gfx::scene::Scene::getTransportShader()
{
	return m_shader_table.getEntityShader();
}

gfx::scene::model::TransportModel* gfx::scene::Scene::addTransport(uint32_t id, uint32_t hub1_id, uint32_t hub1_platform_id, uint32_t hub2_id, uint32_t hub2_platform_id)
{
	m_transports.emplace_back(*this, id, hub1_id, hub1_platform_id, hub2_id, hub2_platform_id);
	auto* transport = &m_transports.back();

	m_appear_anims.push_back(transport);

	return transport;
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
	auto* charge = &m_charges.back();

	m_appear_anims.push_back(charge);

	return charge;
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
	auto* resource = &m_resources.back();

	m_appear_anims.push_back(resource);

	return resource;
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
	return m_shader_table.getEntityShader();
}

gfx::scene::model::TraceModel* gfx::scene::Scene::addTrace(uint32_t id, GL::Color color, uint32_t hub_id, uint32_t platform_id)
{
	m_traces.emplace_back(*this, id, color, hub_id, platform_id);
	auto* trace = &m_traces.back();

	m_appear_anims.push_back(trace);

	return trace;
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
	return m_shader_table.getEntityShader();
}

gfx::scene::model::SpawnModel* gfx::scene::Scene::addSpawn(uint32_t id, GL::Color color, uint32_t hub_id, uint32_t platform_id)
{
	m_spawns.emplace_back(*this, id, color, hub_id, platform_id);
	auto* spawn = &m_spawns.back();

	m_appear_anims.push_back(spawn);

	return spawn;
}

gfx::scene::model::SpawnModel* gfx::scene::Scene::getSpawn(uint32_t id)
{
	return getModel(m_spawns, id);
}

void gfx::scene::Scene::changeSpawnColor(uint32_t id, GL::Color color)
{
	auto* spawn = getSpawn(id);
	if (spawn)
		spawn->changeColor(color);
}


GL::Program& gfx::scene::Scene::getPortalShader()
{
	return m_shader_table.getEntityShader();
}

gfx::scene::model::PortalModel* gfx::scene::Scene::addPortal(uint32_t id, uint32_t hub_id, uint32_t platform_id)
{
	m_portals.emplace_back(*this, id, hub_id, platform_id);
	auto* portal = &m_portals.back();

	m_appear_anims.push_back(portal);

	return portal;
}

gfx::scene::model::PortalModel* gfx::scene::Scene::getPortal(uint32_t id)
{
	return getModel(m_portals, id);
}


GL::Program& gfx::scene::Scene::getTrapShader()
{
	return m_shader_table.getEntityShader();
}

gfx::scene::model::TrapModel* gfx::scene::Scene::addTrap(uint32_t id, GL::Color color, uint32_t hub_id, uint32_t platform_id)
{
	m_traps.emplace_back(*this, id, color, hub_id, platform_id);
	auto* trap = &m_traps.back();

	m_appear_anims.push_back(trap);

	return trap;
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
	return m_shader_table.getEntityShader();
}

gfx::scene::model::CreatureModel* gfx::scene::Scene::addCreature(uint32_t id, uint64_t seed, GL::Color color, uint32_t hub_id, uint32_t platform_id)
{
	m_creatures.emplace_back(*this, id, seed, color, hub_id, platform_id);
	auto* creature = &m_creatures.back();

	m_appear_anims.push_back(creature);

	return creature;
}

gfx::scene::model::CreatureModel* gfx::scene::Scene::getCreature(uint32_t id)
{
	return getModel(m_creatures, id);
}

void gfx::scene::Scene::moveCreature(uint32_t id, uint32_t target_hub_id, uint32_t target_platform_id)
{
	// TODO: ADD EITHER JUMP OR TRANSPORT ANIMATION
}

void gfx::scene::Scene::changeCreatureColor(uint32_t id, GL::Color color)
{
	auto* creature = getCreature(id);
	if (creature)
		creature->changeColor(color);
}

void gfx::scene::Scene::removeCreature(uint32_t id)
{
	removeModel(m_creatures, id);
}
