cmake_minimum_required (VERSION 2.8.8)

INCLUDE($ENV{HOME}/.config.cmake)

find_package(CMakeHelper)

project(galaxy_log)
INCLUDE(../../../../config.cmake)
INCLUDE(cmh_build_config)

INCLUDE(cmh_boost)
FIND_PACKAGE(Boost 1.55 COMPONENTS
<<<<<<< HEAD
	system
	thread
	REQUIRED)

SET(libs
	${Boost_LIBRARIES}
=======
	REQUIRED)


SET(libs
	#${Boost_LIBRARIES}
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
	pthread
	rt)

INCLUDE(cmh_library)

<<<<<<< HEAD
#add_subdirectory(test)
=======
add_subdirectory(test)
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507


