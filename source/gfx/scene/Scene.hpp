/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <vector>
#include <GL/Math/Mat4.hpp>
#include <GL/GL/Context.hpp>
#include <GL/Window/Event.hpp>
#include <raz/memory.hpp>
#include "gfx/model/ModelRenderer.hpp"
#include "gfx/scene/FreeCameraController.hpp"
#include "gfx/model/Horizon.hpp"
#include "gfx/model/HubModel.hpp"
#include "gfx/model/TransportModel.hpp"
#include "gfx/model/ChargeModel.hpp"
#include "gfx/model/ResourceModel.hpp"
#include "gfx/model/TraceModel.hpp"
#include "gfx/model/SpawnModel.hpp"
#include "gfx/model/PortalModel.hpp"
#include "gfx/model/TrapModel.hpp"
#include "gfx/model/CreatureModel.hpp"

namespace gfx
{
class RenderThread;

namespace scene
{
	class Scene : public gfx::model::ModelRenderer
	{
	public:
		Scene(RenderThread& render_thread);
		~Scene();
		raz::IMemoryPool* getMemoryPool();
		bool feed(const GL::Event& ev);
		void render();
		void reset();

		// hub
		model::HubModel* addHub(uint32_t id, uint64_t seed, uint32_t size, GL::Vec2 position);
		model::HubModel* getHub(uint32_t id);
		void changeHubColor(uint32_t id, GL::Color color);
		bool getPlatform(uint32_t hub_id, uint32_t platform_id, gfx::shape::PlatformShape& platform) const;

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
				model->animate(gfx::model::animator::AnimatorType::APPEAR, scene.getElapsedTime());
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

			const T* get(uint32_t id) const
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

				for (auto it = models.begin(); it != models.end(); )
				{
					it->animate(material.time);
					it->render(material, gl);

					if (it->getFlag(model::ModelFlag::REMOVE))
						it = models.erase(it);
					else
						++it;
				}
			}
		};

		RenderThread& m_render_thread;
		raz::IMemoryPool* m_memory;
		FreeCameraController m_cam_mgr;
		model::Horizon m_horizon;
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
