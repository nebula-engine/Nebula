cmake_minimum_required (VERSION 2.8)

project(gru)

find_package(math)
find_package(galaxy)
find_package(glfw)
find_package(TinyXML2)

if(${TinyXML2_FOUND})
else()
	set(TinyXML2_FOUND 0)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -D_DEBUG -std=c++0x")

include_directories("/usr/include/freetype2")

# custom include extensions
set(INCLUDE_EXTENSIONS obj)

# common methods for static library
# =================================
include($ENV{HOME}/usr/lib/cmake/CMakeHelper/static/library.cmake)

add_subdirectory(test)


