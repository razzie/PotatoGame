/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <GL/Window/Window.hpp>

class Application
{
public:
	Application(int argc, char** argv);
	~Application();
	int run();

private:
	GL::Window m_window;
	GL::Context& m_gl;
};
