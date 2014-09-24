CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)

INCLUDE($ENV{HOME}/.config.cmake)

FIND_PACKAGE(CMakeHelper)

PROJECT(test_dll_sh1)
INCLUDE(../../../../../../../config.cmake)
INCLUDE(cmh_build_config)


SET(libs
	)

INCLUDE(cmh_library)


