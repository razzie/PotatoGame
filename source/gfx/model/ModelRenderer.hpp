/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <GL/GL/Context.hpp>
#include <GL/GL/Program.hpp>
#include <GL/GL/VertexBuffer.hpp>
#include <GL/GL/VertexArray.hpp>
#include <GL/GL/Framebuffer.hpp>
#include <raz/timer.hpp>
#include "gfx/core/Camera.hpp"
#include "gfx/core/GBuffer.hpp"

namespace gfx
{
class RenderThread;

namespace model
{
	template<class Model>
	struct ModelContainer
	{
		typename Model::MaterialType material;
		Model model;
	};

	class ModelRenderer
	{
	public:
		enum Blur
		{
			NONE,
			DEPTH,
			FULL
		};

		typedef core::GBuffer<3> GBuffer;

		ModelRenderer(RenderThread& render_thread);
		GL::Context& getContext();
		GBuffer& getGBuffer();
		core::Camera& getCamera();
		const core::Camera& getCamera() const;
		float getElapsedTime() const;
		void setBlur(Blur blur);
		void begin();
		void present(GL::Framebuffer* framebuffer = nullptr);

		template<class Model>
		void render(ModelContainer<Model>& container)
		{
			m_gl.UseProgram(container.material.shader);
			container.material.time = m_time;
			container.material.camera_mat = m_cam.getMatrix();
			container.model.animate(container.material.time);
			container.model.render(container.material, m_gl);
		}

	private:
		GL::Context& m_gl;
		GL::Program m_postfx;
		GL::Program m_aa;
		GL::VertexBuffer m_vbo;
		GL::VertexArray m_vao;
		GL::Framebuffer m_fbo;
		raz::Timer m_timer;
		float m_time;
		GBuffer m_gbuffer;
		core::Camera m_cam;
		Blur m_blur;
	};
}
}
