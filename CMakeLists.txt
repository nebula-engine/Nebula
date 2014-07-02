cmake_minimum_required (VERSION 2.6)

project(nebula)

find_package(gru)

add_definitions(-DNDEBUG -DPHYSX)

set(CMAKE_CXX_FLAGS "-std=c++0x")

# need to refine versioning in cmake
SET(NEBULA_VERSION 0.1.1)

include_directories(${gru_INCLUDE_DIR})

# common methods for static library
# =================================
include($ENV{HOME}/usr/lib/cmake/CMakeHelper/static/library.cmake)


