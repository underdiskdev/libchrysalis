// libchrysalis is subject to the terms of the GNU Lesser General Public License v3.0
// If a copy of the LGPLv3 was not distributed with this copy of the source code,
// you can obtain one at https://www.gnu.org/licenses/lgpl-3.0.en.html

/**
 * @file
 * @brief Main header file
 * @author underdisk
 * @date May 2020 - June 2020
 * @copyright GNU Lesser General Public License v3.0
 */

/*! \mainpage libchrysalis
 *
 * \section intro_sec Introduction
 *
 * libchrysalis is a C library that acts as an abstraction layer for graphics API (OpenGL, Vulkan...)
 * It consists of header files and different implementations for each graphics API
 * 
 * \section gettingstarted_sec Getting started
 *
 * The library is still in it's very-early stage. You can look at basic functions in the chrysalis.h header file
 * 
 * \section install_sec License
 * 
 * libchrysalis is subject to the terms of the GNU Lesser General Public License v3.0.
 * you can obtain a copy of the license at https://www.gnu.org/licenses/lgpl-3.0.en.html
 */

#pragma once

#include <stdio.h>
#include <string.h>

#include "load.h"
#include "gfx_api_info.h"
#include "renderer.h"
#include "util.h"
#include "common.h"
#include "whereami.c"

#define __CHRYSALIS_VERSION_MAJOR__ 0
#define __CHRYSALIS_VERSION_MINOR__ 2
#define __CHRYSALIS_VERSION_PATCH__ 0 // PATCH updates are not allowed to touch the API and therefore are not referenced in the headers

// Function pointer list for loading
void (*__chs_oninit_funcptr)();
void (*__chs_onexit_funcptr)();
int (*__chs_get_version_major_funcptr)();
int (*__chs_get_version_minor_funcptr)();
int (*__chs_get_version_patch_funcptr)();
void (*__chs_get_graphics_api_info_funcptr)(CHS_Graphics_API_Info*);

/**
 * @brief Checks if the libchrysalis headers and the loaded implementation do match
 * @remark The patch version number is not taken into account as a patch update to the library should not change it's API
 * @remark This function is implemented in the headers
 * @returns 1 if header and implementation versions do match, 0 if not
 */
int chs_version_check();

/**
 * @brief Get the dynamic library extension per system
 */

const char* chs_private_get_dylib_file_ext()
{
	#ifdef __APPLE__
		return ".dylib";
	#elif defined(_WIN32) || defined(WIN32)
		return ".dll";
	#elif defined(unix) || defined(__unix__) || defined(__unix)
		return ".so"
	#endif
}

const char* chs_private_get_dylib_file_pre()
{
#ifdef __APPLE__
	return "lib";
#elif defined(_WIN32) || defined(WIN32)
	return "";
#elif defined(unix) || defined(__unix__) || defined(__unix)
	return "lib"
#endif
}


/**
 * @brief Inits libchrysalis
 */
void chs_init(const char* implementation_str)
{

	//dirty way of doing things... didn't find a good alternative. thanks to @Lazy_Monique for the help
#if defined(_WIN32) || defined(WIN32)
	char* path = (char*)malloc(80);
	memset(path, 0, 80);
	strcat(path, implementation_str);
	strcat(path, chs_private_get_dylib_file_ext());
#else
	int path_len = wai_getExecutablePath(NULL, 0, NULL);
	int dir_len;
	char* path = (char*)malloc(path_len + 80);
	wai_getExecutablePath(path, path_len, &dir_len);
	path[path_len] = '\0'; //security

	for (int i = path_len; i > 0; --i)
	{
		if (path[i] == '/')
		{
			path[i] = '\0';
			break;
		}
	}

	strcat(path, "/");
	strcat(path, chs_private_get_dylib_file_pre());
	strcat(path, implementation_str);
	strcat(path, chs_private_get_dylib_file_ext());
#endif

	chs_private_load_library(path);

	// CHRYSALIS.H
	__chs_get_version_major_funcptr = (int(*)())chs_private_load_symbol("chs_get_version_major");
	__chs_get_version_minor_funcptr = (int(*)())chs_private_load_symbol("chs_get_version_minor");
	__chs_get_version_patch_funcptr = (int(*)())chs_private_load_symbol("chs_get_version_patch");
	__chs_get_graphics_api_info_funcptr = (void(*)(CHS_Graphics_API_Info*))chs_private_load_symbol("chs_get_graphics_api_info");

	__chs_oninit_funcptr = (void(*)())chs_private_load_symbol("chs_oninit");
	__chs_onexit_funcptr = (void(*)())chs_private_load_symbol("chs_onexit");

	chs_private_load_window_funcptr();
	chs_private_load_renderer_funcptr();

	if (!chs_version_check())
	{
		chs_die("Implementation and header versions do not match");
	}

	(*__chs_oninit_funcptr)();

	free(path);
}


/**
 * @brief Should be called at the end of the program / library use
 */
void chs_quit()
{
	__chs_onexit_funcptr();
	chs_private_close_library();
}

/**
 * @brief Major version of the loaded libchrysalis implementation
 * @returns Major version number of the loaded libchrysalis implementation
 */
int chs_get_version_major()
{ return (*__chs_get_version_major_funcptr)(); }

/**
 * @brief Minor version of the loaded libchrysalis implementation
 * @returns Minor version number of the loaded libchrysalis implementation
 */
int chs_get_version_minor()
{ return (*__chs_get_version_minor_funcptr)(); }

/**
 * @brief Patch version of the loaded libchrysalis implementation
 * @returns Patch version number of the loaded libchrysalis implementation
 */
int chs_get_version_patch()
{ return (*__chs_get_version_patch_funcptr)(); }

/**
 * @brief Information about the graphics api
 * @param[out] info CHS_Graphics_API_Info pointer to write to
 */
void chs_get_graphics_api_info(CHS_Graphics_API_Info* info)
{ return (*__chs_get_graphics_api_info_funcptr)(info); }

int chs_version_check()
{
	return (chs_get_version_major() == __CHRYSALIS_VERSION_MAJOR__) && (chs_get_version_minor() == __CHRYSALIS_VERSION_MINOR__);
}