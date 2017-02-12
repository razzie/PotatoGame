/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <GL/Math/Util.hpp>
#include "ui/scene/Camera.hpp"
#include "common/equals.hpp"
#include "common/Quaternion.hpp"

ui::scene::Camera::Camera(float aspect_ratio) :
	m_position(1, 1, 1),
	m_target(0, 0, 0),
	m_dirty(true)
{
	m_proj = GL::Mat4::Perspective(GL::Rad(90), aspect_ratio, 0.1f, 1000.0f);
}

ui::scene::Camera::Camera(float aspect_ratio, GL::Vec3 position, GL::Vec3 target) :
	m_position(position),
	m_target(target),
	m_dirty(false)
{
	m_proj = GL::Mat4::Perspective(GL::Rad(90), aspect_ratio, 0.1f, 1000.0f);
}

ui::scene::Camera::~Camera()
{
}

GL::Vec3 ui::scene::Camera::getPosition() const
{
	return m_position;
}

void ui::scene::Camera::setPosition(GL::Vec3 position)
{
	m_position = position;
	m_dirty = true;
}

GL::Vec3 ui::scene::Camera::getTarget() const
{
	return m_target;
}

void ui::scene::Camera::setTarget(GL::Vec3 target)
{
	m_target = target;
	m_dirty = true;
}

const GL::Mat4& ui::scene::Camera::getMatrix() const
{
	if (m_dirty)
	{
		GL::Mat4 view = GL::Mat4::LookAt(m_position, m_target, GL::Vec3(0, 1, 0));
		m_cam_matrix = m_proj * view;
		m_dirty = false;
	}

	return m_cam_matrix;
}

void ui::scene::Camera::zoom(float rate)
{
	GL::Vec3 direction = (m_target - m_position).Normal() * rate;
	m_position += direction;
	m_dirty = true;
}

void ui::scene::Camera::move(float axial, float lateral)
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

void ui::scene::Camera::rotate(float horizontal, float vertical)
{
	GL::Vec3 pos = m_position;
	pos -= m_target;

	if (!common::equals(horizontal, 0.f))
	{
		common::rotateVectorAroundAxis(pos, GL::Vec3(0.f, 1.f, 0.f), GL::Rad(horizontal));
	}

	if (!common::equals(vertical, 0.f))
	{
		GL::Vec3 right = GL::Vec3(0.f, 1.f, 0.f).Cross(m_target - m_position).Normal();
		common::rotateVectorAroundAxis(pos, right, GL::Rad(vertical));
	}

	pos += m_target;
	m_position = pos;
	m_dirty = true;
}
