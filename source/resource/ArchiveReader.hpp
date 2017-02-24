/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <cstdint>
#include <fstream>
#include <string>
#include <vector>
#include <raz/memory.hpp>

namespace resource
{
	class ArchiveReader
	{
	public:
		struct FileInfo
		{
			const char* filename;
			size_t size;
		};

		ArchiveReader(const char*    archive, raz::IMemoryPool* memory = nullptr);
		ArchiveReader(const wchar_t* archive, raz::IMemoryPool* memory = nullptr);
		size_t getFileCount() const;
		bool getFileIndex(const char* filename, size_t& file_index) const;
		bool getFileInfo(size_t file_index, FileInfo& file_info) const;
		bool decompress(size_t file_index, void* destination);

	private:
		template<class T> using Vector = std::vector<T, raz::Allocator<T>>;
		typedef std::basic_string<char, std::char_traits<char>, raz::Allocator<char>> String;

		struct InternalFileInfo
		{
			InternalFileInfo(raz::IMemoryPool* memory = nullptr);
			InternalFileInfo(InternalFileInfo&& other);

			String filename;
			uint32_t position;
			uint32_t original_size;
			uint32_t compressed_size;
		};

		std::ifstream m_archive;
		raz::IMemoryPool* m_memory;
		Vector<InternalFileInfo> m_file_table;

		void readFileData();
	};
}
