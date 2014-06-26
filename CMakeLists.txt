CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)

INCLUDE($ENV{HOME}/.config.cmake)

PROJECT(nebula_gfx_shared)

fIND_PACKAGE(glfw)


	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -D_DEBUG -std=c++0x")

	include_directories("/usr/include/freetype2")
	include_directories("./Galaxy-Standard/include")
	include_directories("./Galaxy-Network/include")
	include_directories("./Galaxy-Log/include")
	include_directories("./galaxy/console/include")
	include_directories("./Nebula-Core/include")
	include_directories("./Nebula-Core/Debug/include")
	include_directories("./maze/include")
	include_directories("./Control-System/include")
	include_directories("./glm")
#include_directories(${physx_INCLUDE_DIR})

	link_directories("./Galaxy-Network/Debug")
	link_directories("./Galaxy-Standard/Debug")
	link_directories("./Galaxy-Log/Debug")
	link_directories("./galaxy/console/Debug")
	link_directories("./Nebula-Core/Debug")
	link_directories("./maze/Debug")
	link_directories("./Control-System/Debug")

	ADD_DEFINITIONS("-D_DEBUG -DGAL_NET_USE_BOOST -DGLM_FORCE_RADIANS")

# custom include extensions
set(include_extensions obj)

SET(GRU_VERSION 0.1.1)

FIND_PACKAGE(CMakeHelper)

	set(Boost_USE_STATIC_LIBS OFF)
	set(Boost_USE_STATIC_RUNTIME OFF)
add_definitions(-DBOOST_ALL_DYN_LINK)

	FIND_PACKAGE(Boost 1.55 COMPONENTS
			program_options
			serialization
			log
			system
			thread
			REQUIRED)


	SET(libs ${libs}
			${PROJECT_NAME}
			nebula_core_shared
			maze
			galaxy_std_shared
			galaxy_log_shared
			galaxy_console_shared
			${Boost_LIBRARIES}
			glfw
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

cmh_shared_library()

add_subdirectory(test)


