cmake_minimum_required (VERSION 2.8.8)

INCLUDE($ENV{HOME}/.config.cmake)

find_package(CMakeHelper)

project(galaxy_log)
INCLUDE(../../../../config.cmake)
INCLUDE(cmh_build_config)

INCLUDE(cmh_boost)
FIND_PACKAGE(Boost 1.55 COMPONENTS
	REQUIRED)


SET(libs
	#${Boost_LIBRARIES}
	pthread
	rt)

INCLUDE(cmh_library)

add_subdirectory(test)


