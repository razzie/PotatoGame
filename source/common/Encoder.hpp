/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once

namespace common
{
	void encode(unsigned char* buf, size_t len);
	void decode(unsigned char* buf, size_t len);

	void genShuffleArray();
	void genDeshuffleArray(const unsigned char* shuffle);
}
