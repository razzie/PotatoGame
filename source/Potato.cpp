/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "Potato.hpp"

Potato::Potato(int argc, char** argv) :
	m_game(*this, nullptr),
	m_render(*this, 1366, 768, false, nullptr)
{
}

Potato::~Potato()
{
}

game::GameThread& Potato::getGameThread()
{
	return m_game;
}

gfx::RenderThread& Potato::getRenderThread()
{
	return m_render;
}

int Potato::run()
{
	return m_render.run();
}
