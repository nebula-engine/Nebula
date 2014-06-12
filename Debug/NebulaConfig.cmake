# - Config file for the FooBar package
# It defines the following variables
#  FOOBAR_INCLUDE_DIRS - include directories for FooBar
#  FOOBAR_LIBRARIES    - libraries to link against
#  FOOBAR_EXECUTABLE   - the bar executable

# Compute paths
#get_filename_component(_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
#get_filename_component(_CMAKE_DIR "" PATH)

# location of this file...
set(Nebula_CMAKE_DIR "/home/chuck/usr/lib/cmake")

set(Nebula_INCLUDE_DIR "/home/chuck/Programming/gru/include")
set(Nebula_INCLUDE_DIRS "/home/chuck/Programming/gru/include;/home/chuck/Programming/gru/Debug/include")

# Our library dependencies (contains definitions for IMPORTED targets)
if(NOT TARGET Nebula AND NOT Nebula_BINARY_DIR)
	message("${Nebula_CMAKE_DIR}")
	include("${Nebula_CMAKE_DIR}/Nebula/NebulaTargets.cmake")
endif()

# These are IMPORTED targets created by FooBarTargets.cmake
set(Nebula_LIBRARIES Nebula Nebula;Galaxy-Standard;Galaxy-Network;Galaxy-Log;/home/chuck/usr/lib/libboost_program_options.a;/home/chuck/usr/lib/libboost_serialization.a;/home/chuck/usr/lib/libboost_log.a;/home/chuck/usr/lib/libboost_system.a;/home/chuck/usr/lib/libboost_thread.a;pthread;glfw3;GL;GLU;GLEW;freetype;png;rt;pthread;X11;Xrandr;Xi;Xcursor)

set(Nebula_DOX_TAGFILE /home/chuck/Programming/gru/doc/Nebula/doxygen/Nebula.tag)

# dox
set(Nebula_DOX_TAGFILE /home/chuck/Programming/gru/doc/Nebula/doxygen/Nebula.tag)
set(DOX_TAGFILES ${DOX_TAGFILES} ${Nebula_DOX_TAGFILE})


# add include dirs to current project
include_directories(${Nebula_INCLUDE_DIRS})

# add libs to current project
SET(libs ${libs} ${Nebula_LIBRARIES})


