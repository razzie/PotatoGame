/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <cstring>
#include <GL/Platform.hpp>
#include <GL/Math/Vec2.hpp>
#include <GL/Math/Vec3.hpp>
#include <GL/Util/Color.hpp>

namespace gfx
{
namespace core
{
	struct VertexAttribute
	{
		const char* name;
		GL::Type::type_t type;
		GL::uint count;
		GL::uint stride;
		intptr_t offset;
	};

	struct Vertex
	{
		GL::Vec3 position;
		GL::Vec3 normal;
		GL::Color color;

		static unsigned getVertexAttributeCount();
		static const VertexAttribute* getVertexAttribute(unsigned n);
	};

	struct AnimatedVertex
	{
		GL::Vec3 begin_position;
		GL::Vec3 end_position;
		GL::Vec3 normal;
		GL::Color color;

		static unsigned getVertexAttributeCount();
		static const VertexAttribute* getVertexAttribute(unsigned n);
	};

	struct TexturedVertex
	{
		GL::Vec3 position;
		GL::Vec3 normal;
		GL::Color color;
		GL::Vec2 tcoords;

		static unsigned getVertexAttributeCount();
		static const VertexAttribute* getVertexAttribute(unsigned n);
	};

	template<class VertexType>
	const VertexAttribute* getVertexAttributeByName(const char* name)
	{
		for (unsigned i = 0, len = VertexType::getVertexAttributeCount(); i < len; ++i)
		{
			const VertexAttribute* attrib = VertexType::getVertexAttribute(i);

			if (std::strcmp(attrib->name, name) == 0)
				return attrib;
		}

		return nullptr;
	}
}
}
