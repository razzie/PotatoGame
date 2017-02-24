/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <fstream>
#include <string>
#include <raz/memory.hpp>

namespace resource
{
	class ArchiveWriter
	{
	public:
		ArchiveWriter(const char*    archive, bool append = true);
		ArchiveWriter(const wchar_t* archive, bool append = true);
		bool compress(const char*    source_filename, const char* dest_filename, raz::IMemoryPool* memory = nullptr);
		bool compress(const wchar_t* source_filename, const char* dest_filename, raz::IMemoryPool* memory = nullptr);

	private:
		typedef std::basic_string<char, std::char_traits<char>, raz::Allocator<char>> String;

		std::ofstream m_archive;

		bool compressInternal(std::ifstream& source, const char* dest_filename, raz::IMemoryPool* memory);
	};
}
