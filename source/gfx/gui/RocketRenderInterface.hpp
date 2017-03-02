/*
 * Copyright (C) G�bor G�rzs�ny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <Rocket/Core/RenderInterface.h>
#include <GL/Window/Window.hpp>
#include <GL/GL/Context.hpp>
#include <GL/GL/Program.hpp>
#include <GL/Math/Mat4.hpp>
#include <raz/memory.hpp>

namespace gfx
{
namespace gui
{
	class RocketRenderInterface : public Rocket::Core::RenderInterface
	{
	public:
		RocketRenderInterface(GL::Window& window, GL::Context& gl, GL::Program& gui_shader, raz::IMemoryPool* memory = nullptr);
		void resize();
		const GL::Mat4 getProjectionMatrix() const;
		virtual void RenderGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f& translation);
		virtual Rocket::Core::CompiledGeometryHandle CompileGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture);
		virtual void RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f& translation);
		virtual void ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry);
		virtual void EnableScissorRegion(bool enable);
		virtual void SetScissorRegion(int x, int y, int width, int height);
		virtual bool LoadTexture(Rocket::Core::TextureHandle& texture_handle, Rocket::Core::Vector2i& texture_dimensions, const Rocket::Core::String& source);
		virtual bool GenerateTexture(Rocket::Core::TextureHandle& texture_handle, const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions);
		virtual void ReleaseTexture(Rocket::Core::TextureHandle texture_handle);

	private:
		GL::Window* m_window;
		GL::Context* m_gl;
		raz::IMemoryPool* m_memory;
		GL::Mat4 m_proj;
		GL::Program& m_gui_shader;
	};
}
}
