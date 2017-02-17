/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <map>
#include <vector>
#include <GL/Math/Vec3.hpp>
#include <GL/Math/Mat4.hpp>
#include <GL/GL/Context.hpp>
#include <GL/GL/Program.hpp>
#include <raz/timer.hpp>
#include "common/stringhash.hpp"
#include "ui/scene/Camera.hpp"
#include "ui/scene/model/HubModel.hpp"
#include "ui/scene/model/CreatureModel.hpp"

namespace ui
{
namespace scene
{
	class Scene
	{
	public:
		Scene(GL::Context& gl);
		Scene(const Scene&) = delete;
		~Scene();
		Scene& operator=(const Scene&) = delete;
		GL::Context& getContext();
		Camera& getCamera();
		const Camera& getCamera() const;
		const GL::Mat4& getCameraMatrix() const;
		GL::Program& getShader(uint32_t shader);
		GL::Program& getCurrentShader();
		void render();

	private:
		GL::Context& m_gl;
		Camera m_cam;
		std::map<uint32_t, GL::Program> m_shaders;
		GL::Program* m_current_shader;
		std::vector<model::HubModel, raz::Allocator<model::HubModel>> m_hubs;
		std::vector<model::CreatureModel, raz::Allocator<model::CreatureModel>> m_creatures;
	};
}
}

constexpr uint32_t operator"" _shader(const char* str, size_t)
{
	return (uint32_t)common::stringhash(str);
}
