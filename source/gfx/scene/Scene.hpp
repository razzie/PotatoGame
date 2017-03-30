/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <vector>
#include <GL/Math/Mat4.hpp>
#include <GL/GL/Context.hpp>
#include <GL/GL/Program.hpp>
#include <GL/Window/Event.hpp>
#include <raz/memory.hpp>
#include <raz/timer.hpp>
#include "gfx/core/ShaderTable.hpp"
#include "gfx/scene/Camera.hpp"
#include "gfx/scene/CameraManager.hpp"
#include "gfx/scene/Horizon.hpp"
#include "gfx/scene/model/HubModel.hpp"
#include "gfx/scene/model/TransportModel.hpp"
#include "gfx/scene/model/ChargeModel.hpp"
#include "gfx/scene/model/ResourceModel.hpp"
#include "gfx/scene/model/TraceModel.hpp"
#include "gfx/scene/model/SpawnModel.hpp"
#include "gfx/scene/model/PortalModel.hpp"
#include "gfx/scene/model/TrapModel.hpp"
#include "gfx/scene/model/CreatureModel.hpp"
#include "gfx/scene/animator/AppearAnimator.hpp"

namespace gfx
{
class RenderThread;

namespace scene
{
	class Scene
	{
	public:
		Scene(RenderThread& render_thread);
		~Scene();
		GL::Context& getContext();
		raz::IMemoryPool* getMemoryPool();
		Camera& getCamera();
		const Camera& getCamera() const;
		const GL::Mat4& getCameraMatrix() const;
		GL::Program& getCurrentShader();
		float getElapsedTime() const;
		bool getHubPlatform(uint32_t hub_id, uint32_t platform_id, model::HubModel*& hub, const model::HubModel::Platform*& platform);
		bool getHubPlatformPosition(uint32_t hub_id, uint32_t platform_id, GL::Vec3& position);
		bool feed(const GL::Event& ev);
		void render();
		void reset();

		// hub
		GL::Program& getHubShader();
		model::HubModel* addHub(uint32_t id, uint64_t seed, uint32_t size, GL::Vec2 position);
		model::HubModel* getHub(uint32_t id);
		void changeHubColor(uint32_t id, GL::Color color);

		// transport
		GL::Program& getTransportShader();
		model::TransportModel* addTransport(uint32_t id, uint32_t hub1_id, uint32_t hub1_platform_id, uint32_t hub2_id, uint32_t hub2_platform_id);
		model::TransportModel* getTransport(uint32_t id);

		// charge
		GL::Program& getChargeShader();
		model::ChargeModel* addCharge(uint32_t id, uint32_t hub_id, uint32_t platform_id);
		model::ChargeModel* getCharge(uint32_t id);
		void removeCharge(uint32_t id);

		// resource
		GL::Program& getResourceShader();
		model::ResourceModel* addResource(uint32_t id, uint32_t value, uint32_t hub_id, uint32_t platform_id);
		model::ResourceModel* getResource(uint32_t id);
		void removeResource(uint32_t id);

		// trace
		GL::Program& getTraceShader();
		model::TraceModel* addTrace(uint32_t id, GL::Color color, uint32_t hub_id, uint32_t platform_id);
		model::TraceModel* getTrace(uint32_t id);
		void removeTrace(uint32_t id);

		// spawn
		GL::Program& getSpawnShader();
		model::SpawnModel* addSpawn(uint32_t id, GL::Color color, uint32_t hub_id, uint32_t platform_id);
		model::SpawnModel* getSpawn(uint32_t id);
		void changeSpawnColor(uint32_t id, GL::Color color);

		// portal
		GL::Program& getPortalShader();
		model::PortalModel* addPortal(uint32_t id, uint32_t hub_id, uint32_t platform_id);
		model::PortalModel* getPortal(uint32_t id);

		// trap
		GL::Program& getTrapShader();
		model::TrapModel* addTrap(uint32_t id, GL::Color color, uint32_t hub_id, uint32_t platform_id);
		model::TrapModel* getTrap(uint32_t id);
		void removeTrap(uint32_t id);

		// creature
		GL::Program& getCreatureShader();
		model::CreatureModel* addCreature(uint32_t id, uint64_t seed, GL::Color color, uint32_t hub_id, uint32_t platform_id);
		model::CreatureModel* getCreature(uint32_t id);
		void moveCreature(uint32_t id, uint32_t target_hub_id, uint32_t target_platform_id);
		void changeCreatureColor(uint32_t id, GL::Color color);
		void removeCreature(uint32_t id);

	private:
		template<class T>
		using Vector = std::vector<T, raz::Allocator<T>>;

		RenderThread& m_render_thread;
		GL::Context& m_gl;
		raz::IMemoryPool* m_memory;
		gfx::core::ShaderTable& m_shader_table;
		GL::Program* m_current_shader;
		raz::Timer m_timer;
		float m_time;
		Camera m_cam;
		CameraManager m_cam_mgr;
		Horizon m_horizon;
		Vector<model::HubModel> m_hubs;
		Vector<model::TransportModel> m_transports;
		Vector<model::ChargeModel> m_charges;
		Vector<model::ResourceModel> m_resources;
		Vector<model::TraceModel> m_traces;
		Vector<model::SpawnModel> m_spawns;
		Vector<model::PortalModel> m_portals;
		Vector<model::TrapModel> m_traps;
		Vector<model::CreatureModel> m_creatures;
		Vector<animator::AppearAnimator> m_appear_anims;
	};
}
}
