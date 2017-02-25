/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <vector>
#include <Rocket/Core/String.h>
#include <Rocket/Core/FileInterface.h>
#include <raz/memory.hpp>
#include "resource/ArchiveReader.hpp"

namespace gfx
{
namespace gui
{
	class RocketFileInterface : public Rocket::Core::FileInterface
	{
	public:
		struct File
		{
			File(raz::IMemoryPool* memory = nullptr) : data(memory), read_position(0)
			{
			}

			std::vector<char, raz::Allocator<char>> data;
			size_t read_position;
		};

		RocketFileInterface(raz::IMemoryPool* memory = nullptr);
		resource::ArchiveReader* getArchive();
		virtual Rocket::Core::FileHandle Open(const Rocket::Core::String& path);
		virtual void Close(Rocket::Core::FileHandle file_handle);
		virtual size_t Read(void* buffer, size_t size, Rocket::Core::FileHandle file_handle);
		virtual bool Seek(Rocket::Core::FileHandle file_handle, long offset, int origin);
		virtual size_t Tell(Rocket::Core::FileHandle file_handle);

	private:
		raz::IMemoryPool* m_memory;
		resource::ArchiveReader m_archive;
	};
}
}
