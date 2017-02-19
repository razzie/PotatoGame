/*
 * Copyright (C) G�bor G�rzs�ny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <Rocket/Core/RenderInterface.h>
#include <GL/Window/Window.hpp>

namespace ui
{
namespace menu
{
	class RocketRenderInterface : public Rocket::Core::RenderInterface
	{
	public:
		RocketRenderInterface(GL::Window* Window);

		/// Resizes the viewport automatically
		void Resize();

		/// Called by Rocket when it wants to render geometry that it does not wish to optimise.
		virtual void RenderGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f& translation);
		/// Called by Rocket when it wants to compile geometry it believes will be static for the forseeable future.
		virtual Rocket::Core::CompiledGeometryHandle CompileGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture);
		/// Called by Rocket when it wants to render application-compiled geometry.
		virtual void RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f& translation);
		/// Called by Rocket when it wants to release application-compiled geometry.
		virtual void ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry);

		/// Called by Rocket when it wants to enable or disable scissoring to clip content.
		virtual void EnableScissorRegion(bool enable);
		/// Called by Rocket when it wants to change the scissor region.
		virtual void SetScissorRegion(int x, int y, int width, int height);

		/// Called by Rocket when a texture is required by the library.
		virtual bool LoadTexture(Rocket::Core::TextureHandle& texture_handle, Rocket::Core::Vector2i& texture_dimensions, const Rocket::Core::String& source);
		/// Called by Rocket when a texture is required to be built from an internally-generated sequence of pixels.
		virtual bool GenerateTexture(Rocket::Core::TextureHandle& texture_handle, const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions);
		/// Called by Rocket when a loaded texture is no longer required.
		virtual void ReleaseTexture(Rocket::Core::TextureHandle texture_handle);

	private:
		GL::Window* m_window;
	};
}
}