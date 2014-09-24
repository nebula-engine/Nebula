CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)

INCLUDE("$ENV{HOME}/.config.cmake")

PROJECT(galaxy_network)

SET(galaxy_network_STATIC TRUE)
SET(galaxy_network_SHARED TRUE)

FIND_PACKAGE(CMakeHelper)

FIND_PACKAGE(Galaxy COMPONENTS
	std
	REQUIRED)

FIND_PACKAGE(Boost 1.55 COMPONENTS
	system
	thread
	REQUIRED)

SET(libs
	${PROJECT_NAME}
	${Galaxy_LIBRARIES}
	${Boost_LIBRARIES}
	pthread
	rt
	)

cmh_library()
	
ADD_SUBDIRECTORY(test)

