/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <GL/Math/Util.hpp>
#include "ui/core/SimpleShader.hpp"
#include "ui/core/HubShader.hpp"
#include "ui/scene/Scene.hpp"
#include "ui/scene/model/HubModel.hpp"

ui::scene::Scene::Scene(GL::Context& gl) :
	m_gl(gl),
	m_cam(1024.f / 768.f)
{
	m_shaders.emplace("simple"_shader, core::SimpleShader().getProgram());
	m_shaders.emplace("hub"_shader, core::HubShader().getProgram());

	m_hubs.emplace_back(new model::HubModel(*this));
}

ui::scene::Scene::~Scene()
{
}

GL::Context& ui::scene::Scene::getContext()
{
	return m_gl;
}

ui::scene::Camera& ui::scene::Scene::getCamera()
{
	return m_cam;
}

const ui::scene::Camera& ui::scene::Scene::getCamera() const
{
	return m_cam;
}

const GL::Mat4& ui::scene::Scene::getCameraMatrix() const
{
	return m_cam.getMatrix();
}

const GL::Program& ui::scene::Scene::getShader(uint32_t shader) const
{
	auto it = m_shaders.find(shader);
	if (it == m_shaders.end())
		throw std::runtime_error("no such shader exists");

	return it->second;
}

void ui::scene::Scene::render()
{
	m_gl.UseProgram(m_shaders["hub"_shader]);
	for (auto& hub : m_hubs)
		hub->render(*this);
}
