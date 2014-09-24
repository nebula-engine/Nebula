CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)

INCLUDE($ENV{HOME}/.config.cmake)

FIND_PACKAGE(CMakeHelper)

PROJECT(test_map)
INCLUDE(../../../../../../../config.cmake)
INCLUDE(cmh_build_config)

ADD_DEFINITIONS("-DGLM_FORCE_RADIANS")

SET(libs
	galaxy_std_0_so_db
	/scratch/usr/lib/libboost_system.so.1.55.0
	)


INCLUDE(cmh_executable)


