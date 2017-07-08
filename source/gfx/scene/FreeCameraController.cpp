/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "common/equals.hpp"
#include "common/GLlerp.hpp"
#include "gfx/scene/Scene.hpp"
#include "gfx/scene/FreeCameraController.hpp"

gfx::scene::FreeCameraController::FreeCameraController() :
	m_cam_movement(0.f, 0.f),
	m_cam_prev_movement(0.f, 0.f),
	m_cam_rotation(0.f, 0.f),
	m_cam_zoom(0.f)
{
}

bool gfx::scene::FreeCameraController::feed(const GL::Event& ev, const common::InputHelper& helper)
{
	if (ev.Type == GL::Event::KeyDown)
	{
		const float speed = 0.5f;

		switch (ev.Key.Code)
		{
		case GL::Key::W:
			m_cam_movement.X = speed;
			return true;
		case GL::Key::S:
			m_cam_movement.X = -speed;
			return true;
		case GL::Key::A:
			m_cam_movement.Y = -speed;
			return true;
		case GL::Key::D:
			m_cam_movement.Y = speed;
			return true;
		}
	}
	if (ev.Type == GL::Event::KeyUp)
	{
		switch (ev.Key.Code)
		{
		case GL::Key::W:
		case GL::Key::S:
			m_cam_movement.X = 0.f;
			return true;
		case GL::Key::A:
		case GL::Key::D:
			m_cam_movement.Y = 0.f;
			return true;
		}
	}
	else if (ev.Type == GL::Event::MouseMove)
	{
		if (helper.isLeftMouseButtonDown() || helper.isRightMouseButtonDown())
		{
			const float speed = 0.1f;
			auto delta = helper.getMouseDelta();
			m_cam_rotation.X -= speed * delta.x;
			m_cam_rotation.Y += speed * delta.y;
			return true;
		}
	}
	else if (ev.Type == GL::Event::MouseWheel)
	{
		m_cam_zoom += (ev.Mouse.Delta > 0) ? 0.5f : -0.5f;
		return true;
	}

	return false;
}

void gfx::scene::FreeCameraController::update(Scene& scene)
{
	auto& cam = scene.getCamera();

	cam.move(m_cam_prev_movement.X, m_cam_prev_movement.Y);
	cam.rotate(m_cam_rotation.X, m_cam_rotation.Y);
	cam.zoom(m_cam_zoom);

	m_cam_prev_movement = common::lerp(m_cam_movement, m_cam_prev_movement, 0.9f);
	m_cam_rotation = m_cam_rotation * 0.9f;
	m_cam_zoom = m_cam_zoom * 0.9f;
}
