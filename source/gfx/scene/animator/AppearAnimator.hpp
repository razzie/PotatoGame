/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include "common/lerp.hpp"

namespace gfx
{
namespace scene
{
namespace animator
{
	template<class Model>
	class AppearAnimator
	{
	public:
		void begin(Model* model)
		{
			m_num_faces = model->getMesh().num_of_indices / 3;
		}

		bool update(Model* model, float elapsed)
		{
			const float duration = 0.75f;

			if (elapsed < 0.f)
				elapsed = 0.f;
			else if (elapsed > duration)
				return true;

			unsigned show_faces = common::lerp(0u, m_num_faces, elapsed / duration);
			model->getMesh().num_of_indices = show_faces * 3;
			return false;
		}

		void end(Model* model)
		{
			model->getMesh().num_of_indices = m_num_faces * 3;
		}

	private:
		unsigned m_num_faces;
	};
}
}
}
