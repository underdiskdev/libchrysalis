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

#pragma once

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Crashes the program with a message
 */
void chs_die(const char* reason)
{
	fprintf(stderr, "Error: %s", reason);
	exit(-1);
}