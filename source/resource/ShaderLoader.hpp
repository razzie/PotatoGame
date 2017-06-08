/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <map>
#include <string>
#include <GL/GL/Program.hpp>
#include <raz/memory.hpp>
#include "resource/ArchiveReader.hpp"

namespace resource
{
	class ShaderLoaderError : public std::exception
	{
	public:
		virtual const char* what() const;
	};

	class ShaderLoader
	{
	public:
		ShaderLoader(raz::IMemoryPool* memory);
		GL::Program& get(const char* shader_name);

	private:
		typedef std::basic_string<char, std::char_traits<char>, raz::Allocator<char>> String;
		typedef std::map<String, GL::Program, std::less<String>, raz::Allocator<std::pair<const String, GL::Program>>> ShaderMap;

		raz::IMemoryPool* m_memory;
		ArchiveReader m_archive;
		ShaderMap m_shaders;

		bool loadShader(const char* shader_name, GL::Program& shader);
	};
}
