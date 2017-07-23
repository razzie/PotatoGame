/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include "common/lerp.hpp"
#include "gfx/model/ModelFlag.hpp"

namespace gfx
{
namespace model
{
namespace animator
{
	template<class Model>
	class DisappearAnimator
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

			model->getMesh().setCompleteness(1.f - elapsed / duration);
			return false;
		}

		void end(Model* model)
		{
			model->getMesh().setCompleteness(0.f);
			model->setFlag(ModelFlag::REMOVE);
		}
	};
}
}
}
