/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <cstring>
#include <stdexcept>
#include "ui/core/Vertex.hpp"

static const ui::core::VertexAttribute vertex_attributes[] = {
	{ "position", GL::Type::Float,        3, sizeof(ui::core::Vertex), 0 },
	{ "normal",   GL::Type::Float,        3, sizeof(ui::core::Vertex), sizeof(float) * 3 },
	{ "color",    GL::Type::UnsignedByte, 4, sizeof(ui::core::Vertex), sizeof(float) * 6 }
};

int ui::core::Vertex::getVertexAttributeCount()
{
	return sizeof(vertex_attributes) / sizeof(ui::core::VertexAttribute);
}

const ui::core::VertexAttribute& ui::core::Vertex::getVertexAttribute(int n)
{
	if (n < sizeof(vertex_attributes) / sizeof(ui::core::VertexAttribute))
		return vertex_attributes[n];
	else
		throw std::out_of_range({});
}

const ui::core::VertexAttribute* ui::core::Vertex::getVertexAttribute(const char* name)
{
	for (size_t i = 0, len = sizeof(vertex_attributes) / sizeof(ui::core::VertexAttribute); i < len; ++i)
	{
		if (std::strcmp(vertex_attributes[i].name, name) == 0)
			return &vertex_attributes[i];
	}

	return nullptr;
}
