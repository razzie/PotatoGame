/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "common/lerp.hpp"
#include "gfx/scene/animator/AppearAnimator.hpp"

gfx::scene::animator::AppearAnimator::AppearAnimator(model::Model* model) :
	m_model(model),
	m_num_faces(model->getMesh().num_of_indices / 3)
{
}

gfx::scene::animator::AppearAnimator::AppearAnimator(AppearAnimator&& other) :
	m_model(other.m_model),
	m_num_faces(other.m_num_faces)
{
	other.m_model = nullptr;
}

gfx::scene::animator::AppearAnimator::~AppearAnimator()
{
	if (m_model)
		m_model->getMesh().num_of_indices = m_num_faces * 3;
}

void gfx::scene::animator::AppearAnimator::update(float progress)
{
	if (progress < 0.f)
		progress = 0.f;
	else if (progress > 1.f)
		progress = 1.f;

	unsigned show_faces = common::lerp(0u, m_num_faces, progress);
	if (m_model)
		m_model->getMesh().num_of_indices = show_faces * 3;
}
