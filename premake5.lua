workspace "libchrysalis"
	architecture "x86_64"

	configurations {
		"debug",
		"release"
	}

	platform = "unknown"

	if os.host() == "linux" then
		platform = "linux64"
	elseif os.host() == "macosx" then
		platform = "macOS"
	elseif os.host() == "windows" then
		platform = "win64"
	end

outputdir = ("%{cfg.buildcfg}-" .. platform .. "-%{cfg.architecture}")

project "glew"
	location "buildjunk/makefiles/glew"
	kind "StaticLib"
	language "C"
	targetdir ("buildjunk/lib/" .. outputdir .. "/%{prj.name}")
	objdir ("buildjunk/obj/" .. outputdir .. "/%{prj.name}")

	files {
		"deps/glew/**.h",
		"deps/glew/**.c"
	}

	includedirs {
		"deps/glew/include"
	}

	defines {
		"GLEW_STATIC",
		"GLEW_NO_GLU",
		"GL_SILENCE_DEPRECATION" -- for macOS
	}

project "chrysalis-gl"
	location "buildjunk/makefiles/chrysalis-gl"
	kind "SharedLib"
	language "C"
	targetdir ("build/lib/" .. outputdir .. "/%{prj.name}")
	objdir ("buildjunk/obj/" .. outputdir .. "/%{prj.name}")

	libdirs {
		("buildjunk/lib/" .. outputdir .. "/glew"),
		_OPTIONS["SDL2_lib_path"]
	}

	filter "system:macosx"
		links { "glew", "OpenGL.framework", "SDL2" }
	filter "system:windows" 
		links { "glew", "opengl32", "SDL2" }
	filter "system:linux"
		--todo: Support linux
	filter {}

	files {
		"src/gl/**.h",
		"src/gl/**.c"
	}

	defines {
		"GLEW_STATIC",
		"GLEW_NO_GLU"
	}

	includedirs {
		"include",
		"deps/glew/include",
		_OPTIONS["SDL2_include_path"]
	}

	postbuildcommands {
		--"{COPY} %{cfg.basedir}/include %{cfg.basedir}/build/include",
		--"cd %{cfg.basedir}/docs && doxygen",
		--"{MOVE} %{cfg.basedir}/docs/documentation %{cfg.basedir}/build/documentation/"
	}

	filter "configurations:debug"
		defines "CHRYSALIS_DEBUG"
		symbols "on"
	filter "configurations:release"
		defines "CHRYSALIS_RELEASE"
		symbols "off"

project "sandbox"
	location "buildjunk/makefiles/sandbox"
	kind "ConsoleApp" 
	language "C"
	targetdir ("build/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("buildjunk/obj/" .. outputdir .. "/%{prj.name}")
	filter "system:macosx"
		links { "OpenGL.framework", "SDL2" }
	filter "system:windows" 
		links { "opengl32", "SDL2" }
	filter "system:linux"
		--todo: Support linux
	filter {}
	files {
		"src/sandbox.c",
		"include/chrysalis/**.h"
	}
	libdirs {
		_OPTIONS["SDL2_lib_path"]
	}
	includedirs {
		"include",
		_OPTIONS["SDL2_include_path"]
	}
	filter "configurations:debug"
		defines "CHRYSALIS_DEBUG"
		symbols "on"
	filter "configurations:release"
		defines "CHRYSALIS_RELEASE"
		symbols "off"

newoption {
	trigger     = "SDL2_include_path",
	value       = "path",
	description = "include directory where the SDL2 headers can be found"
}

newoption {
	trigger     = "SDL2_lib_path",
	value       = "path",
	description = "lib directory where the SDL2 library can be found"
}

newaction {
	trigger     = "clean",
	description = "clean build files",
	execute     = function ()
		print("clean the build...")
		os.rmdir("./build")
		os.rmdir("./buildjunk")
		os.remove("./Makefile")
		os.rmdir("./libchrysalis.xcworkspace")
		os.rmdir("./docs/documentation")
		os.remove("./libchrysalis.sln")
		print("done")
	end
}