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
		}

		bool update(Model* model, float elapsed)
		{
			const float duration = 0.75f;

			if (elapsed < 0.f)
				elapsed = 0.f;
			else if (elapsed > duration)
				return true;

			model->getMesh().setCompleteness(elapsed / duration);
			return false;
		}

		void end(Model* model)
		{
			model->getMesh().setCompleteness(1.f);
		}

	private:
		unsigned m_num_faces;
	};
}
}
}
