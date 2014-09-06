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
	physx
	python
	final
	ext)


ADD_DEFINITIONS("-DGLM_FORCE_RADIANS")



INCLUDE(cmh_executable)


