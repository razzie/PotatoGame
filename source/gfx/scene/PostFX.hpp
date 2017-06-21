/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <GL/GL/Program.hpp>
#include <GL/GL/VertexBuffer.hpp>
#include <GL/GL/VertexArray.hpp>
#include <GL/GL/Framebuffer.hpp>
#include "gfx/core/GBuffer.hpp"

namespace gfx
{
class RenderThread;

namespace scene
{
	class Scene;

	class PostFX
	{
	public:
		typedef core::GBuffer<3> GBuffer;

		PostFX(RenderThread& render_thread);
		~PostFX();
		void render(Scene& scene);

	private:
		GL::Program m_postfx;
		GL::Program m_aa;
		GL::VertexBuffer m_vbo;
		GL::VertexArray m_vao;
		GL::Framebuffer m_fbo;
	};
}
}
