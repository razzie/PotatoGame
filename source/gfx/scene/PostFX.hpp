/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <GL/GL/Program.hpp>
#include <GL/GL/VertexBuffer.hpp>
#include <GL/GL/VertexArray.hpp>
#include "resource/ShaderLoader.hpp"
#include "gfx/core/GBuffer.hpp"

namespace gfx
{
namespace scene
{
	class Scene;

	class PostFX
	{
	public:
		typedef core::GBuffer<3> GBuffer;

		PostFX(unsigned width, unsigned height, float render_distance, resource::ShaderLoader& shader_loader);
		~PostFX();
		void render(Scene& scene);

	private:
		GL::Program m_postfx;
		GL::VertexBuffer m_vbo;
		GL::VertexArray m_vao;
	};
}
}
