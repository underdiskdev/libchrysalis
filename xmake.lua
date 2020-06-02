target("libglew") -- GLEW dependency
    set_version("2.1.0")
    set_kind("static")
    add_includedirs("deps/glew/include")
    add_files("deps/glew/src/*.c")
    add_defines("GLEW_NO_GLU", "GLEW_STATIC")

target("libchrysalis-gl") -- OpenGL implementation (3.3 -> 4.6)
    set_version("1.0.0")
    set_kind("shared")
    add_includedirs("include", "deps/glew/include")
    add_files("src/gl/**.c", "include/**.h")