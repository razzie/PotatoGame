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
	class Scene;

	namespace model
	{
		class Model
		{
		public:
			Model();
			virtual ~Model() = default;
			void setPosition(GL::Vec3 position);
			GL::Vec3 getPosition() const;
			void setRotation(GL::Vec3 rotation);
			GL::Vec3 getRotation() const;
			void setScale(GL::Vec3 scale);
			GL::Vec3 getScale() const;
			void getMatrices(GL::Mat4& world, GL::Mat4& normal) const;
			virtual void render(Scene&) = 0;

		private:
			GL::Vec3 m_position;
			GL::Vec3 m_rotation;
			GL::Vec3 m_scale;
			mutable GL::Mat4 m_world_mat;
			mutable GL::Mat4 m_normal_mat;
			mutable bool m_dirty;
		};
	}
}
}
