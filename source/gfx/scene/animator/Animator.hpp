/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include "gfx/scene/animator/AppearAnimator.hpp"

namespace gfx
{
namespace scene
{
namespace animator
{
	class Animator
	{
	public:
		enum Type
		{
			NONE,
			APPEAR
		};

		Animator();
		~Animator();
		void start(Type type, model::Model* model, float start_time);
		void reset(model::Model* model);
		void update(float elapsed, model::Model* model);

	private:
		Type m_type;
		float m_start_time;
		AppearAnimator m_appear_anim;
	};
}
}
}
