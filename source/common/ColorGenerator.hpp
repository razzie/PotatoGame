/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

#include <GL/Util/Color.hpp>

namespace common
{
	class ColorGenerator
	{
	public:
		ColorGenerator();
		GL::Color operator[](size_t n) const;

	private:
		GL::Color m_table[6];
	};
}
