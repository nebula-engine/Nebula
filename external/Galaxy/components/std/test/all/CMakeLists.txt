CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)

PROJECT(test-all)

SET(CMAKE_INSTALL_PREFIX /scratch/usr)

FIND_PACKAGE(CMakeHelper)

INCLUDE(${CMakeHelper_INCLUDE_DIR}/CMakeHelper/functions.cmake)

SET(Boost_USE_STATIC_LIBS ON)
SET(Boost_NO_SYSTEM_PATHS ON)
SET(BOOST_ROOT /scratch/usr)

#FIND_PACKAGE(Boost 1.55 COMPONENTS system thread REQUIRED)

MESSAGE(STATUS "boost: ${Boost_SYSTEM_LIBRARY}")

SET(libs
	Galaxy-Standard
	${Boost_SYSTEM_LIBRARY}
	${Boost_THREAD_LIBRARY}
	pthread
	rt
	)

link_exe()

