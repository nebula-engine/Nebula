cmake_minimum_required (VERSION 2.8.8)

INCLUDE($ENV{HOME}/.config.cmake)

project(Nebula)

find_package(glfw)
FIND_PACKAGE(physx)



set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -D_DEBUG -std=c++0x")

include_directories("/usr/include/freetype2")
include_directories("./Galaxy-Standard/include")
include_directories("./Galaxy-Network/include")
include_directories(${physx_INCLUDE_DIR})

ADD_DEFINITIONS("-D_DEBUG -DGAL_NET_USE_BOOST")

# custom include extensions
set(INCLUDE_EXTENSIONS obj)

SET(GRU_VERSION 0.1.1)


# common methods for static library
# =================================


find_package(CMakeHelper)
include(${CMakeHelper_INCLUDE_DIR}/CMakeHelper/static/library.cmake)

cmh_static_library()

add_subdirectory(test)


