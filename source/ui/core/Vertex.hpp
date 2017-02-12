/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <GL/Platform.hpp>
#include <GL/Math/Vec3.hpp>
#include <GL/Util/Color.hpp>

namespace ui
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

		static int getVertexAttributeCount();
		static const VertexAttribute& getVertexAttribute(int n);
		static const VertexAttribute* getVertexAttribute(const char* name);
	};
}
}
