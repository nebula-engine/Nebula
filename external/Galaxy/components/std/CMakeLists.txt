CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)

<<<<<<< HEAD
#INCLUDE($ENV{HOME}/.config.cmake)
=======
INCLUDE($ENV{HOME}/.config.cmake)
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507

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

