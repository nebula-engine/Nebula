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
<<<<<<< HEAD
	console
=======
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
	REQUIRED)

FIND_PACKAGE(nebula 0 COMPONENTS
	core
<<<<<<< HEAD
	gfx
=======
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
	physx
	python
	REQUIRED)

include_directories("/usr/include/freetype2")
include_directories(${physx_INCLUDE_DIR})

ADD_DEFINITIONS("-DGLM_FORCE_RADIANS")

set(include_extensions obj)

INCLUDE(cmh_boost)
<<<<<<< HEAD
FIND_PACKAGE(Boost 1.55 COMPONENTS program_options serialization log system thread)

SET(libs
	${nebula_LIBRARIES}
	${galaxy_LIBRARIES}
	${PhysX_LIBRARIES}
	${Boost_LIBRARIES}
	${glfw_LIBRARIES}
	)

=======

SET(libs
	nebula_physx_0_so_db
	#${nebula_LIBRARIES}
	#${galaxy_LIBRARIES}
	${PhysX_LIBRARIES}
	#${Boost_LIBRARIES}
	${glfw_LIBRARIES}
	)

SET(exports
	nebula_core_0_so_db
	galaxy_std_0_so_db
	galaxy_log_0_so_db
	galaxy_console_0_so_db
)

>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
INCLUDE(cmh_library)

add_subdirectory(test)


