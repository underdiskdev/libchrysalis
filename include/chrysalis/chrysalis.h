// libchrysalis is subject to the terms of the GNU Lesser General Public License v3.0
// If a copy of the LGPLv3 was not distributed with this copy of the source code,
// you can obtain one at https://www.gnu.org/licenses/lgpl-3.0.en.html

/**
 * @file
 * @brief Main header file
 * @author underdisk
 * @date May 2020 - May 2020
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

#include "gfx_api_info.h"
#include "renderer.h"
#include "util.h"

#define __CHRYSALIS_VERSION_MAJOR__ 1
#define __CHRYSALIS_VERSION_MINOR__ 0
#define __CHRYSALIS_VERSION_PATCH__ 0 // PATCH updates are not allowed to touch the API and therefore are not referenced in the headers

/**
 * @brief Inits libchrysalis
 */
void chs_init();

/**
 * @brief Should be called at the end of the program / library use
 */
void chs_quit();

/**
 * @brief Major version of the loaded libchrysalis implementation
 * @returns Major version number of the loaded libchrysalis implementation
 */
int chs_get_version_major();

/**
 * @brief Minor version of the loaded libchrysalis implementation
 * @returns Minor version number of the loaded libchrysalis implementation
 */
int chs_get_version_minor();

/**
 * @brief Patch version of the loaded libchrysalis implementation
 * @returns Patch version number of the loaded libchrysalis implementation
 */
int chs_get_version_patch();

/**
 * @brief Information about the graphics api
 * @param[out] info CHS_Graphics_API_Info pointer to write to
 */
void chs_get_graphics_api_info(CHS_Graphics_API_Info* info);

/**
 * @brief Checks if the libchrysalis headers and the loaded implementation do match
 * @remark The patch version number is not taken into account as a patch update to the library should not change it's API
 * @remark This function is implemented in the headers
 * @returns 1 if header and implementation versions do match, 0 if not
 */
int chs_version_check()
{
	return (chs_get_version_major() == __CHRYSALIS_VERSION_MAJOR__) && (chs_get_version_minor() == __CHRYSALIS_VERSION_MINOR__);
}
