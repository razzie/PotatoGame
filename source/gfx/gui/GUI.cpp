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

static const char* vert = GLSL(
uniform mat4 transform;
in vec2 position;
in vec4 color;
in vec2 tcoords;
out vec4 frag_color;
out vec2 frag_tcoords;
void main()
{
	frag_color = vec4(color.r / 255.0, color.g / 255.0, color.b / 255.0, color.a / 255.0);
	frag_tcoords = tcoords;
	gl_Position = transform * vec4(position, 0.0, 1.0);
}
);

static const char* frag = GLSL(
uniform sampler2D texture;
uniform bool use_texture;
in vec4 frag_color;
in vec2 frag_tcoords;
out vec4 out_color;
void main()
{
	if (use_texture)
		out_color = texture2D(texture, frag_tcoords) * frag_color;
	else
		out_color = frag_color;
}
);

gfx::gui::GUI::GUI(gfx::RenderThread& render_thread) :
	m_render_thread(render_thread),
	m_gui_shader(GL::Shader(GL::ShaderType::Vertex, vert), GL::Shader(GL::ShaderType::Fragment, frag)),
	m_archive("gui.res", render_thread.getMemoryPool()),
	m_file_if(m_archive, render_thread.getMemoryPool()),
	m_render_if(render_thread.getWindow(), render_thread.getContext(), m_gui_shader, render_thread.getMemoryPool()),
	m_mouse(*this, render_thread.getWindow())
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

#ifdef _DEBUG
	Rocket::Debugger::Initialise(m_context);
	Rocket::Debugger::SetVisible(true);
#endif

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

GL::Context& gfx::gui::GUI::getContext()
{
	return m_render_thread.getContext();
}

raz::IMemoryPool* gfx::gui::GUI::getMemoryPool()
{
	return m_render_thread.getMemoryPool();
}

GL::Program& gfx::gui::GUI::getShader()
{
	return m_gui_shader;
}

resource::ArchiveReader& gfx::gui::GUI::getArchive()
{
	return m_archive;
}

bool gfx::gui::GUI::feed(const GL::Event& ev)
{
	const int modifiers = getKeyModifiers();

	switch (ev.Type)
	{
	case GL::Event::KeyDown:
		return !m_context->ProcessKeyDown(m_system_if.translateKey(ev.Key.Code), modifiers);

	case GL::Event::KeyUp:
		return !m_context->ProcessKeyUp(m_system_if.translateKey(ev.Key.Code), modifiers);

	case GL::Event::MouseDown:
		m_mouse_event_consumed = false;
		m_context->ProcessMouseButtonDown(ev.Mouse.Button, modifiers);
		break;

	case GL::Event::MouseUp:
		m_mouse_event_consumed = false;
		m_context->ProcessMouseButtonUp(ev.Mouse.Button, modifiers);
		break;

	case GL::Event::MouseWheel:
		return !m_context->ProcessMouseWheel(-ev.Mouse.Delta, modifiers);

	case GL::Event::MouseMove:
		m_mouse_event_consumed = false;
		m_context->ProcessMouseMove(ev.Mouse.X, ev.Mouse.Y, modifiers);
		break;
	}

	return m_mouse_event_consumed;
}

void gfx::gui::GUI::update()
{
	m_mouse.update(m_render_thread.getInputHelper());
	m_context->Update();
}

void gfx::gui::GUI::render()
{
	auto& gl = m_render_thread.getContext();

	//gl.DepthMask(false);
	//gl.Disable(GL::Capability::DepthTest);

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	gl.UseProgram(m_gui_shader);
	m_context->Render();

	m_mouse.render();
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
