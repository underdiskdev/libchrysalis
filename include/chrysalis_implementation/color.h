// libchrysalis is subject to the terms of the GNU Lesser General Public License v3.0
// If a copy of the LGPLv3 was not distributed with this copy of the source code,
// you can obtain one at https://www.gnu.org/licenses/lgpl-3.0.en.html

/**
 * @file
 * @brief Color header
 * @author underdisk
 * @date May 2020 - May 2020
 * @copyright GNU Lesser General Public License v3.0
 */

#pragma once

/**
 * @brief Data type representing a color
 */
typedef struct
CHS_Color {
	/**
	 * @brief Red
	 */
	float r;

	/**
	 * @brief Green
	 */
	float g;

	/**
	 * @brief Blue
	 */
	float b;

	/**
	 * @brief Alpha
	 */
	float a;
}	CHS_Color;
