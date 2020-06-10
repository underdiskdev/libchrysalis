// libchrysalis is subject to the terms of the GNU Lesser General Public License v3.0
// If a copy of the LGPLv3 was not distributed with this copy of the source code,
// you can obtain one at https://www.gnu.org/licenses/lgpl-3.0.en.html

/**
 * @file
 * @brief Module loading header for windows systems
 * @author underdisk
 * @date June 2020 - June 2020
 * @copyright GNU Lesser General Public License v3.0
 */

#pragma once

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <strsafe.h>

typedef HMODULE ____CHRYSALIS_IMP_HANDLE_T;

____CHRYSALIS_IMP_HANDLE_T ____chrysalis_imp_handle__;

void chs_private_print_win32_error(DWORD errorMessageID)
{
	LPSTR messageBuffer = NULL;
	size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

	MessageBoxA(
		NULL,
		messageBuffer,
		NULL,
		MB_OK | MB_ICONERROR
	);

	LocalFree(messageBuffer);
}

void chs_private_load_library(const char* path)
{
	____chrysalis_imp_handle__ = LoadLibraryExA(path, NULL, LOAD_LIBRARY_SEARCH_DEFAULT_DIRS);
	if (____chrysalis_imp_handle__ == NULL)
	{
		DWORD error = GetLastError();
		chs_private_print_win32_error(error);
        exit(-1);
	}
}

void chs_private_close_library()
{
	FreeLibrary(____chrysalis_imp_handle__);
}

void* chs_private_load_symbol(const char* symbol)
{
	void* fun = GetProcAddress(____chrysalis_imp_handle__, symbol);
	if (fun == NULL)
	{
		DWORD error = GetLastError();
		chs_private_print_win32_error(error);
        exit(-1);
	}

	return fun;
}