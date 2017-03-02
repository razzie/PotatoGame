/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <Rocket/Core.h>
#include <Rocket/Core/FileInterface.h>
#include <GL/GL/Context.hpp>
#include <GL/GL/VertexBuffer.hpp>
#include <GL/GL/VertexArray.hpp>
#include <GL/GL/Texture.hpp>
#include "gfx/gui/RocketFileInterface.hpp"
#include "gfx/gui/RocketRenderInterface.hpp"

class CompiledGeometry
{
public:
	CompiledGeometry(GL::Program& shader, Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture) :
		m_shader(shader)
	{
		if (texture)
		{
			m_texture = *(GL::Texture*)texture;
			m_use_texture = true;
		}
		else
		{
			m_use_texture = false;
		}
		m_vertices = GL::VertexBuffer(vertices, num_vertices * sizeof(Rocket::Core::Vertex), GL::BufferUsage::StaticCopy);
		m_indices = GL::VertexBuffer(indices, num_indices * sizeof(int), GL::BufferUsage::StaticCopy);
		m_num_indices = num_indices;
		m_vertex_array.BindElements(m_indices);

		m_vertex_array.BindAttribute(m_shader.GetAttribute("position"), m_vertices, GL::Type::Float,        2, sizeof(Rocket::Core::Vertex), 0);
		m_vertex_array.BindAttribute(m_shader.GetAttribute("color"),    m_vertices, GL::Type::UnsignedByte, 4, sizeof(Rocket::Core::Vertex), sizeof(float) * 2);
		m_vertex_array.BindAttribute(m_shader.GetAttribute("tcoords"),  m_vertices, GL::Type::Float,        2, sizeof(Rocket::Core::Vertex), sizeof(float) * 2 + sizeof(unsigned char) * 4);
	}

	void render(GL::Window& window, GL::Context& gl, const GL::Mat4& proj, const Rocket::Core::Vector2f& translation)
	{
		GL::Mat4 world;
		world.Translate({ translation.x, translation.y, 0.f });

		//gl.UseProgram(m_shader);

		if (m_use_texture)
		{
			gl.BindTexture(m_texture, 0);
		}
		m_shader.SetUniform("transform", proj * world);
		m_shader.SetUniform("texture", 0);
		m_shader.SetUniform("use_texture", (int)m_use_texture);

		gl.DrawElements(m_vertex_array, GL::Primitive::Triangles, 0, m_num_indices, GL::Type::UnsignedInt);
	}

private:
	GL::Program& m_shader;
	GL::Texture m_texture;
	GL::VertexBuffer m_vertices;
	GL::VertexBuffer m_indices;
	GL::VertexArray m_vertex_array;
	unsigned m_num_indices;
	bool m_use_texture;
};


gfx::gui::RocketRenderInterface::RocketRenderInterface(GL::Window& window, GL::Context& gl, GL::Program& gui_shader, raz::IMemoryPool* memory) :
	m_window(&window),
	m_gl(&gl),
	m_memory(memory),
	m_proj(GL::Mat4::Ortho(0.f, (float)window.GetWidth(), (float)window.GetHeight(), 0.f, 0.f, 1000.f)),
	m_gui_shader(gui_shader)
{
}

void gfx::gui::RocketRenderInterface::resize()
{
	auto width = m_window->GetWidth();
	auto height = m_window->GetHeight();

	Rocket::Core::Context* context = Rocket::Core::GetContext(0);
	context->SetDimensions(Rocket::Core::Vector2i(width, height));

	m_proj = GL::Mat4::Ortho(0.f, (float)width, (float)height, 0.f, 0.f, 1000.f);
}

const GL::Mat4 gfx::gui::RocketRenderInterface::getProjectionMatrix() const
{
	return m_proj;
}

void gfx::gui::RocketRenderInterface::RenderGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f& translation)
{
	CompiledGeometry geom(m_gui_shader, vertices, num_vertices, indices, num_indices, texture);
	geom.render(*m_window, *m_gl, m_proj, translation);
}

Rocket::Core::CompiledGeometryHandle gfx::gui::RocketRenderInterface::CompileGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture)
{
	raz::Allocator<CompiledGeometry> alloc(m_memory);
	CompiledGeometry* geom = std::allocator_traits<raz::Allocator<CompiledGeometry>>::allocate(alloc, 1);
	std::allocator_traits<raz::Allocator<CompiledGeometry>>::construct(alloc, geom, m_gui_shader, vertices, num_vertices, indices, num_indices, texture);

	return Rocket::Core::CompiledGeometryHandle(geom);
}

void gfx::gui::RocketRenderInterface::RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f& translation)
{
	reinterpret_cast<CompiledGeometry*>(geometry)->render(*m_window, *m_gl, m_proj, translation);
}

void gfx::gui::RocketRenderInterface::ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry)
{
	CompiledGeometry* geom = reinterpret_cast<CompiledGeometry*>(geometry);

	raz::Allocator<CompiledGeometry> alloc(m_memory);
	std::allocator_traits<raz::Allocator<CompiledGeometry>>::destroy(alloc, geom);
	std::allocator_traits<raz::Allocator<CompiledGeometry>>::deallocate(alloc, geom, 1);
}

void gfx::gui::RocketRenderInterface::EnableScissorRegion(bool enable)
{
	if (enable)
		glEnable(GL_SCISSOR_TEST);
	else
		glDisable(GL_SCISSOR_TEST);
}

void gfx::gui::RocketRenderInterface::SetScissorRegion(int x, int y, int width, int height)
{
	glScissor(x, m_window->GetHeight() - (y + height), width, height);
}

bool gfx::gui::RocketRenderInterface::LoadTexture(Rocket::Core::TextureHandle& texture_handle, Rocket::Core::Vector2i& texture_dimensions, const Rocket::Core::String& source)
{
	Rocket::Core::FileInterface* file_interface = Rocket::Core::GetFileInterface();
	Rocket::Core::FileHandle file_handle = file_interface->Open(source);
	if (file_handle == 0)
		return false;

	bool return_value = true;

	try
	{
		RocketFileInterface::File* file = reinterpret_cast<RocketFileInterface::File*>(file_handle);

		GL::Image image(reinterpret_cast<GL::uchar*>(file->data.data()), file->data.size());

		raz::Allocator<GL::Texture> tex_alloc(m_memory);
		GL::Texture* tex = std::allocator_traits<raz::Allocator<GL::Texture>>::allocate(tex_alloc, 1);
		std::allocator_traits<raz::Allocator<GL::Texture>>::construct(tex_alloc, tex, image);

		texture_handle = Rocket::Core::TextureHandle(tex);
		texture_dimensions.x = image.GetWidth();
		texture_dimensions.y = image.GetHeight();
	}
	catch (GL::FormatException&)
	{
		return_value = false;
	}

	file_interface->Close(file_handle);

	return return_value;
}

bool gfx::gui::RocketRenderInterface::GenerateTexture(Rocket::Core::TextureHandle& texture_handle, const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions)
{
	try
	{
		GL::Image image((GL::ushort)source_dimensions.x, (GL::ushort)source_dimensions.y, const_cast<GL::uchar*>(source));

		raz::Allocator<GL::Texture> tex_alloc(m_memory);
		GL::Texture* tex = std::allocator_traits<raz::Allocator<GL::Texture>>::allocate(tex_alloc, 1);
		std::allocator_traits<raz::Allocator<GL::Texture>>::construct(tex_alloc, tex, image);

		texture_handle = Rocket::Core::TextureHandle(tex);

		return true;
	}
	catch (GL::FormatException&)
	{
		return false;
	}
}

void gfx::gui::RocketRenderInterface::ReleaseTexture(Rocket::Core::TextureHandle texture_handle)
{
	GL::Texture* tex = reinterpret_cast<GL::Texture*>(texture_handle);

	raz::Allocator<GL::Texture> tex_alloc(m_memory);
	std::allocator_traits<raz::Allocator<GL::Texture>>::destroy(tex_alloc, tex);
	std::allocator_traits<raz::Allocator<GL::Texture>>::deallocate(tex_alloc, tex, 1);
}
