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
#include "gfx/scene/PostFX.hpp"
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
		PostFX::GBuffer& getGBuffer();
		Camera& getCamera();
		const Camera& getCamera() const;
		float getElapsedTime() const;
		bool getHubPlatform(uint32_t hub_id, uint32_t platform_id, model::HubModel*& hub, const model::HubModel::Platform*& platform);
		bool getHubPlatformPosition(uint32_t hub_id, uint32_t platform_id, GL::Vec3& position);
		bool feed(const GL::Event& ev);
		void render();
		void reset();

		// hub
		model::HubModel* addHub(uint32_t id, uint64_t seed, uint32_t size, GL::Vec2 position);
		model::HubModel* getHub(uint32_t id);
		void changeHubColor(uint32_t id, GL::Color color);

		// transport
		model::TransportModel* addTransport(uint32_t id, uint32_t hub1_id, uint32_t hub1_platform_id, uint32_t hub2_id, uint32_t hub2_platform_id);
		model::TransportModel* getTransport(uint32_t id);

		// charge
		model::ChargeModel* addCharge(uint32_t id, uint32_t hub_id, uint32_t platform_id);
		model::ChargeModel* getCharge(uint32_t id);
		void removeCharge(uint32_t id);

		// resource
		model::ResourceModel* addResource(uint32_t id, uint32_t value, uint32_t hub_id, uint32_t platform_id);
		model::ResourceModel* getResource(uint32_t id);
		void removeResource(uint32_t id);

		// trace
		model::TraceModel* addTrace(uint32_t id, GL::Color color, uint32_t hub_id, uint32_t platform_id);
		model::TraceModel* getTrace(uint32_t id);
		void removeTrace(uint32_t id);

		// spawn
		model::SpawnModel* addSpawn(uint32_t id, GL::Color color, uint32_t hub_id, uint32_t platform_id);
		model::SpawnModel* getSpawn(uint32_t id);
		void changeSpawnColor(uint32_t id, GL::Color color);

		// portal
		model::PortalModel* addPortal(uint32_t id, uint32_t hub_id, uint32_t platform_id);
		model::PortalModel* getPortal(uint32_t id);

		// trap
		model::TrapModel* addTrap(uint32_t id, GL::Color color, uint32_t hub_id, uint32_t platform_id);
		model::TrapModel* getTrap(uint32_t id);
		void removeTrap(uint32_t id);

		// creature
		model::CreatureModel* addCreature(uint32_t id, uint64_t seed, GL::Color color, uint32_t hub_id, uint32_t platform_id);
		model::CreatureModel* getCreature(uint32_t id);
		void moveCreature(uint32_t id, uint32_t target_hub_id, uint32_t target_platform_id);
		void changeCreatureColor(uint32_t id, GL::Color color);
		void removeCreature(uint32_t id);

	private:
		template<class T>
		using Vector = std::vector<T, raz::Allocator<T>>;

		template<class T>
		struct ModelContainer
		{
			typename T::MaterialType material;
			Vector<T> models;

			template<class... Args>
			ModelContainer(raz::IMemoryPool* memory, Args... args) :
				material(std::forward<Args>(args)...),
				models(memory)
			{
			}

			template<class... Args>
			T* add(Scene& scene, Args... args)
			{
				models.emplace_back(scene, std::forward<Args>(args)...);
				T* model = &models.back();
				model->getMesh().bindShader(material.shader);
				model->animate(animator::AnimatorType::APPEAR, scene.getElapsedTime());
				return model;
			}

			T* get(uint32_t id)
			{
				for (auto& model : models)
				{
					if (model.getID() == id)
						return &model;
				}

				return nullptr;
			}

			void remove(uint32_t id)
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

			void clear()
			{
				models.clear();
			}

			void render(Scene& scene)
			{
				GL::Context& gl = scene.getContext();
				gl.UseProgram(material.shader);

				material.time = scene.getElapsedTime();
				material.camera_mat = scene.getCamera().getMatrix();

				for (auto& model : models)
				{
					model.animate(material.time);
					model.render(material, gl);
				}
			}
		};

		RenderThread& m_render_thread;
		GL::Context& m_gl;
		raz::IMemoryPool* m_memory;
		raz::Timer m_timer;
		float m_time;
		PostFX::GBuffer m_gbuffer;
		Camera m_cam;
		CameraManager m_cam_mgr;
		Horizon m_horizon;
		ModelContainer<model::HubModel> m_hubs;
		ModelContainer<model::TransportModel> m_transports;
		ModelContainer<model::ChargeModel> m_charges;
		ModelContainer<model::ResourceModel> m_resources;
		ModelContainer<model::TraceModel> m_traces;
		ModelContainer<model::SpawnModel> m_spawns;
		ModelContainer<model::PortalModel> m_portals;
		ModelContainer<model::TrapModel> m_traps;
		ModelContainer<model::CreatureModel> m_creatures;
	};
}
}
