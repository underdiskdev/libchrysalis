cmake_minimum_required(VERSION 3.15)
project(libchrysalis C)

option(BUILD_DOC "Build documentation" ON)
option(BUILD_STANDALONE "Build test executable" ON)

set(CMAKE_BUILD_TYPE Debug)

find_package(SDL2 REQUIRED)

if(BUILD_DOC)
    find_package(Doxygen)
    if (DOXYGEN_FOUND)
        set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile)
        set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/documentation/Doxyfile)

        #File configuration
        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
        message("Doxygen build started")

        add_custom_target(doc ALL
                COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                COMMENT "Generating Doxygen documentation"
                VERBATIM)
    else (DOXYGEN_FOUND)
        message("Doxygen needs to be installed in order to generate the documentation")
    endif (DOXYGEN_FOUND)
endif()

set (	HEADERS
		"include/chrysalis/chrysalis.h" )
	
set (	CHRYSALIS_GL_SRCS
		"src/gl/chrysalis-gl.c" )

set (	STANDALONE_GL_SRCS
        "src/standalone.c" )
        
# Build GLEW
add_library(glew "deps/glew/include/GL/glew.h" "deps/glew/src/glew.c")
target_include_directories(glew PRIVATE "deps/glew/include")

add_library(chrysalis-gl SHARED ${HEADERS} ${CHRYSALIS_GL_SRCS})
target_include_directories(chrysalis-gl PRIVATE "include/chrysalis" "deps/glad/include" ${SDL2_INCLUDE_DIRS})
target_link_libraries(chrysalis-gl SDL2::SDL2 "-framework OpenGL" glew)

if (BUILD_STANDALONE)
	add_executable(chrysalis_standalone ${HEADERS} ${STANDALONE_GL_SRCS})
	target_link_libraries(chrysalis_standalone chrysalis-gl SDL2::SDL2 "-framework OpenGL")
	target_include_directories(chrysalis_standalone PRIVATE include ${SDL2_INCLUDE_DIRS})
endif (BUILD_STANDALONE)