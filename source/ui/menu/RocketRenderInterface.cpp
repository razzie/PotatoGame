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
#include <GL/Math/Mat4.hpp>
#include "ui/menu/RocketRenderInterface.hpp"

class CompiledGeometry
{
public:
	CompiledGeometry(const GL::Program& shader, Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture)
	{
		m_shader = shader;
		m_texture = *(GL::Texture*)texture;
		m_vertices = GL::VertexBuffer(vertices, num_vertices * sizeof(Rocket::Core::Vertex), GL::BufferUsage::StaticCopy);
		m_indices = GL::VertexBuffer(indices, num_indices * sizeof(int), GL::BufferUsage::StaticCopy);
		m_num_indices = num_indices;
		m_vertex_array.BindElements(m_indices);

		m_vertex_array.BindAttribute(m_shader.GetAttribute("position"), m_vertices, GL::Type::Float,        2, sizeof(Rocket::Core::Vertex), 0);
		m_vertex_array.BindAttribute(m_shader.GetAttribute("color"),    m_vertices, GL::Type::UnsignedByte, 4, sizeof(Rocket::Core::Vertex), sizeof(float) * 2);
		m_vertex_array.BindAttribute(m_shader.GetAttribute("tcoords"),  m_vertices, GL::Type::Float,        2, sizeof(Rocket::Core::Vertex), sizeof(float) * 2 + sizeof(unsigned char) * 4);
	}

	void render(GL::Context& gl, const Rocket::Core::Vector2f& translation)
	{
		m_shader.SetUniform("position", GL::Vec2(translation.x, translation.y));
		gl.UseProgram(m_shader);
		gl.BindTexture(m_texture, 0);
		gl.DrawElements(m_vertex_array, GL::Primitive::Triangles, 0, m_num_indices, GL::Type::Int);
	}

private:
	GL::Program m_shader;
	GL::Texture m_texture;
	GL::VertexBuffer m_vertices;
	GL::VertexBuffer m_indices;
	GL::VertexArray m_vertex_array;
	unsigned m_num_indices;
};

ui::menu::RocketRenderInterface::RocketRenderInterface(GL::Window& window, GL::Context& gl) :
	m_window(&window),
	m_gl(&gl)
{
}

void ui::menu::RocketRenderInterface::RenderGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f& translation)
{
	CompiledGeometry geom(m_shader, vertices, num_vertices, indices, num_indices, texture);
	geom.render(*m_gl, translation);
}

Rocket::Core::CompiledGeometryHandle ui::menu::RocketRenderInterface::CompileGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture)
{
	return (Rocket::Core::CompiledGeometryHandle)(new CompiledGeometry(m_shader, vertices, num_vertices, indices, num_indices, texture));
}

void ui::menu::RocketRenderInterface::RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f& translation)
{
	((CompiledGeometry*)geometry)->render(*m_gl, translation);
}

void ui::menu::RocketRenderInterface::ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry)
{
	delete (CompiledGeometry*)geometry;
}

void ui::menu::RocketRenderInterface::EnableScissorRegion(bool enable)
{
	if (enable)
		glEnable(GL_SCISSOR_TEST);
	else
		glDisable(GL_SCISSOR_TEST);
}

void ui::menu::RocketRenderInterface::SetScissorRegion(int x, int y, int width, int height)
{
	glScissor(x, m_window->GetHeight() - (y + height), width, height);
}

bool ui::menu::RocketRenderInterface::LoadTexture(Rocket::Core::TextureHandle& texture_handle, Rocket::Core::Vector2i& texture_dimensions, const Rocket::Core::String& source)
{
	Rocket::Core::FileInterface* file_interface = Rocket::Core::GetFileInterface();
	Rocket::Core::FileHandle file_handle = file_interface->Open(source);
	if (file_handle == NULL)
		return false;

	file_interface->Seek(file_handle, 0, SEEK_END);
	size_t buffer_size = file_interface->Tell(file_handle);
	file_interface->Seek(file_handle, 0, SEEK_SET);

	GL::uchar* buffer = new GL::uchar[buffer_size];
	file_interface->Read(buffer, buffer_size, file_handle);
	file_interface->Close(file_handle);

	GL::Image image(buffer, buffer_size);
	delete buffer;

	texture_handle = (Rocket::Core::TextureHandle)(new GL::Texture(image));
	texture_dimensions.x = image.GetWidth();
	texture_dimensions.y = image.GetHeight();

	return false;
}

bool ui::menu::RocketRenderInterface::GenerateTexture(Rocket::Core::TextureHandle& texture_handle, const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions)
{
	GL::Image image((GL::ushort)source_dimensions.x, (GL::ushort)source_dimensions.y, const_cast<GL::uchar*>(source));
	texture_handle = (Rocket::Core::TextureHandle)(new GL::Texture(image));
	return true;
}

void ui::menu::RocketRenderInterface::ReleaseTexture(Rocket::Core::TextureHandle texture_handle)
{
	delete (GL::Texture*)texture_handle;
}
