/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "gfx/scene/model/Model.hpp"

gfx::scene::model::Model::Model(uint32_t id) :
	m_id(id),
	m_position(0.f, 0.f, 0.f),
	m_rotation(0.f, 0.f, 0.f),
	m_scale(1.f, 1.f, 1.f),
	m_dirty(true)
{
}

uint32_t gfx::scene::model::Model::getID() const
{
	return m_id;
}

void gfx::scene::model::Model::setPosition(GL::Vec3 position)
{
	m_position = position;
	m_dirty = true;
}

GL::Vec3 gfx::scene::model::Model::getPosition() const
{
	return m_position;
}

void gfx::scene::model::Model::setRotation(GL::Vec3 rotation)
{
	m_rotation = rotation;
	m_dirty = true;
}

GL::Vec3 gfx::scene::model::Model::getRotation() const
{
	return m_rotation;
}

void gfx::scene::model::Model::setScale(GL::Vec3 scale)
{
	m_scale = scale;
	m_dirty = true;
}

GL::Vec3 gfx::scene::model::Model::getScale() const
{
	return m_scale;
}

void gfx::scene::model::Model::getMatrices(GL::Mat4& world, GL::Mat4& normal) const
{
	if (m_dirty)
	{
		// set translation
		GL::Mat4 translation;
		translation.Translate(m_position);

		// set rotation
		GL::Mat4 rotation;
		rotation.RotateX(m_rotation.X);
		rotation.RotateY(m_rotation.Y);
		rotation.RotateZ(m_rotation.Z);

		// set scale
		GL::Mat4 scale;
		scale.Scale(m_scale);

		m_world_mat = translation * rotation * scale;
		m_normal_mat = rotation;
		m_dirty = false;
	}

	world = m_world_mat;
	normal = m_normal_mat;
}

gfx::core::Mesh& gfx::scene::model::Model::getMesh()
{
	return m_mesh;
}

gfx::scene::animator::Animator& gfx::scene::model::Model::getAnimator()
{
	return m_animator;
}

void gfx::scene::model::Model::animate(animator::Animator::Type type)
{
	m_animator.start(type, this);
}

void gfx::scene::model::Model::animate(float elapsed_time)
{
	m_animator.update(elapsed_time, this);
}
