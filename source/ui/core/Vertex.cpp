/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "ui/core/Vertex.hpp"

static const ui::core::VertexAttribute vertex_attributes[] = {
	{ "position", GL::Type::Float,        3, sizeof(ui::core::Vertex), 0 },
	{ "normal",   GL::Type::Float,        3, sizeof(ui::core::Vertex), sizeof(float) * 3 },
	{ "color",    GL::Type::UnsignedByte, 4, sizeof(ui::core::Vertex), sizeof(float) * 6 }
};

unsigned ui::core::Vertex::getVertexAttributeCount()
{
	return sizeof(vertex_attributes) / sizeof(ui::core::VertexAttribute);
}

const ui::core::VertexAttribute* ui::core::Vertex::getVertexAttribute(unsigned n)
{
	if (n < sizeof(vertex_attributes) / sizeof(ui::core::VertexAttribute))
		return &vertex_attributes[n];
	else
		return nullptr;
}


static const ui::core::VertexAttribute animated_vertex_attributes[] = {
	{ "begin_position", GL::Type::Float,        3, sizeof(ui::core::Vertex), 0 },
	{ "end_position",   GL::Type::Float,        3, sizeof(ui::core::Vertex), sizeof(float) * 3 },
	{ "normal",         GL::Type::Float,        3, sizeof(ui::core::Vertex), sizeof(float) * 6 },
	{ "color",          GL::Type::UnsignedByte, 4, sizeof(ui::core::Vertex), sizeof(float) * 9 }
};

unsigned ui::core::AnimatedVertex::getVertexAttributeCount()
{
	return 0;
}

const ui::core::VertexAttribute* ui::core::AnimatedVertex::getVertexAttribute(unsigned n)
{
	return nullptr;
}


static const ui::core::VertexAttribute textured_vertex_attributes[] = {
	{ "position", GL::Type::Float,        3, sizeof(ui::core::Vertex), 0 },
	{ "normal",   GL::Type::Float,        3, sizeof(ui::core::Vertex), sizeof(float) * 3 },
	{ "color",    GL::Type::UnsignedByte, 4, sizeof(ui::core::Vertex), sizeof(float) * 6 },
	{ "tcoords",  GL::Type::Float,        2, sizeof(ui::core::Vertex), sizeof(float) * 6 + sizeof(unsigned char) * 4 }
};

unsigned ui::core::TexturedVertex::getVertexAttributeCount()
{
	return 0;
}

const ui::core::VertexAttribute* ui::core::TexturedVertex::getVertexAttribute(unsigned n)
{
	return nullptr;
}
