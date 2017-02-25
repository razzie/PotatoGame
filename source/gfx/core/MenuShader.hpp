/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <GL/GL/Program.hpp>

namespace gfx
{
namespace core
{
	class MenuShader
	{
	public:
		MenuShader();
		const GL::Program& getProgram() const;

	private:
		GL::Program m_program;
	};
}
}
