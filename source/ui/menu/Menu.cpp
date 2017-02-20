/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <stdexcept>
#include <Rocket/Core.h>
#include "ui/menu/Menu.hpp"

ui::menu::Menu::Menu(GL::Window& window, GL::Context& gl) :
	m_window(&window),
	m_gl(&gl),
	m_file_if("../data/"),
	m_render_if(window, gl)
{
	Rocket::Core::SetFileInterface(&m_file_if);
	Rocket::Core::SetRenderInterface(&m_render_if);
	Rocket::Core::SetSystemInterface(&m_system_if);

	if (!Rocket::Core::Initialise())
		throw std::runtime_error("librocket initialization error");

	Rocket::Core::FontDatabase::LoadFontFace("Delicious-Bold.otf");
	Rocket::Core::FontDatabase::LoadFontFace("Delicious-BoldItalic.otf");
	Rocket::Core::FontDatabase::LoadFontFace("Delicious-Italic.otf");
	Rocket::Core::FontDatabase::LoadFontFace("Delicious-Roman.otf");

	m_context = Rocket::Core::CreateContext("main", Rocket::Core::Vector2i(m_window->GetWidth(), m_window->GetHeight()));
	if (m_context == NULL)
	{
		Rocket::Core::Shutdown();
		throw std::runtime_error("librocket initialization error");
	}

	//Rocket::Core::ElementDocument* document = m_context->LoadDocument("tutorial.rml");
	//if (document != NULL)
	//{
	//	document->Show();
	//	document->RemoveReference();
	//}
}

ui::menu::Menu::~Menu()
{
	m_context->RemoveReference();
	Rocket::Core::Shutdown();
}

void ui::menu::Menu::feed(GL::Event& ev)
{
}

void ui::menu::Menu::render()
{
	m_context->Update();
	m_context->Render();
}
