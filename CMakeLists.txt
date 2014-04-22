cmake_minimum_required (VERSION 2.6)

project(nebula)

find_package(gru)

add_definitions(-DNDEBUG -DPHYSX)

set(CMAKE_CXX_FLAGS "-std=c++0x")

# common methods for static library
# =================================
include($ENV{HOME}/usr/lib/cmake/CMakeHelperstatic_library.cmake)


