/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <array>
//#include <GL/GL/Texture.hpp>
//#include <GL/GL/Renderbuffer.hpp>
#include <GL/GL/Framebuffer.hpp>

#define PUSHSTATE() GLint restoreId; glGetIntegerv( GL_DRAW_FRAMEBUFFER_BINDING, &restoreId );
#define POPSTATE() glBindFramebuffer( GL_DRAW_FRAMEBUFFER, restoreId );

namespace gfx
{
namespace core
{
	template<size_t N>
	class GBuffer
	{
	public:
		GBuffer(unsigned width, unsigned height)
		{
			PUSHSTATE()

			// Create FBO		
			m_gc.Create(m_obj, glGenFramebuffers, glDeleteFramebuffers);
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_obj);

			GLenum drawbuffers[N];

			for (size_t i = 0; i < N; ++i)
			{
				// Create texture to hold color buffer
				GL::Texture& tex = m_attachments[i];
				tex.Image2D(0, GL::DataType::Float, Format::RGB, width, height, GL::InternalFormat::RGB32F);
				tex.SetWrapping(GL::Wrapping::ClampEdge, GL::Wrapping::ClampEdge);
				tex.SetFilters(GL::Filter::Linear, GL::Filter::Linear);
				glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, tex, 0);
				drawbuffers[i] = GL_COLOR_ATTACHMENT0 + i;
			}

			// Create renderbuffer to hold depth buffer
			glBindTexture(GL_TEXTURE_2D, m_depth);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
			m_depth.SetWrapping(GL::Wrapping::ClampEdge, GL::Wrapping::ClampEdge);
			m_depth.SetFilters(GL::Filter::Nearest, GL::Filter::Nearest);
			glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texDepth, 0);
			glDrawBuffers(N, drawbuffers);

			// Check
			if (glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				throw GL::FramebufferException();

			POPSTATE()
		}

		GBuffer(const GBuffer& other)
		{
			m_gc.Copy(other.m_obj, m_obj);
			m_attachments = other.m_attachments;
			m_depth = other.m_depth;
		}

		~GBuffer()
		{
			m_gc.Destroy(m_obj);
		}

		operator GLuint() const
		{
			return m_obj;
		}

		const GBuffer& operator=(const GBuffer& other)
		{
			m_gc.Copy(other.m_obj, m_obj, true);
			m_attachments = other.m_attachments;
			m_depth = other.m_depth;
			return *this;
		}

		const Texture& GetTexture(size_t n)
		{
			return m_attachments[n];
		}

		const Texture& GetDepthTexture()
		{
			return m_depth;
		}

	private:
		static GL::GC m_gc;
		GLuint m_obj;
		std::array<GL::Texture, N> m_attachments;
		GL::Texture m_depth;
	};
}
}
