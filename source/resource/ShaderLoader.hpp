/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <GL/GL/Program.hpp>
#include <raz/memory.hpp>
#include "resource/ArchiveReader.hpp"

namespace resource
{
	class ShaderLoader
	{
	public:
		ShaderLoader(raz::IMemoryPool* memory);
		bool loadShader(const char* shader_name, GL::Program& shader);

	private:
		raz::IMemoryPool* m_memory;
		ArchiveReader m_archive;
	};
}
