/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <GL/GL/Program.hpp>

namespace ui
{
namespace core
{
	class HubShader
	{
	public:
		HubShader();
		const GL::Program& getProgram() const;

	private:
		GL::Program m_program;
	};
}
}
