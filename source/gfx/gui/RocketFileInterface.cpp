/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <cstring>
#include "gfx/gui/RocketFileInterface.hpp"

gfx::gui::RocketFileInterface::RocketFileInterface(resource::ArchiveReader& archive, raz::IMemoryPool* memory) :
	m_archive(archive),
	m_memory(memory)
{
}

Rocket::Core::FileHandle gfx::gui::RocketFileInterface::Open(const Rocket::Core::String& path)
{
	resource::ArchiveReader::FileInfo file_info;
	if (!m_archive.getFileInfo(path.CString(), file_info))
	{
		return 0;
	}

	raz::Allocator<File> alloc(m_memory);
	File* file = std::allocator_traits<raz::Allocator<File>>::allocate(alloc, 1);
	std::allocator_traits<raz::Allocator<File>>::construct(alloc, file, m_memory);

	file->data.resize(file_info.size);
	m_archive.decompress(file_info.file_index, file->data.data());

	return Rocket::Core::FileHandle(file);
}

void gfx::gui::RocketFileInterface::Close(Rocket::Core::FileHandle file_handle)
{
	File* file = reinterpret_cast<File*>(file_handle);

	raz::Allocator<File> alloc(m_memory);
	std::allocator_traits<raz::Allocator<File>>::destroy(alloc, file);
	std::allocator_traits<raz::Allocator<File>>::deallocate(alloc, file, 1);
}

size_t gfx::gui::RocketFileInterface::Read(void* buffer, size_t size, Rocket::Core::FileHandle file_handle)
{
	File* file = reinterpret_cast<File*>(file_handle);

	if (size > file->data.size() - file->read_position)
		size = file->data.size() - file->read_position;

	std::memcpy(buffer, file->data.data(), size);
	file->read_position += size;

	return size;
}

bool gfx::gui::RocketFileInterface::Seek(Rocket::Core::FileHandle file_handle, long offset, int origin)
{
	File* file = reinterpret_cast<File*>(file_handle);

	if (origin == SEEK_SET)
	{
		file->read_position = 0;
	}
	else if (origin == SEEK_END)
	{
		file->read_position = file->data.size();
	}

	if (offset < -static_cast<long>(file->read_position))
		return false;

	file->read_position += offset;
	return true;
}

size_t gfx::gui::RocketFileInterface::Tell(Rocket::Core::FileHandle file_handle)
{
	File* file = reinterpret_cast<File*>(file_handle);

	return file->read_position;
}
