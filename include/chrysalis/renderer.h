// libchrysalis is subject to the terms of the GNU Lesser General Public License v3.0
// If a copy of the LGPLv3 was not distributed with this copy of the source code,
// you can obtain one at https://www.gnu.org/licenses/lgpl-3.0.en.html

/**
 * @file
 * @brief Renderer and context definitions
 * @author underdisk
 * @date May 2020 - June 2020
 * @copyright GNU Lesser General Public License v3.0
 */

#pragma once

#include "window.h"
#include "color.h"

#include "load.h"
#include "common.h"

/**
 * @brief Represents a renderer
 */
typedef struct
CHS_Renderer {
	/**
	 * @brief Window the renderer is attached to 
	 */
	CHS_Window* window;

	/**
	 * @brief Additional data for the implementation
	 * @details Information that are not common to every implementation goes here.
	 * 			It can hold anything (raw pointer). If you are writing an implementation,
	 * 			this is where you want to put your OpenGL context, Direct3D / Vulkan Swap Chain
	 * 			etc
	 */
	void* data;
}	CHS_Renderer;

/**
 * @brief Represents a renderer
 */
typedef struct
CHS_Renderer_Config {
	/**
	 * @brief Use fallbacks
	 * @details A fallback is a change of version for the graphics API if the last version if not available.
	 * 			For example with the OpenGL implementation: if OpenGL 4.6 is not available, it will fallback
	 * 			on OpenGL 4.5, then 4.4... until a working version is found.
	 * 			If this parameter is set to 0 and if the last API version fails to load, the application will
	 * 			crash with an error
	 */
	int use_fallbacks;

	/**
	 * @brief Number of bits used for the depth buffer (usually 24)
	 */
	int depth_bits;

	/**
	 * @brief Number of bits used for the stencil buffer (usually 8)
	 */
	int stencil_bits;
}	CHS_Renderer_Config;

CHS_Renderer* (*__chs_create_renderer_funcptr)(CHS_Renderer_Config*, CHS_Window*);
void (*__chs_delete_renderer_funcptr)(CHS_Renderer*);
void (*__chs_renderer_display_funcptr)(CHS_Renderer*);
void (*__chs_renderer_set_clear_color_funcptr)(CHS_Renderer*, CHS_Color);
void (*__chs_renderer_clear_funcptr)(CHS_Renderer*);

void chs_private_load_renderer_funcptr()
{
	__chs_create_renderer_funcptr = chs_private_load_symbol("chs_create_renderer");
	__chs_delete_renderer_funcptr = chs_private_load_symbol("chs_delete_renderer");
	__chs_renderer_display_funcptr = chs_private_load_symbol("chs_renderer_display");
	__chs_renderer_set_clear_color_funcptr = chs_private_load_symbol("chs_renderer_set_clear_color");
	__chs_renderer_clear_funcptr = chs_private_load_symbol("chs_renderer_clear");
}


/**
 * @brief Creates a renderer
 * @param[in] config Configuration of the renderer
 * @param[in] window Window for the renderer to attach to
 * @returns Pointer on a CHS_Renderer object
 * @details This field creates the renderer. It is also responsible of selecting/binding the
 * 			main framebuffer / backbuffer
 */
CHS_Renderer* chs_create_renderer(CHS_Renderer_Config* config, CHS_Window* window)
{ return (*__chs_create_renderer_funcptr)(config, window); }

/**
 * @brief Deletes a renderer
 * @param[in] renderer Pointer to the CHS_Renderer to destroy
 */
void chs_delete_renderer(CHS_Renderer* renderer)
{ return (*__chs_delete_renderer_funcptr)(renderer); }

/**
 * @brief Display image (swap buffers)
 * @param[in] renderer Pointer to the CHS_Renderer to display
 */
void chs_renderer_display(CHS_Renderer* renderer)
{ return (*__chs_renderer_display_funcptr)(renderer); }

/**
 * @brief Changes the color that gets drawn when calling chs_renderer_clear()
 * @param[in] renderer Pointer to the CHS_Renderer to change the clear color of
 * @param[in] color Color to display when clearing
 */
void chs_renderer_set_clear_color(CHS_Renderer* renderer, CHS_Color color)
{ return (*__chs_renderer_set_clear_color_funcptr)(renderer, color); }

/**
 * @brief Clears the screen with the color set using chs_renderer_set_clear_color()
 * @param[in] renderer Pointer to the CHS_Renderer to clear
 */
void chs_renderer_clear(CHS_Renderer* renderer)
{ return (*__chs_renderer_clear_funcptr)(renderer); }

