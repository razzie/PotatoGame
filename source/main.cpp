/*
 * Copyright (C) G�bor G�rzs�ny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <iostream>
#include <exception>
#include <Windows.h>
#include "Potato.hpp"

int main(int argc, char** argv)
{
	try
	{
		return Potato(argc, argv).run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		MessageBoxA(NULL, e.what(), "Error", MB_OK | MB_ICONERROR);
	}

	return -1;
}
