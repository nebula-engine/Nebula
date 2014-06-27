CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)

INCLUDE($ENV{HOME}/.config.cmake)

PROJECT(nebula_core)

SET(nebula_core_SHARED TRUE)
SET(nebula_core_STATIC TRUE)

FIND_PACKAGE(glfw)

FIND_PACKAGE(Galaxy COMPONENTS
	std
	log
	REQUIRED)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -D_DEBUG -std=c++0x")

include_directories("/usr/include/freetype2")
include_directories("../maze/include")
include_directories("../Control-System/include")
include_directories("../glm")
#include_directories(${physx_INCLUDE_DIR})

link_directories("../maze/Debug")
link_directories("../Control-System/Debug")

ADD_DEFINITIONS("-D_DEBUG -DGAL_NET_USE_BOOST -DGLM_FORCE_RADIANS")

# custom include extensions
set(include_extensions obj)

SET(GRU_VERSION 0.1.1)

FIND_PACKAGE(CMakeHelper)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_STATIC_RUNTIME OFF)
add_definitions( -DBOOST_ALL_DYN_LINK )

FIND_PACKAGE(Boost 1.55 COMPONENTS
	serialization
	log
	system
	thread
	REQUIRED)

SET(libs ${libs}
	${PROJECT_NAME}
	maze
	galaxy_std_shared
	Galaxy-Network
	galaxy_log_shared
	${Boost_LIBRARIES}
	glfw3
	GL
	GLU
	GLEW
	freetype
	png
	rt
	pthread
	X11
	Xrandr
	Xi
	Xcursor
	)



# common methods for static library
# =================================

cmh_library()

#add_subdirectory(test)


