CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)

INCLUDE($ENV{HOME}/.config.cmake)

FIND_PACKAGE(CMakeHelper)

PROJECT(box)
INCLUDE(../../config.cmake)
INCLUDE(cmh_build_config)

FIND_PACKAGE(PhysX)
FIND_PACKAGE(galaxy 0 COMPONENTS
	std
	log
	console)
FIND_PACKAGE(nebula 0 COMPONENTS
	core
	gfx
	physx
	python
	final
	ext)


ADD_DEFINITIONS("-DGLM_FORCE_RADIANS")



INCLUDE(cmh_executable)

#SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -v")


add_custom_command(
	TARGET box POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory "${nebula_gfx_INCLUDE_DIR}/neb/gfx/media" ${PROJECT_BINARY_DIR}/media)

add_custom_target(
	box_media
	DEPENDS ${PROJECT_BINARY_DIR}/media)

