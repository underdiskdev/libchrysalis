// libchrysalis is subject to the terms of the GNU Lesser General Public License v3.0
// If a copy of the LGPLv3 was not distributed with this copy of the source code,
// you can obtain one at https://www.gnu.org/licenses/lgpl-3.0.en.html

/**
 * @file
 * @brief Cross platform module loading header
 * @author underdisk
 * @date June 2020 - June 2020
 * @copyright GNU Lesser General Public License v3.0
 */

#pragma once

#if defined( __APPLE__) || defined(unix) || defined(__unix__) || defined(__unix) // macOS and other Unix(-like) including linux
	
	#include "load_unix.h"

#elif defined(_WIN32) || defined(WIN32) // Microsoft Windows (32 and 64 bits)
	// todo: Support Microsoft Windows
#else
	#error libchrysalis currently only supports macOS, GNU/Linux or Microsoft Windows
#endif
