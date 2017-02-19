/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "ui/menu/RocketRenderInterface.hpp"

ui::menu::RocketRenderInterface::RocketRenderInterface(GL::Window* Window)
{
}

void ui::menu::RocketRenderInterface::Resize()
{
}

void ui::menu::RocketRenderInterface::RenderGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f& translation)
{
}

Rocket::Core::CompiledGeometryHandle ui::menu::RocketRenderInterface::CompileGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture)
{
	return Rocket::Core::CompiledGeometryHandle();
}

void ui::menu::RocketRenderInterface::RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f& translation)
{
}

void ui::menu::RocketRenderInterface::ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry)
{
}

void ui::menu::RocketRenderInterface::EnableScissorRegion(bool enable)
{
}

void ui::menu::RocketRenderInterface::SetScissorRegion(int x, int y, int width, int height)
{
}

bool ui::menu::RocketRenderInterface::LoadTexture(Rocket::Core::TextureHandle& texture_handle, Rocket::Core::Vector2i& texture_dimensions, const Rocket::Core::String& source)
{
	return false;
}

bool ui::menu::RocketRenderInterface::GenerateTexture(Rocket::Core::TextureHandle& texture_handle, const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions)
{
	return false;
}

void ui::menu::RocketRenderInterface::ReleaseTexture(Rocket::Core::TextureHandle texture_handle)
{
}
