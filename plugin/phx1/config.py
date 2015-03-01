"""
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)

INCLUDE($ENV{HOME}/.config.cmake)

FIND_PACKAGE(CMakeHelper)

PROJECT(nebula_gfx)
INCLUDE(../../config.cmake)
INCLUDE(cmh_build_config)

SET(SHARED True)

FIND_PACKAGE(glfw)
FIND_PACKAGE(PhysX)
FIND_PACKAGE(galaxy 0 COMPONENTS
	std
	log
	console	
	REQUIRED)

FIND_PACKAGE(nebula 0 COMPONENTS
	core
	REQUIRED)


include_directories("/usr/include/freetype2")
include_directories("../../glm")
include_directories(${physx_INCLUDE_DIR})

link_directories("../Debug")

ADD_DEFINITIONS("-DGLM_FORCE_RADIANS")

# custom include extensions
set(include_extensions obj)

SET(GRU_VERSION 0.1.1)

INCLUDE(cmh_boost)
#FIND_PACKAGE(Boost 1.55 COMPONENTS program_options serialization log system thread)

SET(libs
	#${galaxy_LIBRARIES}
	#${nebula_LIBRARIES}
	#nebula_core_0
	#galaxy_std_0
	#galaxy_log_0
	#galaxy_console_0
	${Boost_LIBRARIES}
	${PhysX_LIBRARIES}
	png
	)

INCLUDE(cmh_library)

#add_subdirectory(test)
"""

l = Dynamic("nebula_plugin_phx1")

l.require("galaxy_std", whole=True)
l.require("galaxy_log", whole=True)
l.require("galaxy_console", whole=True)
l.require("nebula_core", whole=True)
l.require("nebula_physx", whole=True)
l.require("physx")

l.make()



