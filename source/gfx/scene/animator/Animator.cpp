/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "gfx/scene/animator/Animator.hpp"

gfx::scene::animator::Animator::Animator() :
	m_type(Type::NONE)
{
}

gfx::scene::animator::Animator::~Animator()
{
}

void gfx::scene::animator::Animator::start(Type type, model::Model* model)
{
	reset(model);

	m_start_time = 0.f;
	m_type = type;

	switch (type)
	{
	case Type::APPEAR:
		m_appear_anim.begin(model);
		break;
	}
}

void gfx::scene::animator::Animator::reset(model::Model* model)
{
	switch (m_type)
	{
	case Type::APPEAR:
		m_appear_anim.end(model);
		break;
	}

	m_type = Type::NONE;
}

void gfx::scene::animator::Animator::update(float elapsed, model::Model* model)
{
	switch (m_type)
	{
	case Type::APPEAR:
		if (m_appear_anim.update(model, elapsed - m_start_time))
			reset(model);
		break;
	}
}
