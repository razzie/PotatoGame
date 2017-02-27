/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <cstdint>
#include <vector>
#include "common/Encoder.hpp"
#include "resource/ArchiveWriter.hpp"

resource::ArchiveWriter::ArchiveWriter(const char* archive, bool append)
{
	std::ios::openmode mode = std::ios::out | std::ios::binary;

	if (append)
		mode |= std::ios::app;
	else
		mode |= std::ios::trunc;

	m_archive.open(archive, mode);
}

resource::ArchiveWriter::ArchiveWriter(const wchar_t* archive, bool append)
{
	std::ios::openmode mode = std::ios::out | std::ios::binary;

	if (append)
		mode |= std::ios::app;
	else
		mode |= std::ios::trunc;

	m_archive.open(archive, mode);
}

bool resource::ArchiveWriter::compress(const char* source_filename, const char* dest_filename, raz::IMemoryPool* memory)
{
	std::ifstream file(source_filename, std::ios_base::in | std::ios_base::binary);
	return compressInternal(file, dest_filename, memory);
}

bool resource::ArchiveWriter::compress(const wchar_t* source_filename, const char* dest_filename, raz::IMemoryPool* memory)
{
	std::ifstream file(source_filename, std::ios_base::in | std::ios_base::binary);
	return compressInternal(file, dest_filename, memory);
}

bool resource::ArchiveWriter::compressInternal(std::ifstream& file, const char* dest_filename, raz::IMemoryPool* memory)
{
	if (!file.is_open())
		return false;

	// get original file size
	file.seekg(0, std::ios::end);
	const uint32_t original_size = static_cast<uint32_t>(file.tellg());
	file.seekg(0, std::ios::beg);

	// get estimated compressed size
	uint32_t compressed_size = static_cast<uint32_t>(doboz::Compressor::getMaxCompressedSize(original_size));

	// allocate buffer for both original and compressed file data
	std::vector<char, raz::Allocator<char>> buffer(memory);
	buffer.resize(original_size + compressed_size);

	// read file data
	if (!file.read(buffer.data(), original_size))
		return false;

	// compress data (also updates compressed_size)
	doboz::Result result = m_compressor.compress(&buffer[0], original_size, &buffer[original_size], buffer.size(), compressed_size);
	if (result != doboz::RESULT_OK)
		return false;

	// encrypt file name
	String filename(dest_filename, memory);
	const uint16_t filename_length = static_cast<uint16_t>(filename.size());
	common::encode(reinterpret_cast<unsigned char*>(&filename[0]), filename_length);

	// write filename length
	m_archive.write(reinterpret_cast<const char*>(&filename_length), sizeof(uint16_t));

	// write filename
	m_archive.write(&filename[0], filename_length);

	// write original size
	m_archive.write(reinterpret_cast<const char*>(&original_size), sizeof(uint32_t));

	// write compressed size
	m_archive.write(reinterpret_cast<const char*>(&compressed_size), sizeof(uint32_t));

	// write compressed data
	m_archive.write(&buffer[original_size], compressed_size);

	m_archive.flush();
	return static_cast<bool>(m_archive);
}
