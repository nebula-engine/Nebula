CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)

INCLUDE($ENV{HOME}/.config.cmake)

FIND_PACKAGE(PkgConfig REQUIRED)
FIND_PACKAGE(CMakeHelper)

PROJECT(nebula_ext_hf)
INCLUDE(../../../config.cmake)
INCLUDE(cmh_build_config)

#INCLUDE(${PROJECT_SOURCE_DIR}/../../external/glfw.cmake)

#pkg_search_module(GLFW REQUIRED glfw3)

FIND_PACKAGE(glfw REQUIRED)
FIND_PACKAGE(PhysX)
FIND_PACKAGE(maze_0_so_db REQUIRED)

FIND_PACKAGE(galaxy 0 COMPONENTS std log console REQUIRED)

FIND_PACKAGE(nebula 0 COMPONENTS
	core
	physx
	python
	final
	REQUIRED)

INCLUDE(../../../external/glfw.cmake)

#FIND_PACKAGE(Boost 1.55 COMPONENTS python REQUIRED)

#INCLUDE_DIRECTORIES("/usr/include/python2.7")
#include_directories("/usr/include/freetype2")
#include_directories("./glm")
#include_directories(${physx_INCLUDE_DIR})

ADD_DEFINITIONS("-DGLM_FORCE_RADIANS")

SET(libs
	#${nebula_LIBRARIES}
	#${galaxy_LIBRARIES}
	${glfw_LIBRARIES}
	)


INCLUDE(cmh_library)




