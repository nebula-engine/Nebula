cmake_minimum_required (VERSION 2.6)

project(gru)

find_package(math)
find_package(glfw)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -D_DEBUG -std=c++0x")

# custom variables for config header
set(object_dir ${CMAKE_INSTALL_PREFIX}/include/glutpp/objects)
set(shader_dir ${CMAKE_INSTALL_PREFIX}/include/glutpp/glsl/shaders)

# custom include extensions
set(INCLUDE_EXTENSIONS obj)

# common methods for static library
# =================================
include(../cmake/static_library.cmake)




