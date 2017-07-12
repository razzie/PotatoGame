/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <GL/Math/Mat4.hpp>
#include <GL/GL/Context.hpp>
#include <GL/GL/Program.hpp>
#include <GL/GL/VertexBuffer.hpp>
#include <GL/GL/VertexArray.hpp>

namespace gfx
{
namespace model
{
	class Horizon
	{
	public:
		Horizon(GL::Program& shader);
		void render(GL::Context& gl, const GL::Mat4& wvp);

	private:
		GL::VertexBuffer m_vertices;
		GL::VertexBuffer m_indices;
		GL::VertexArray m_vertex_array;
		GL::Program& m_shader;
	};
}
}
