/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include "gfx/scene/model/Model.hpp"

namespace gfx
{
namespace scene
{
namespace animator
{
	class AppearAnimator
	{
	public:
		AppearAnimator(model::Model* model);
		AppearAnimator(AppearAnimator&& other);
		AppearAnimator(const AppearAnimator&) = delete;
		~AppearAnimator();
		void update(float progress);

	private:
		model::Model* m_model;
		unsigned m_num_faces;
	};
}
}
}
