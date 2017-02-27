/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <stdexcept>
#include <Doboz/Compressor.h>
#include <Doboz/Decompressor.h>
#include "common/Encoder.hpp"
#include "resource/ArchiveReader.hpp"

resource::ArchiveReader::ArchiveReader(const char* archive, raz::IMemoryPool* memory) :
	m_archive(archive, std::ios_base::in | std::ios_base::binary),
	m_memory(memory),
	m_file_table(memory)
{
	readFileData();
}

resource::ArchiveReader::ArchiveReader(const wchar_t* archive, raz::IMemoryPool* memory) :
	m_archive(archive, std::ios_base::in | std::ios_base::binary),
	m_memory(memory),
	m_file_table(memory)
{
	readFileData();
}

size_t resource::ArchiveReader::getFileCount() const
{
	return m_file_table.size();
}

bool resource::ArchiveReader::getFileInfo(const char* filename, FileInfo& file_info) const
{
	for (size_t i = 0, count = m_file_table.size(); i < count; ++i)
	{
		auto& file = m_file_table[i];

		if (file.filename.compare(filename) == 0)
		{
			file_info.file_index = i;
			file_info.filename = file.filename.c_str();
			file_info.size = file.original_size;
			return true;
		}
	}

	return false;
}

bool resource::ArchiveReader::getFileInfo(size_t file_index, FileInfo& file_info) const
{
	if (file_index >= m_file_table.size())
		return false;

	auto& file = m_file_table[file_index];

	file_info.filename = file.filename.c_str();
	file_info.size = file.original_size;
	return true;
}

bool resource::ArchiveReader::decompress(size_t file_index, void* destination)
{
	if (file_index >= m_file_table.size())
		return false;

	auto& file = m_file_table[file_index];

	// set up buffer for compressed data
	std::vector<char, raz::Allocator<char>> compressed_data(m_memory);
	compressed_data.resize(file.compressed_size);

	// read compressed data to buffer
	m_archive.seekg(file.position);
	m_archive.read(&compressed_data[0], file.compressed_size);

	// decompress
	doboz::Result result = doboz::Decompressor().decompress(&compressed_data[0], file.compressed_size, destination, file.original_size);
	return (result == doboz::RESULT_OK);
}

void resource::ArchiveReader::readFileData()
{
	if (!m_archive.is_open())
		throw std::runtime_error("couldn't open archive");

	m_archive.seekg(0, std::ios::end);
	const std::streampos end_pos = m_archive.tellg();
	m_archive.seekg(0, std::ios::beg);

	while (m_archive)
	{
		m_file_table.emplace_back(m_memory);
		InternalFileInfo& file = m_file_table.back();

		// read filename length
		uint16_t filename_length;
		m_archive.read(reinterpret_cast<char*>(&filename_length), sizeof(uint16_t));

		// read filename
		file.filename.resize(filename_length);
		m_archive.read(&file.filename[0], filename_length);

		// decrypt filename
		common::decode(reinterpret_cast<unsigned char*>(&file.filename[0]), file.filename.size());

		// read original size
		m_archive.read(reinterpret_cast<char*>(&file.original_size), sizeof(uint32_t));

		// read compressed size
		m_archive.read(reinterpret_cast<char*>(&file.compressed_size), sizeof(uint32_t));

		// get pointer to compressed content
		file.position = static_cast<size_t>(m_archive.tellg());

		// skip compressed content
		m_archive.seekg(file.compressed_size, std::ios_base::cur);

		if (m_archive.tellg() == end_pos)
			break;
	}
}

resource::ArchiveReader::InternalFileInfo::InternalFileInfo(raz::IMemoryPool* memory) :
	filename(memory),
	position(0),
	original_size(0),
	compressed_size(0)
{
}

resource::ArchiveReader::InternalFileInfo::InternalFileInfo(InternalFileInfo&& other) :
	filename(other.filename),
	position(other.position),
	original_size(other.original_size),
	compressed_size(other.compressed_size)
{
}
