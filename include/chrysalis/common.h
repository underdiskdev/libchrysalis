// libchrysalis is subject to the terms of the GNU Lesser General Public License v3.0
// If a copy of the LGPLv3 was not distributed with this copy of the source code,
// you can obtain one at https://www.gnu.org/licenses/lgpl-3.0.en.html

/**
 * @file
 * @brief Default types
 * @author underdisk
 * @date June 2020 - June 2020
 * @copyright GNU Lesser General Public License v3.0
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>

#ifndef bool
	typedef _Bool bool; // _Bool is the C definition of the boolean type. let's use the bool keyword instead
#endif
typedef uint8_t u8;
typedef int8_t i8;
typedef uint16_t u16;
typedef int16_t i16;
typedef uint32_t u32;
typedef int32_t i32;
typedef uint64_t u64;
typedef int64_t i64;
