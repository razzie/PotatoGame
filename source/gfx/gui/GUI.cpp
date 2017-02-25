/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <stdexcept>
#include <Rocket/Core.h>
#include <Rocket/Controls.h>
#include <Rocket/Debugger.h>
#include "gfx/gui/GUI.hpp"

gfx::gui::GUI::GUI(GL::Window& window, GL::Context& gl) :
	m_window(&window),
	m_gl(&gl),
	m_file_if(nullptr),
	m_render_if(window, gl)
{
	Rocket::Core::SetFileInterface(&m_file_if);
	Rocket::Core::SetRenderInterface(&m_render_if);
	Rocket::Core::SetSystemInterface(&m_system_if);

	if (!Rocket::Core::Initialise())
		throw std::runtime_error("librocket initialization error");

	Rocket::Controls::Initialise();

	Rocket::Core::FontDatabase::LoadFontFace("arial.ttf");

	m_context = Rocket::Core::CreateContext("main", Rocket::Core::Vector2i(m_window->GetWidth(), m_window->GetHeight()));
	if (m_context == NULL)
	{
		Rocket::Core::Shutdown();
		throw std::runtime_error("librocket initialization error");
	}

	//Rocket::Debugger::Initialise(m_context);
	//Rocket::Debugger::SetVisible(true);

	//Rocket::Core::ElementDocument* document = m_context->LoadDocument("tutorial.rml");
	//if (document != NULL)
	//{
	//	document->Show();
	//	document->RemoveReference();
	//}
}

gfx::gui::GUI::~GUI()
{
	m_context->RemoveReference();
	Rocket::Core::Shutdown();
}

bool gfx::gui::GUI::feed(GL::Event& ev)
{
	return false;
}

void gfx::gui::GUI::render()
{
	m_gl->Disable(GL::Capability::DepthTest);
	m_gl->Disable(GL::Capability::CullFace);

	m_context->Update();
	m_context->Render();

	m_gl->Enable(GL::Capability::DepthTest);
	m_gl->Enable(GL::Capability::CullFace);
}
