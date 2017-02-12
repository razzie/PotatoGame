/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <GL/Math/Vec3.hpp>
#include <GL/Math/Mat4.hpp>

namespace ui
{
namespace scene
{
	class Camera
	{
	public:
		Camera(float aspect_ratio);
		Camera(float aspect_ratio, GL::Vec3 position, GL::Vec3 target);
		Camera(const Camera&) = delete;
		~Camera();
		Camera& operator=(const Camera&) = delete;
		GL::Vec3 getPosition() const;
		void setPosition(GL::Vec3 position);
		GL::Vec3 getTarget() const;
		void setTarget(GL::Vec3 target);
		const GL::Mat4& getMatrix() const;
		void zoom(float rate);
		void move(float axial, float lateral);
		void rotate(float horizontal, float vertical);

	private:
		GL::Vec3 m_position;
		GL::Vec3 m_target;
		GL::Mat4 m_proj;
		mutable GL::Mat4 m_cam_matrix;
		mutable bool m_dirty;
	};
}
}
