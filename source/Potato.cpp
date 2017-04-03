/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "Potato.hpp"

Potato::Settings::Settings(int argc, char** argv) :
	screen_width(1366),
	screen_height(768),
	fullscreen(false)
{
}

Potato::Potato(int argc, char** argv) :
	m_settings(argc, argv),
	m_game(*this, nullptr),
	m_render(*this, m_settings.screen_width, m_settings.screen_height, m_settings.fullscreen, nullptr)
{
}

Potato::~Potato()
{
}

Potato::Settings& Potato::getSettings()
{
	return m_settings;
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
