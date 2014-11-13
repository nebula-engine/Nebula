CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)

INCLUDE($ENV{HOME}/.config.cmake)

FIND_PACKAGE(CMakeHelper)

PROJECT(nebula_physx)
INCLUDE(../../config.cmake)
INCLUDE(cmh_build_config)

FIND_PACKAGE(glfw)
FIND_PACKAGE(PhysX)

FIND_PACKAGE(galaxy 0 COMPONENTS
	std
	log
	console
	REQUIRED)

FIND_PACKAGE(nebula 0 COMPONENTS
<<<<<<< HEAD
	gfx
	core
	REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -D_DEBUG -std=c++0x")
=======
	core
	REQUIRED)

>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507

include_directories("/usr/include/freetype2")
include_directories("../../glm")
include_directories(${physx_INCLUDE_DIR})

link_directories("../Debug")

<<<<<<< HEAD
ADD_DEFINITIONS("-D_DEBUG -DGAL_NET_USE_BOOST -DGLM_FORCE_RADIANS")
=======
ADD_DEFINITIONS("-DGLM_FORCE_RADIANS")
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507

# custom include extensions
set(include_extensions obj)

SET(GRU_VERSION 0.1.1)

INCLUDE(cmh_boost)
<<<<<<< HEAD
FIND_PACKAGE(Boost 1.55 COMPONENTS program_options serialization log system thread)

SET(libs
	${galaxy_LIBRARIES}
	${nebula_LIBRARIES}
=======
#FIND_PACKAGE(Boost 1.55 COMPONENTS program_options serialization log system thread)

SET(libs
	#${galaxy_LIBRARIES}
	#${nebula_LIBRARIES}
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
	${Boost_LIBRARIES}
	${PhysX_LIBRARIES}
	)

INCLUDE(cmh_library)

add_subdirectory(test)


