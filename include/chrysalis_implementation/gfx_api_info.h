// libchrysalis is subject to the terms of the GNU Lesser General Public License v3.0
// If a copy of the LGPLv3 was not distributed with this copy of the source code,
// you can obtain one at https://www.gnu.org/licenses/lgpl-3.0.en.html

/**
 * @file
 * @brief Graphics API info type header
 * @author underdisk
 * @date May 2020 - May 2020
 * @copyright GNU Lesser General Public License v3.0
 */

#pragma once

/**
 * @brief Contains information about a graphics API
 */
typedef struct
CHS_Graphics_API_Info {
	/**
	 * @brief Null-terminated string representing the name of the graphics API.
	 */
	char* name;

	/**
	 * @brief Null-terminated string representing the oldest supported version of the graphics API
	 */
	char* oldest_version;

	/**
	 * @brief Null-terminated string representing the latest supported version of the graphics API
	 */
	char* latest_version;
}	CHS_Graphics_API_Info;