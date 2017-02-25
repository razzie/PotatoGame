/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "gfx/core/Vertex.hpp"

static const gfx::core::VertexAttribute vertex_attributes[] = {
	{ "position", GL::Type::Float,        3, sizeof(gfx::core::Vertex), 0 },
	{ "normal",   GL::Type::Float,        3, sizeof(gfx::core::Vertex), sizeof(float) * 3 },
	{ "color",    GL::Type::UnsignedByte, 4, sizeof(gfx::core::Vertex), sizeof(float) * 6 }
};

unsigned gfx::core::Vertex::getVertexAttributeCount()
{
	return sizeof(vertex_attributes) / sizeof(gfx::core::VertexAttribute);
}

const gfx::core::VertexAttribute* gfx::core::Vertex::getVertexAttribute(unsigned n)
{
	if (n < sizeof(vertex_attributes) / sizeof(gfx::core::VertexAttribute))
		return &vertex_attributes[n];
	else
		return nullptr;
}


static const gfx::core::VertexAttribute animated_vertex_attributes[] = {
	{ "begin_position", GL::Type::Float,        3, sizeof(gfx::core::AnimatedVertex), 0 },
	{ "end_position",   GL::Type::Float,        3, sizeof(gfx::core::AnimatedVertex), sizeof(float) * 3 },
	{ "normal",         GL::Type::Float,        3, sizeof(gfx::core::AnimatedVertex), sizeof(float) * 6 },
	{ "color",          GL::Type::UnsignedByte, 4, sizeof(gfx::core::AnimatedVertex), sizeof(float) * 9 }
};

unsigned gfx::core::AnimatedVertex::getVertexAttributeCount()
{
	return 0;
}

const gfx::core::VertexAttribute* gfx::core::AnimatedVertex::getVertexAttribute(unsigned n)
{
	return nullptr;
}


static const gfx::core::VertexAttribute textured_vertex_attributes[] = {
	{ "position", GL::Type::Float,        3, sizeof(gfx::core::TexturedVertex), 0 },
	{ "normal",   GL::Type::Float,        3, sizeof(gfx::core::TexturedVertex), sizeof(float) * 3 },
	{ "color",    GL::Type::UnsignedByte, 4, sizeof(gfx::core::TexturedVertex), sizeof(float) * 6 },
	{ "tcoords",  GL::Type::Float,        2, sizeof(gfx::core::TexturedVertex), sizeof(float) * 6 + sizeof(unsigned char) * 4 }
};

unsigned gfx::core::TexturedVertex::getVertexAttributeCount()
{
	return 0;
}

const gfx::core::VertexAttribute* gfx::core::TexturedVertex::getVertexAttribute(unsigned n)
{
	return nullptr;
}
