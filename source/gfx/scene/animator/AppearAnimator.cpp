/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "common/lerp.hpp"
#include "gfx/scene/model/Model.hpp"
#include "gfx/scene/animator/AppearAnimator.hpp"

void gfx::scene::animator::AppearAnimator::begin(model::Model* model)
{
	m_num_faces = model->getMesh().num_of_indices / 3;
}

bool gfx::scene::animator::AppearAnimator::update(model::Model* model, float elapsed)
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

void gfx::scene::animator::AppearAnimator::end(model::Model* model)
{
	model->getMesh().num_of_indices = m_num_faces * 3;
}
