CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)

INCLUDE($ENV{HOME}/.config.cmake)

FIND_PACKAGE(CMakeHelper)

PROJECT(nebula_final)
INCLUDE(../../config.cmake)
INCLUDE(cmh_build_config)

FIND_PACKAGE(glfw)
FIND_PACKAGE(PhysX)
#FIND_PACKAGE(maze)

FIND_PACKAGE(galaxy 0 COMPONENTS
	std
	log
	console
	REQUIRED)

FIND_PACKAGE(nebula 0 COMPONENTS
	core
	gfx
	physx
	python
	REQUIRED)

include_directories("/usr/include/freetype2")
include_directories(${physx_INCLUDE_DIR})

ADD_DEFINITIONS("-DGLM_FORCE_RADIANS")

set(include_extensions obj)

INCLUDE(cmh_boost)
FIND_PACKAGE(Boost 1.55 COMPONENTS program_options serialization log system thread)

SET(libs
	${nebula_LIBRARIES}
	${galaxy_LIBRARIES}
	${PhysX_LIBRARIES}
	${Boost_LIBRARIES}
	${glfw_LIBRARIES}
	)

INCLUDE(cmh_library)

add_subdirectory(test)


