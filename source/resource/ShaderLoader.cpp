/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <string>
#include "resource/ShaderLoader.hpp"

resource::ShaderLoader::ShaderLoader(raz::IMemoryPool* memory) :
	m_memory(memory),
	m_archive("shader.res", memory),
	m_shaders(memory)
{
}

GL::Program& resource::ShaderLoader::get(const char* shader_name)
{
	String name(shader_name, m_memory);

	auto it = m_shaders.find(name);
	if (it == m_shaders.end())
	{
		GL::Program shader;

		if (!loadShader(shader_name, shader))
			throw ShaderLoaderError();

		it = m_shaders.emplace(name, std::move(shader)).first;
	}

	return it->second;
}

bool resource::ShaderLoader::loadShader(const char* shader_name, GL::Program& program)
{
	String filename(shader_name, m_memory);
	filename += ".vert";

	ArchiveReader::FileInfo vert_info;
	if (!m_archive.getFileInfo(filename.c_str(), vert_info))
		return false;

	filename = shader_name;
	filename += ".frag";

	ArchiveReader::FileInfo frag_info;
	if (!m_archive.getFileInfo(filename.c_str(), frag_info))
		return false;

	// at this point we made sure both vertex and fragment shaders exist, let's decompress them
	String vert_data(m_memory);
	vert_data.resize(vert_info.size);
	if (!m_archive.decompress(vert_info.file_index, &vert_data[0]))
		return false;

	String frag_data(m_memory);
	frag_data.resize(frag_info.size);
	if (!m_archive.decompress(frag_info.file_index, &frag_data[0]))
		return false;

	// compiling the shaders
	GL::Shader vert_shader(GL::ShaderType::Vertex, vert_data.c_str());
	GL::Shader frag_shader(GL::ShaderType::Fragment, frag_data.c_str());

	// attach and link them
	program.Attach(vert_shader);
	program.Attach(frag_shader);
	program.Link();

	return true;
}

const char* resource::ShaderLoaderError::what() const
{
	return "Could not load shader";
}
