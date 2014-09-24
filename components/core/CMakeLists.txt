CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)

INCLUDE($ENV{HOME}/.config.cmake)

FIND_PACKAGE(CMakeHelper)

PROJECT(nebula_core)
INCLUDE(../../config.cmake)
INCLUDE(cmh_build_config)

FIND_PACKAGE(glfw)

FIND_PACKAGE(galaxy 0 COMPONENTS
	log
	console
	REQUIRED)

INCLUDE(cmh_boost)
FIND_PACKAGE(Boost 1.55 COMPONENTS
	serialization
	REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -D_DEBUG -std=c++0x")

#include_directories("/usr/include/freetype2")
include_directories("../glm")
#include_directories(${physx_INCLUDE_DIR})

ADD_DEFINITIONS("-DGLM_FORCE_RADIANS")

SET(libs
	#galaxy_log_0_so_db
	#galaxy_console_0_so_db
	#/scratch/usr/lib/libboost_serialization.so.1.55.0
	)

INCLUDE(cmh_library)




