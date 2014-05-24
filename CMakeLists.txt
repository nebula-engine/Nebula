cmake_minimum_required (VERSION 2.8.9)

project(Nebula)

find_package(glfw)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -D_DEBUG -std=c++0x")

include_directories("/usr/include/freetype2")

# custom include extensions
set(INCLUDE_EXTENSIONS obj)

SET(GRU_VERSION 0.1.1)


# common methods for static library
# =================================
include($ENV{HOME}/usr/lib/cmake/CMakeHelper/static/library.cmake)


add_subdirectory(test)


