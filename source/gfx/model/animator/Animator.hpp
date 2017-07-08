/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include "gfx/model/animator/AppearAnimator.hpp"

namespace gfx
{
namespace model
{
namespace animator
{
	enum AnimatorType
	{
		NONE,
		APPEAR
	};

	template<class Model>
	class Animator
	{
	public:
		Animator() : m_type(AnimatorType::NONE)
		{
		}

		~Animator()
		{
		}

		void start(AnimatorType type, Model* model, float start_time)
		{
			reset(model);

			m_start_time = start_time;
			m_type = type;

			switch (type)
			{
			case AnimatorType::APPEAR:
				m_appear_anim.begin(model);
				break;
			}
		}

		void reset(Model* model)
		{
			switch (m_type)
			{
			case AnimatorType::APPEAR:
				m_appear_anim.end(model);
				break;
			}

			m_type = AnimatorType::NONE;
		}

		void update(float elapsed, Model* model)
		{
			switch (m_type)
			{
			case AnimatorType::APPEAR:
				if (m_appear_anim.update(model, elapsed - m_start_time))
					reset(model);
				break;
			}
		}

	private:
		AnimatorType m_type;
		float m_start_time;
		AppearAnimator<Model> m_appear_anim;
	};
}
}
}
