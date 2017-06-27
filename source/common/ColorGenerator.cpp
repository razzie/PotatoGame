/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "common/ColorGenerator.hpp"

#pragma warning(push)
#pragma warning(disable: 4267) // possible loss of data

common::ColorGenerator::ColorGenerator() :
	m_table{
		GL::Color(255, 0, 0),
		GL::Color(0, 255, 0),
		GL::Color(0, 0, 255),
		GL::Color(255, 255, 0),
		GL::Color(255, 0, 255),
		GL::Color(0, 255, 255)
	}
{
}

GL::Color common::ColorGenerator::operator[](size_t n) const
{
	GL::Color base = m_table[n % 6];

	for (size_t iter = n / 6; iter > 0; iter /= 6)
	{
		GL::Color sub = m_table[iter % 6];
		sub.R /= iter + 1;
		sub.G /= iter + 1;
		sub.B /= iter + 1;

		base.R -= sub.R;
		base.G -= sub.G;
		base.B -= sub.B;
	}

	return base;
}

#pragma warning(pop)
