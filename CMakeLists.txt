cmake_minimum_required(VERSION 2.6)
project(MarioLike)
include_directories(${sdl_include_dir} include)
link_directories(${sdl_lib_dir})
link_directories(${expat_lib_dir})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${bin_output_dir})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(CMAKE_BUILD_TYPE "Debug")

set(sdl_name "SDL2" CACHE STRING "Name of the lib")
set(sdl_image_name "SDL2_image" CACHE STRING "Name of sdl image lib")
set(sdl_ttf_name "SDL2_ttf" CACHE STRING "Name of sdl ttf lib")
set(sdl_mixer_name "SDL2_mixer" CACHE STRING "Name of sdl mixer lib")
set(expat_name "expat" CACHE STRING "Name of expat lib")

IF(WIN32)
	set(sdl_lib_dir "${CMAKE_SOURCE_DIR}/lib/bin/" CACHE PATH "Path to libs")
	set(sdl_include_dir "${CMAKE_SOURCE_DIR}/lib/include/" CACHE PATH "Path to the include directory of the lib")
	set(expat_lib_dir "${CMAKE_SOURCE_DIR}/lib/bin/" CACHE PATH "Path to expat lib")
ELSE()
	set(sdl_lib_dir "/usr/lib/" CACHE PATH "Path to libs")
	set(sdl_include_dir "/usr/include" CACHE PATH "Path to the include directory of the lib")
	set(expat_lib_dir "/usr/lib" CACHE PATH "Path to expat lib")
ENDIF()

set(bin_output_dir "bin/" CACHE PATH "Path to where the program will be build")

file(
	COPY Resources
	DESTINATION bin/
)

IF(WIN32)
	file(
		GLOB_RECURSE
		bin_file
		lib/bin/*.dll
	)

	file(
		COPY ${bin_file}
		DESTINATION bin/
	)
ENDIF()

file(
	GLOB_RECURSE
	source_file
	src/*
)

add_executable(
	MarioLike
	${source_file}
)

target_link_libraries(
	MarioLike
	${sdl_name}
	${sdl_image_name}
	${sdl_ttf_name}
	${sdl_mixer_name}
	${expat_name}
	m
)	
