/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <GL/Window/Event.hpp>
#include <GL/Math/Vec2.hpp>
#include "common/InputHelper.hpp"

namespace gfx
{
namespace scene
{
	class Scene;

	class CameraManager
	{
	public:
		CameraManager();
		bool feed(const GL::Event& ev, const common::InputHelper& helper);
		void update(Scene& scene);

	private:
		GL::Vec2 m_cam_movement;
		GL::Vec2 m_cam_prev_movement;
		GL::Vec2 m_cam_rotation;
		float m_cam_zoom;
	};
}
}
