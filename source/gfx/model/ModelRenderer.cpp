/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "gfx/RenderThread.hpp"
#include "gfx/model/ModelRenderer.hpp"

static const float vertices[] = {
	-1.f, -1.f,
	 1.f, -1.f,
	-1.f,  1.f,

	 1.f,  1.f,
	-1.f,  1.f,
	 1.f, -1.f
};

gfx::model::ModelRenderer::ModelRenderer(RenderThread& render_thread) :
	m_gl(render_thread.getContext()),
	m_postfx(render_thread.getShaderLoader().get("postfx")),
	m_aa(render_thread.getShaderLoader().get("aa")),
	m_vbo(vertices, sizeof(vertices), GL::BufferUsage::StaticCopy),
	m_fbo(render_thread.getWindow().GetWidth(), render_thread.getWindow().GetHeight(), 24, 8),
	m_time(0.f),
	m_gbuffer(render_thread.getWindow().GetWidth(), render_thread.getWindow().GetHeight()),
	m_cam(render_thread.getAspectRatio(), render_thread.getRenderDistance())
{
	m_vao.BindAttribute(m_postfx.GetAttribute("position"), m_vbo, GL::Type::Float, 2, sizeof(float) * 2, 0);
	m_timer.reset();
}

GL::Context& gfx::model::ModelRenderer::getContext()
{
	return m_gl;
}

gfx::model::ModelRenderer::GBuffer& gfx::model::ModelRenderer::getGBuffer()
{
	return m_gbuffer;
}

gfx::core::Camera& gfx::model::ModelRenderer::getCamera()
{
	return m_cam;
}

const gfx::core::Camera& gfx::model::ModelRenderer::getCamera() const
{
	return m_cam;
}

float gfx::model::ModelRenderer::getElapsedTime() const
{
	return m_time;
}

void gfx::model::ModelRenderer::begin()
{
	m_time = 0.001f * m_timer.peekElapsed();

	glDisable(GL_BLEND);

	m_gl.DepthMask(true);
	m_gl.Enable(GL::Capability::DepthTest);

	m_gbuffer.bind();
	m_gl.Clear(GL::Buffer::Color | GL::Buffer::Depth);
}

void gfx::model::ModelRenderer::present(GL::Framebuffer* framebuffer)
{
	m_gl.DepthMask(false);
	m_gl.Disable(GL::Capability::DepthTest);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// PostFX pass
	m_gl.BindFramebuffer(m_fbo);
	m_gl.Clear(GL::Buffer::Color);

	m_gl.UseProgram(m_postfx);

	m_gl.BindTexture(m_gbuffer.GetTexture(0), 0);
	m_gl.BindTexture(m_gbuffer.GetTexture(1), 1);
	m_gl.BindTexture(m_gbuffer.GetTexture(2), 2);
	m_gl.BindTexture(m_gbuffer.GetDepthTexture(), 3);

	m_postfx.SetUniform("color_tex", 0);
	m_postfx.SetUniform("normal_tex", 1);
	m_postfx.SetUniform("position_tex", 2);
	m_postfx.SetUniform("depth_tex", 3);
	m_postfx.SetUniform("time", m_time);
	m_postfx.SetUniform("render_distance", m_cam.getRenderDistance());
	m_postfx.SetUniform("camera", m_cam.getPosition());

	m_gl.DrawArrays(m_vao, GL::Primitive::Triangles, 0, 6);

	// anti-aliasing pass
	if (framebuffer)
		m_gl.BindFramebuffer(*framebuffer);
	else
		m_gl.BindFramebuffer();

	m_gl.Clear(GL::Buffer::Color | GL::Buffer::Depth);

	m_gl.UseProgram(m_aa);

	m_gl.BindTexture(m_fbo.GetTexture(), 0);

	m_aa.SetUniform("color_tex", 0);

	m_gl.DrawArrays(m_vao, GL::Primitive::Triangles, 0, 6);
}
