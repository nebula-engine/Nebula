CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)

INCLUDE($ENV{HOME}/.config.cmake)

FIND_PACKAGE(CMakeHelper)

PROJECT(galaxy_std)
INCLUDE(../../../../config.cmake)
INCLUDE(cmh_build_config)


INCLUDE(cmh_boost)
FIND_PACKAGE(Boost 1.55 COMPONENTS
	REQUIRED)

#INCLUDE_DIRECTORIES("/usr/include/python2.7")

SET(libs
	${Boost_LIBRARIES}
	pthread
	)

INCLUDE(cmh_library)

ADD_SUBDIRECTORY(test)

