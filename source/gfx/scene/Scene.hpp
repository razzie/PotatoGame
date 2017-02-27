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
#include <raz/memory.hpp>
#include <raz/timer.hpp>
#include "gfx/core/ShaderTable.hpp"
#include "gfx/scene/Camera.hpp"
#include "gfx/scene/model/HubModel.hpp"
#include "gfx/scene/model/CreatureModel.hpp"

namespace gfx
{
namespace scene
{
	class Scene
	{
	public:
		Scene(GL::Context& gl, gfx::core::ShaderTable& shader_table);
		Scene(const Scene&) = delete;
		~Scene();
		Scene& operator=(const Scene&) = delete;
		GL::Context& getContext();
		raz::IMemoryPool* getMemoryPool();
		Camera& getCamera();
		const Camera& getCamera() const;
		const GL::Mat4& getCameraMatrix() const;
		GL::Program& getCurrentShader();
		void render();

		// hub functions
		GL::Program& getHubShader();
		model::HubModel* getHub(uint32_t id);

		// creature functions
		GL::Program& getCreatureShader();
		model::CreatureModel* getCreature(uint32_t id);

	private:
		template<class T>
		using Vector = std::vector<T, raz::Allocator<T>>;

		GL::Context& m_gl;
		gfx::core::ShaderTable& m_shader_table;
		GL::Program* m_current_shader;
		Camera m_cam;
		Vector<model::HubModel> m_hubs;
		Vector<model::CreatureModel> m_creatures;
	};
}
}
