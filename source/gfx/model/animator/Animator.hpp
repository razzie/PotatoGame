/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <tuple>
#include "gfx/model/animator/AppearAnimator.hpp"
#include "gfx/model/animator/DisappearAnimator.hpp"

namespace gfx
{
namespace model
{
namespace animator
{
	enum AnimatorType : size_t
	{
		NONE,
		APPEAR,
		DISAPPEAR,
		COLOR_BLINK,
		MOVE,
		TRANSPORT
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

			start<>(type, model, start_time);
		}

		void reset(Model* model)
		{
			reset<>(model);
			m_type = AnimatorType::NONE;
		}

		void update(float elapsed, Model* model)
		{
			update<>(elapsed, model);
		}

	private:
		template<class Model, template<class> class... Animator>
		using AnimatorContainer = std::tuple<Animator<Model>...>;

		AnimatorType m_type;
		float m_start_time;
		AnimatorContainer<Model, AppearAnimator, DisappearAnimator> m_animators;

		static constexpr size_t ANIMS = std::tuple_size<decltype(m_animators)>::value;

		template<size_t N>
		using ValidN = typename std::enable_if<N < ANIMS>::type;

		template<size_t N>
		using InvalidN = typename std::enable_if<N >= ANIMS>::type;

		template<size_t N = 0>
		ValidN<N> start(AnimatorType type, Model* model, float start_time)
		{
			if (N + 1 == (size_t)type)
			{
				std::get<N>(m_animators).begin(model);
			}
			else
			{
				start<N + 1>(type, model, start_time);
			}
		}

		template<int N = 0>
		InvalidN<N> start(AnimatorType type, Model* model, float start_time)
		{
		}

		template<size_t N = 0>
		ValidN<N> reset(Model* model)
		{
			if (N + 1 == (size_t)m_type)
			{
				auto& anim = std::get<N>(m_animators);
				anim.end(model);
			}
			else
			{
				reset<N + 1>(model);
			}
		}

		template<size_t N = 0>
		InvalidN<N> reset(Model* model)
		{
		}

		template<int N = 0>
		ValidN<N> update(float elapsed, Model* model)
		{
			if (N + 1 == (size_t)m_type)
			{
				auto& anim = std::get<N>(m_animators);
				if (anim.update(model, elapsed - m_start_time))
				{
					anim.end(model);
					m_type = AnimatorType::NONE;
				}
			}
			else
			{
				update<N + 1>(elapsed, model);
			}
		}

		template<int N = 0>
		InvalidN<N> update(float elapsed, Model* model)
		{
		}
	};
}
}
}
