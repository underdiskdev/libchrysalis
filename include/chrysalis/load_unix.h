// libchrysalis is subject to the terms of the GNU Lesser General Public License v3.0
// If a copy of the LGPLv3 was not distributed with this copy of the source code,
// you can obtain one at https://www.gnu.org/licenses/lgpl-3.0.en.html

/**
 * @file
 * @brief Module loading header for Unix(-like) systems
 * @author underdisk
 * @date June 2020 - June 2020
 * @copyright GNU Lesser General Public License v3.0
 */

#pragma once

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

typedef void* ____CHRYSALIS_IMP_HANDLE_T;

____CHRYSALIS_IMP_HANDLE_T ____chrysalis_imp_handle__;

void chs_private_load_library(const char* path)
{
	dlerror(); //clearing any error
	____chrysalis_imp_handle__ = dlopen(path, RTLD_NOW);
	if (____chrysalis_imp_handle__ == NULL)
	{
		fprintf(stderr, "Could not load libchrysalis implementation: %s\n", dlerror());
        exit(-1);
	}
}

void chs_private_close_library()
{
	dlclose(____chrysalis_imp_handle__);
}

void* chs_private_load_symbol(const char* symbol)
{
	dlerror(); //clearing any error
	void* fun = dlsym(____chrysalis_imp_handle__, symbol);
	if (fun == NULL)
	{
		fprintf(stderr, "Could not load libchrysalis symbol: %s\n", dlerror());
        exit(-1);
	}

	return fun;
}