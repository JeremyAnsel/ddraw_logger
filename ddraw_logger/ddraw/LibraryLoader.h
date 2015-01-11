// Copyright (c) 2014 Jérémy Ansel
// Licensed under the MIT license. See LICENSE.txt

#pragma once

#include "common.h"

class LibraryLoader
{
public:
	LibraryLoader(LPCSTR lpLibFileName)
	{
		char path[MAX_PATH];
		GetSystemDirectoryA(path, MAX_PATH);
		strcat_s(path, "\\");
		strcat_s(path, lpLibFileName);

		this->_module = LoadLibraryA(path);
	}

	~LibraryLoader()
	{
		if (this->_module)
		{
			FreeLibrary(this->_module);
		}
	}

	FARPROC GetAddress(LPCSTR lpProcName) const throw ()
	{
		return GetProcAddress(this->_module, lpProcName);
	}

private:
	HMODULE _module;
};
