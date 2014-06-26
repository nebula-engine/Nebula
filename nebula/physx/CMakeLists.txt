CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)

INCLUDE($ENV{HOME}/.config.cmake)

PROJECT(Nebula-PhysX)

FIND_PACKAGE(glfw)
FIND_PACKAGE(CMakeHelper)
FIND_PACKAGE(PhysX)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -D_DEBUG -std=c++0x")

include_directories("/usr/include/freetype2")
INCLUDE_DIRECTORIES("../Debug/include")
include_directories("../Galaxy-Standard/include")
include_directories("../Galaxy-Network/include")
include_directories("../Galaxy-Log/include")
include_directories("../include")
include_directories("../Nebula-Core/include")
include_directories("../Nebula-Core/Debug/include")
include_directories("../glm")
include_directories("../maze/include")
include_directories(${physx_INCLUDE_DIR})

link_directories("../Galaxy-Network/Debug")
link_directories("../Galaxy-Standard/Debug")
link_directories("../Galaxy-Log/Debug")
link_directories("../Nebula-Core/Debug")
link_directories("../Debug")
link_directories("../maze/Debug")

ADD_DEFINITIONS("-D_DEBUG -DGAL_NET_USE_BOOST -DGLM_FORCE_RADIANS")

# custom include extensions
set(include_extensions obj)

SET(GRU_VERSION 0.1.1)


FIND_PACKAGE(Boost 1.55 COMPONENTS program_options serialization log system thread)

SET(libs ${libs}
	${PROJECT_NAME}
	Nebula
	maze
	Galaxy-Standard
	Galaxy-Network
	Galaxy-Log
	${PhysX_LIBRARIES}
	${PhysX_LIBRARIES}
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
	Xxf86vm
	${PhysX_LIBRARIES}
	${PhysX_LIBRARIES}
	)



# common methods for static library
# =================================



cmh_static_library()

add_subdirectory(test)


