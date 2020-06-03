// libchrysalis is subject to the terms of the GNU Lesser General Public License v3.0
// If a copy of the LGPLv3 was not distributed with this copy of the source code,
// you can obtain one at https://www.gnu.org/licenses/lgpl-3.0.en.html

/**
 * @file
 * @brief OpenGL universal include header
 * @author underdisk
 * @date June 2020 - June 2020
 * @copyright GNU Lesser General Public License v3.0
 */

#include <GL/glew.h>

#ifdef __APPLE__
    #include <OpenGL/gl.h>
#elif defined(unix) || defined(__unix__) || defined(__unix)
    #include <gl/GL.h>
#elif defined(_WIN32) || defined(WIN32)
    #include <gl/GL.h>
#endif

