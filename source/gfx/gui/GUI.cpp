/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <stdexcept>
#include <Rocket/Core.h>
#include <Rocket/Controls.h>
#include <Rocket/Debugger.h>
#include "gfx/RenderThread.hpp"
#include "gfx/gui/GUI.hpp"

gfx::gui::GUI::GUI(gfx::RenderThread& render_thread) :
	m_render_thread(render_thread),
	m_gui_shader(render_thread.getShaderTable().getGUIShader()),
	m_file_if(render_thread.getMemoryPool()),
	m_render_if(render_thread.getWindow(), render_thread.getContext(), m_gui_shader, render_thread.getMemoryPool())
{
	Rocket::Core::SetFileInterface(&m_file_if);
	Rocket::Core::SetRenderInterface(&m_render_if);
	Rocket::Core::SetSystemInterface(&m_system_if);

	if (!Rocket::Core::Initialise())
		throw std::runtime_error("librocket initialization error");

	Rocket::Controls::Initialise();

	Rocket::Core::FontDatabase::LoadFontFace("arial.ttf");

	auto& window = m_render_thread.getWindow();
	m_context = Rocket::Core::CreateContext("main", Rocket::Core::Vector2i(window.GetWidth(), window.GetHeight()));
	if (m_context == NULL)
	{
		Rocket::Core::Shutdown();
		throw std::runtime_error("librocket initialization error");
	}

	m_context->AddEventListener("mousedown", this);
	m_context->AddEventListener("mouseup", this);
	m_context->AddEventListener("mousemove", this);

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

bool gfx::gui::GUI::feed(const GL::Event& ev)
{
	const int modifiers = getKeyModifiers();
	m_mouse_event_consumed = false;

	switch (ev.Type)
	{
	case GL::Event::KeyDown:
		return !m_context->ProcessKeyDown(m_system_if.translateKey(ev.Key.Code), modifiers);

	case GL::Event::KeyUp:
		return !m_context->ProcessKeyUp(m_system_if.translateKey(ev.Key.Code), modifiers);

	case GL::Event::MouseDown:
		m_context->ProcessMouseButtonDown(ev.Mouse.Button, modifiers);
		break;

	case GL::Event::MouseUp:
		m_context->ProcessMouseButtonUp(ev.Mouse.Button, modifiers);
		break;

	case GL::Event::MouseWheel:
		return !m_context->ProcessMouseWheel(-ev.Mouse.Delta, modifiers);

	case GL::Event::MouseMove:
		m_context->ProcessMouseMove(ev.Mouse.X, ev.Mouse.Y, modifiers);
		break;
	}

	return m_mouse_event_consumed;
}

void gfx::gui::GUI::render()
{
	auto& gl = m_render_thread.getContext();

	gl.Disable(GL::Capability::DepthTest);
	gl.Disable(GL::Capability::CullFace);

	gl.UseProgram(m_gui_shader);

	m_context->Update();
	m_context->Render();

	gl.Enable(GL::Capability::DepthTest);
	gl.Enable(GL::Capability::CullFace);
}

void gfx::gui::GUI::ProcessEvent(Rocket::Core::Event& ev)
{
	m_mouse_event_consumed = (ev.GetTargetElement() != m_context->GetRootElement());
}

int gfx::gui::GUI::getKeyModifiers() const
{
	auto& helper = m_render_thread.getInputHelper();
	return m_system_if.translateModifiers(helper.isAltDown(), helper.isControlDown(), helper.isShiftDown());
}
