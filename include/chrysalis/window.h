// libchrysalis is subject to the terms of the GNU Lesser General Public License v3.0
// If a copy of the LGPLv3 was not distributed with this copy of the source code,
// you can obtain one at https://www.gnu.org/licenses/lgpl-3.0.en.html

/**
 * @file
 * @brief Window header
 * @author underdisk
 * @date May 2020 - May 2020
 * @copyright GNU Lesser General Public License v3.0
 */

#pragma once

#include <SDL2/SDL.h>
#include <stdio.h>

/**
 * @brief Represents an OS window
 */
typedef struct
CHS_Window {
	/**
	 * @brief SDL Window object
	 */
	SDL_Window* window;
}	CHS_Window;

/**
 * @brief Configuration of a CHS_Window
 */
typedef struct
CHS_Window_Config {
	/**
	 * @brief Title of the window
	 */
	char* title;

	/**
	 * @brief Is the window resizable ?
	 */
	int resizable;

	/**
	 * @brief Does the window have a border ?
	 */
	int borderless;

	/**
	 * @brief Width of the window
	 */
	unsigned int width;

	/**
	 * @brief Height of the window
	 */
	unsigned int height;

	/**
	 * @brief Support for High DPI screens (Retina..)
	 */
	int high_dpi_support;
}	CHS_Window_Config;

/**
 * @brief Returns additional SDL window flag used for context creation
 */
Uint32 chs_get_additional_sdl_window_flags();

/**
 * @brief Called just before creating a SDL Window
 */
void chs_before_window_creation(CHS_Window_Config* config);

/**
 * @brief Creates and initializes a CHS_Window
 * @remark This function is implemented in the headers, but uses functions not implemented in the headers
 * @returns A valid CHS_Window pointer in case of success, NULL in case of failure
 */
CHS_Window* chs_create_window(CHS_Window_Config* config)
{
	chs_before_window_creation(config);
	CHS_Window* ret = (CHS_Window*)malloc(sizeof(CHS_Window));
	ret->window = SDL_CreateWindow(	config->title,
									SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
									config->width, config->height,
										(SDL_WINDOW_RESIZABLE * config->resizable)
									|	(SDL_WINDOW_ALLOW_HIGHDPI * config->high_dpi_support)
									|	(SDL_WINDOW_BORDERLESS * config->borderless)
									|	(SDL_WINDOW_SHOWN)
									|	chs_get_additional_sdl_window_flags()	);

	if(ret->window == NULL)
	{
		fprintf(stderr, "Could not create SDL Window: %s\n", SDL_GetError());
	}

	return ret;
}

/**
 * @brief Deletes a CHS_Window
 * @remark This function is implemented in the headers
 */
void chs_delete_window(CHS_Window* window)
{
	free(window);
}

/**
 * @brief Returns a unique number for each window
 * @remark This function is implemented in the headers
 */
Uint32 chs_window_get_id(CHS_Window* window)
{
	return SDL_GetWindowID(window->window);
}
