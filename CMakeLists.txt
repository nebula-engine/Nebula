cmake_minimum_required (VERSION 2.8)

project(gru)

find_package(math)
find_package(glfw)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -D_DEBUG -std=c++0x")

include_directories("/usr/include/freetype2")

# custom include extensions
set(INCLUDE_EXTENSIONS obj)

# common methods for static library
# =================================
include(../cmake/static_library.cmake)




