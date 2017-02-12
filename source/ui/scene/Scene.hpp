/*
 * Copyright (C) G�bor G�rzs�ny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <map>
#include <memory>
#include <vector>
#include <GL/Math/Vec3.hpp>
#include <GL/Math/Mat4.hpp>
#include <GL/GL/Context.hpp>
#include <GL/GL/Program.hpp>
#include <raz/timer.hpp>
#include "common/stringhash.hpp"
#include "ui/scene/Camera.hpp"
#include "ui/scene/model/Model.hpp"

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
		const GL::Program& getShader(uint32_t shader) const;
		void render();

	private:
		GL::Context& m_gl;
		Camera m_cam;
		std::map<uint32_t, GL::Program> m_shaders;
		std::vector<std::unique_ptr<model::Model>> m_hubs;
	};
}
}

constexpr uint32_t operator"" _shader(const char* str, size_t)
{
	return (uint32_t)common::stringhash(str);
}
