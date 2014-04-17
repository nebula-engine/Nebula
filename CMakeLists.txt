cmake_minimum_required (VERSION 2.6)
#include(ExternalProject)

project(nebula)

set(PROJECT_SOURCE_DIR src)

set(LIB_NAME nebula)
set(PROJECT_NAME NEBULA)
set(PROJECT_name nebula)

set(INSTALL_LIB_DIR ${CMAKE_INSTALL_PREFIX})
set(INSTALL_BIN_DIR ${CMAKE_INSTALL_PREFIX})
set(INSTALL_INCLUDE_DIR ${CMAKE_INSTALL_PREFIX}/include/math)
set(INSTALL_CMAKE_DIR ${CMAKE_INSTALL_PREFIX}/lib/${LIB_NAME})


include_directories("${PROJECT_SOURCE_DIR}" ../glutpp/src ../galaxy/src ../math/src)


# common methods for static library
# =================================
include(../static_library.cmake)


# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
	add_custom_target(doc
		${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMENT "Generating API documentation with Doxygen" VERBATIM
	)
endif(DOXYGEN_FOUND)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -D_DEBUG -std=c++0x -Wall -Wno-unknown-pragmas -Wno-unused-local-typedefs -rdynamic -pthread")
set(CMAKE_INSTALL_PREFIX $ENV{HOME}/usr)


add_dependencies(nebula glutpp)

#ExternalProject_Add(
#        glutpp
#        PREFIX "$ENV{HOME}/Programming/C++/glutpp"
#        SOURCE_DIR "$ENV{HOME}/Programming/C++/glutpp"
#        BUILD_IN_SOURCE 1
#	BUILD_COMMAND make install
#)


