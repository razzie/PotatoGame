/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "gfx/scene/PostFX.hpp"
#include "gfx/scene/Scene.hpp"

static const float vertices[] = {
	-1.f, -1.f,
	 1.f, -1.f,
	-1.f,  1.f,

	 1.f,  1.f,
	-1.f,  1.f,
	 1.f, -1.f
};

gfx::scene::PostFX::PostFX(unsigned width, unsigned height, float render_distance, resource::ShaderLoader& shader_loader) :
	m_postfx(shader_loader.get("postfx")),
	m_vbo(vertices, sizeof(vertices), GL::BufferUsage::StaticCopy)
{
	m_vao.BindAttribute(m_postfx.GetAttribute("position"), m_vbo, GL::Type::Float, 2, sizeof(float) * 2, 0);
}

gfx::scene::PostFX::~PostFX()
{
}

void gfx::scene::PostFX::render(Scene& scene)
{
	GL::Context& gl = scene.getContext();
	GBuffer& gbuffer = scene.getGBuffer();

	gl.DepthMask(false);
	gl.Disable(GL::Capability::DepthTest);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	gl.BindFramebuffer();
	gl.Clear(GL::Buffer::Color | GL::Buffer::Depth);

	gl.UseProgram(m_postfx);

	gl.BindTexture(gbuffer.GetTexture(0), 0);
	gl.BindTexture(gbuffer.GetTexture(1), 1);
	gl.BindTexture(gbuffer.GetTexture(2), 2);
	gl.BindTexture(gbuffer.GetDepthTexture(), 3);

	m_postfx.SetUniform("color_tex", 0);
	m_postfx.SetUniform("normal_tex", 1);
	m_postfx.SetUniform("position_tex", 2);
	m_postfx.SetUniform("depth_tex", 3);
	m_postfx.SetUniform("time", scene.getElapsedTime());
	m_postfx.SetUniform("render_distance", scene.getCamera().getRenderDistance());
	m_postfx.SetUniform("camera", scene.getCamera().getPosition());

	gl.DrawArrays(m_vao, GL::Primitive::Triangles, 0, 6);
}
