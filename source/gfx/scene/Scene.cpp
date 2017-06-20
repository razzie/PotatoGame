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
	m_gbuffer(render_thread.getWindow().GetWidth(), render_thread.getWindow().GetHeight()),
	m_cam(render_thread.getAspectRatio(), render_thread.getRenderDistance()),
	m_horizon(m_render_thread.getShaderLoader().get("horizon")),
#define CONTAINER_INIT m_memory, std::ref(m_render_thread.getShaderLoader())
	m_hubs(CONTAINER_INIT),
	m_transports(CONTAINER_INIT),
	m_charges(CONTAINER_INIT),
	m_resources(CONTAINER_INIT),
	m_traces(CONTAINER_INIT),
	m_spawns(CONTAINER_INIT),
	m_portals(CONTAINER_INIT),
	m_traps(CONTAINER_INIT),
	m_creatures(CONTAINER_INIT)
#undef CONTAINER_INIT
{
	m_cam.setPosition({ -8, 8, -8 });
	m_cam.setTarget({ 0, 5, 0 });

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

gfx::scene::PostFX::GBuffer& gfx::scene::Scene::getGBuffer()
{
	return m_gbuffer;
}

gfx::scene::Camera& gfx::scene::Scene::getCamera()
{
	return m_cam;
}

const gfx::scene::Camera& gfx::scene::Scene::getCamera() const
{
	return m_cam;
}

float gfx::scene::Scene::getElapsedTime() const
{
	return m_time;
}

bool gfx::scene::Scene::feed(const GL::Event& ev)
{
	auto& helper = m_render_thread.getInputHelper();

	if (m_cam_mgr.feed(ev, helper))
	{
		return true;
	}
	else if (ev.Type == GL::Event::KeyDown)
	{
		switch (ev.Key.Code)
		{
		case GL::Key::Comma:
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			return true;
		case GL::Key::Period:
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			return true;
		}
	}

	return false;
}

void gfx::scene::Scene::render()
{
	m_time = 0.001f * m_timer.peekElapsed();

	m_cam_mgr.update(*this);

	glDisable(GL_BLEND);

	m_gl.DepthMask(true);
	m_gl.Enable(GL::Capability::DepthTest);

	m_gbuffer.bind();
	m_gl.Clear(GL::Buffer::Color | GL::Buffer::Depth);

	m_horizon.render(*this);

	m_hubs.render(*this);
	m_transports.render(*this);
	m_charges.render(*this);
	m_resources.render(*this);
	m_traces.render(*this);
	m_spawns.render(*this);
	m_portals.render(*this);
	m_traps.render(*this);
	m_creatures.render(*this);
}

void gfx::scene::Scene::reset()
{
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


gfx::scene::model::HubModel* gfx::scene::Scene::addHub(uint32_t id, uint64_t seed, uint32_t size, GL::Vec2 position)
{
	return m_hubs.add(*this, id, seed, size, position);
}

gfx::scene::model::HubModel* gfx::scene::Scene::getHub(uint32_t id)
{
	return m_hubs.get(id);
}

void gfx::scene::Scene::changeHubColor(uint32_t id, GL::Color color)
{
	auto* hub = getHub(id);
	if (hub)
		hub->setColor(color);
}

bool gfx::scene::Scene::getPlatform(uint32_t hub_id, uint32_t platform_id, gfx::shape::PlatformShape& platform) const
{
	auto* hub = m_hubs.get(hub_id);
	if (!hub)
		return false;

	gfx::shape::PlatformShape p;
	if (hub->getPlatform(platform_id, p))
	{
		p.center += hub->getPosition();
		platform = p;
		return true;
	}

	return false;
}


gfx::scene::model::TransportModel* gfx::scene::Scene::addTransport(uint32_t id, uint32_t hub1_id, uint32_t hub1_platform_id, uint32_t hub2_id, uint32_t hub2_platform_id)
{
	return m_transports.add(*this, id, hub1_id, hub1_platform_id, hub2_id, hub2_platform_id);
}

gfx::scene::model::TransportModel* gfx::scene::Scene::getTransport(uint32_t id)
{
	return m_transports.get(id);
}


gfx::scene::model::ChargeModel* gfx::scene::Scene::addCharge(uint32_t id, uint32_t hub_id, uint32_t platform_id)
{
	return m_charges.add(*this, id, hub_id, platform_id);
}

gfx::scene::model::ChargeModel* gfx::scene::Scene::getCharge(uint32_t id)
{
	return m_charges.get(id);
}

void gfx::scene::Scene::removeCharge(uint32_t id)
{
	m_charges.remove(id);
}


gfx::scene::model::ResourceModel* gfx::scene::Scene::addResource(uint32_t id, uint32_t value, uint32_t hub_id, uint32_t platform_id)
{
	return m_resources.add(*this, id, value, hub_id, platform_id);
}

gfx::scene::model::ResourceModel* gfx::scene::Scene::getResource(uint32_t id)
{
	return m_resources.get(id);
}

void gfx::scene::Scene::removeResource(uint32_t id)
{
	m_resources.remove(id);
}


gfx::scene::model::TraceModel* gfx::scene::Scene::addTrace(uint32_t id, GL::Color color, uint32_t hub_id, uint32_t platform_id)
{
	return m_traces.add(*this, id, color, hub_id, platform_id);
}

gfx::scene::model::TraceModel* gfx::scene::Scene::getTrace(uint32_t id)
{
	return m_traces.get(id);
}

void gfx::scene::Scene::removeTrace(uint32_t id)
{
	m_traces.remove(id);
}


gfx::scene::model::SpawnModel* gfx::scene::Scene::addSpawn(uint32_t id, GL::Color color, uint32_t hub_id, uint32_t platform_id)
{
	return m_spawns.add(*this, id, color, hub_id, platform_id);
}

gfx::scene::model::SpawnModel* gfx::scene::Scene::getSpawn(uint32_t id)
{
	return m_spawns.get(id);
}

void gfx::scene::Scene::changeSpawnColor(uint32_t id, GL::Color color)
{
	auto* spawn = getSpawn(id);
	if (spawn)
		spawn->setColor(color);
}


gfx::scene::model::PortalModel* gfx::scene::Scene::addPortal(uint32_t id, uint32_t hub_id, uint32_t platform_id)
{
	return m_portals.add(*this, id, hub_id, platform_id);
}

gfx::scene::model::PortalModel* gfx::scene::Scene::getPortal(uint32_t id)
{
	return m_portals.get(id);
}


gfx::scene::model::TrapModel* gfx::scene::Scene::addTrap(uint32_t id, GL::Color color, uint32_t hub_id, uint32_t platform_id)
{
	return m_traps.add(*this, id, color, hub_id, platform_id);
}

gfx::scene::model::TrapModel* gfx::scene::Scene::getTrap(uint32_t id)
{
	return m_traps.get(id);
}

void gfx::scene::Scene::removeTrap(uint32_t id)
{
	m_traps.remove(id);
}


gfx::scene::model::CreatureModel* gfx::scene::Scene::addCreature(uint32_t id, uint64_t seed, GL::Color color, uint32_t hub_id, uint32_t platform_id)
{
	return m_creatures.add(*this, id, seed, color, hub_id, platform_id);
}

gfx::scene::model::CreatureModel* gfx::scene::Scene::getCreature(uint32_t id)
{
	return m_creatures.get(id);
}

void gfx::scene::Scene::moveCreature(uint32_t id, uint32_t target_hub_id, uint32_t target_platform_id)
{
	// TODO: ADD EITHER JUMP OR TRANSPORT ANIMATION
}

void gfx::scene::Scene::changeCreatureColor(uint32_t id, GL::Color color)
{
	auto* creature = getCreature(id);
	if (creature)
		creature->setColor(color);
}

void gfx::scene::Scene::removeCreature(uint32_t id)
{
	m_creatures.remove(id);
}
