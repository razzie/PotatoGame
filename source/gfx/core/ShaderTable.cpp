/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "resource/ShaderLoader.hpp"
#include "gfx/core/ShaderTable.hpp"

gfx::core::ShaderTable::ShaderTable(raz::IMemoryPool* memory)
{
	resource::ShaderLoader loader(memory);
	loader.loadShader("gui", m_gui);
	loader.loadShader("horizon", m_horizon);
	loader.loadShader("hub", m_hub);
}

GL::Program& gfx::core::ShaderTable::getGUIShader()
{
	return m_gui;
}

GL::Program& gfx::core::ShaderTable::getHorizonShader()
{
	return m_horizon;
}

GL::Program& gfx::core::ShaderTable::getHubShader()
{
	return m_hub;
}
