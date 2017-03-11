/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <GL/GL/Program.hpp>
#include <raz/memory.hpp>

namespace gfx
{
namespace core
{
	class ShaderTable
	{
	public:
		ShaderTable(raz::IMemoryPool* memory = nullptr);
		GL::Program& getGUIShader();
		GL::Program& getHorizonShader();
		GL::Program& getHubShader();

	private:
		GL::Program m_gui;
		GL::Program m_horizon;
		GL::Program m_hub;
	};
}
}
