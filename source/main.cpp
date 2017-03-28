/*
 * Copyright (C) Gábor Görzsöny <gabor@gorzsony.com> - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <iostream>
#include <exception>
#include <Windows.h>
#include "Potato.hpp"

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow)
{
	try
	{
		return Potato(1, &lpCmdLine).run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		MessageBoxA(NULL, e.what(), "Error", MB_OK | MB_ICONERROR);
	}

	return -1;
}
