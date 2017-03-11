/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <GL/GL/Program.hpp>
#include <GL/GL/VertexBuffer.hpp>
#include <GL/GL/VertexArray.hpp>

namespace gfx
{
namespace scene
{
	class Scene;

	class Horizon
	{
	public:
		Horizon(GL::Program& shader);
		void render(Scene& scene);

	private:
		GL::VertexBuffer m_vertices;
		GL::VertexBuffer m_indices;
		GL::VertexArray m_vertex_array;
		GL::Program& m_shader;
	};
}
}
