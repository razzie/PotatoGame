/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <cstdint>
#include <GL/Math/Vec3.hpp>
#include <GL/Math/Mat4.hpp>
#include "gfx/core/Mesh.hpp"
#include "gfx/core/Material.hpp"
#include "gfx/model/ModelFlag.hpp"
#include "gfx/model/animator/Animator.hpp"

namespace gfx
{
namespace model
{
	template<class Material = gfx::core::EntityMaterial>
	class Model
	{
	public:
		typedef Material MaterialType;

		Model(uint32_t id) :
			m_id(id),
			m_position(0.f, 0.f, 0.f),
			m_rotation(0.f, 0.f, 0.f),
			m_scale(1.f, 1.f, 1.f),
			m_dirty(true),
			m_color(255, 255, 255),
			m_flags(0)
		{
		}

		uint32_t getID() const
		{
			return m_id;
		}

		void setPosition(GL::Vec3 position)
		{
			m_position = position;
			m_dirty = true;
		}

		GL::Vec3 getPosition() const
		{
			return m_position;
		}

		void setRotation(GL::Vec3 rotation)
		{
			m_rotation = rotation;
			m_dirty = true;
		}

		GL::Vec3 getRotation() const
		{
			return m_rotation;
		}

		void setScale(GL::Vec3 scale)
		{
			m_scale = scale;
			m_dirty = true;
		}

		GL::Vec3 getScale() const
		{
			return m_scale;
		}

		void getMatrices(GL::Mat4& world, GL::Mat4& normal) const
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

		void setColor(GL::Color color)
		{
			m_color = color;
		}

		GL::Color getColor() const
		{
			return m_color;
		}

		void setFlag(ModelFlag flag, bool enable = true)
		{
			if (enable)
				m_flags |= flag;
			else
				m_flags &= ~flag;
		}

		bool getFlag(ModelFlag flag) const
		{
			return ((m_flags & flag) != 0);
		}

		gfx::core::Mesh& getMesh()
		{
			return m_mesh;
		}

		void animate(animator::AnimatorType type, float start_time)
		{
			m_animator.start(type, this, start_time);
		}

		void animate(float elapsed_time)
		{
			m_animator.update(elapsed_time, this);
		}

		void render(Material& material, GL::Context& gl)
		{
			getMatrices(material.world_mat, material.normal_mat);
			material.diffuse_color = m_color;
			material.use();

			getMesh().render(gl);
		}

	private:
		uint32_t m_id;
		GL::Vec3 m_position;
		GL::Vec3 m_rotation;
		GL::Vec3 m_scale;
		mutable GL::Mat4 m_world_mat;
		mutable GL::Mat4 m_normal_mat;
		mutable bool m_dirty;
		GL::Color m_color;
		int m_flags;
		gfx::core::Mesh m_mesh;
		gfx::model::animator::Animator<Model> m_animator;
	};
}
}
