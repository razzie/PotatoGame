/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <GL/Math/Util.hpp>
#include "gfx/core/Camera.hpp"
#include "common/equals.hpp"
#include "common/PI.hpp"
#include "common/Quaternion.hpp"

gfx::core::Camera::Camera(float aspect_ratio, float max_depth) :
	Camera(aspect_ratio, max_depth, GL::Vec3(1.f, 1.f, 1.f), GL::Vec3(0.f, 0.f, 0.f))
{
}

gfx::core::Camera::Camera(float aspect_ratio, float render_distance, GL::Vec3 position, GL::Vec3 target) :
	m_aspect_ratio(aspect_ratio),
	m_render_distance(render_distance),
	m_position(position),
	m_target(target),
	m_dirty(true)
{
	m_proj = GL::Mat4::Perspective(GL::Rad(60), m_aspect_ratio, 0.1f, m_render_distance);
}

gfx::core::Camera::~Camera()
{
}

float gfx::core::Camera::getAspectRatio() const
{
	return m_aspect_ratio;
}

void gfx::core::Camera::setAspectRatio(float aspect_ratio)
{
	m_aspect_ratio = aspect_ratio;
	m_proj = GL::Mat4::Perspective(GL::Rad(90), m_aspect_ratio, 0.1f, m_render_distance);
	m_dirty = true;
}

float gfx::core::Camera::getRenderDistance() const
{
	return m_render_distance;
}

void gfx::core::Camera::setRenderDistance(float render_distance)
{
	m_render_distance = render_distance;
	m_proj = GL::Mat4::Perspective(GL::Rad(90), m_aspect_ratio, 0.1f, m_render_distance);
	m_dirty = true;
}

GL::Vec3 gfx::core::Camera::getPosition() const
{
	return m_position;
}

void gfx::core::Camera::setPosition(GL::Vec3 position)
{
	m_position = position;
	m_dirty = true;
}

GL::Vec3 gfx::core::Camera::getTarget() const
{
	return m_target;
}

void gfx::core::Camera::setTarget(GL::Vec3 target)
{
	m_target = target;
	m_dirty = true;
}

const GL::Mat4& gfx::core::Camera::getMatrix() const
{
	if (m_dirty)
	{
		GL::Mat4 view = GL::Mat4::LookAt(m_position, m_target, GL::Vec3(0, 1, 0));
		m_cam_matrix = m_proj * view;
		m_dirty = false;
	}

	return m_cam_matrix;
}

void gfx::core::Camera::zoom(float rate)
{
	GL::Vec3 direction = m_target - m_position;
	float direction_len = direction.Length();

	if (rate > direction_len - 1.f)
		rate = direction_len - 1.f;

	GL::Vec3 movement = (direction * rate) / direction_len;
	m_position += movement;
	m_dirty = true;
}

void gfx::core::Camera::move(float axial, float lateral)
{
	GL::Vec3 movement;
	GL::Vec3 direction = m_target - m_position;
	direction.Y = 0.f;
	direction = direction.Normal();

	if (!common::equals(axial, 0.f))
	{
		movement += direction * axial;
	}

	if (!common::equals(lateral, 0.f))
	{
		movement += GL::Vec3(-direction.Z, 0.f, direction.X) * lateral;
	}

	m_position += movement;
	m_target += movement;
	m_dirty = true;
}

void gfx::core::Camera::rotate(float horizontal, float vertical)
{
	GL::Vec3 pos = m_position;
	pos -= m_target;

	if (!common::equals(horizontal, 0.f))
	{
		common::rotateVectorAroundAxis(pos, GL::Vec3(0.f, 1.f, 0.f), GL::Rad(horizontal));
	}

	if (!common::equals(vertical, 0.f))
	{
		vertical = GL::Rad(vertical);

		const float pitch = std::acos(pos.Normal().Y);
		if (vertical > pitch - 0.01f)
			vertical = pitch - 0.01f;
		else if (vertical < pitch - 0.5f * (float)common::PI)
			vertical = pitch - 0.5f * (float)common::PI;

		GL::Vec3 right = GL::Vec3(0.f, 1.f, 0.f).Cross(m_target - m_position).Normal();
		common::rotateVectorAroundAxis(pos, right, vertical);
	}

	pos += m_target;
	m_position = pos;
	m_dirty = true;
}
