CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)

INCLUDE($ENV{HOME}/.config.cmake)

FIND_PACKAGE(CMakeHelper)

PROJECT(nebula_python)
INCLUDE(../../config.cmake)
INCLUDE(cmh_build_config)


INCLUDE(cmh_boost)
FIND_PACKAGE(Boost 1.55 COMPONENTS
	system
	thread
	python
	serialization
	REQUIRED)

FIND_PACKAGE(galaxy 0 COMPONENTS std REQUIRED)
FIND_PACKAGE(nebula 0 COMPONENTS core REQUIRED)


#SET(Nebula_SHARED TRUE)
#FIND_PACKAGE(Nebula COMPONENETS core REQUIRED)

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
INCLUDE_DIRECTORIES("/usr/include/python2.7")
include_directories("/usr/include/freetype2")
include_directories(${physx_INCLUDE_DIR})


ADD_DEFINITIONS("-D_DEBUG -DGAL_NET_USE_BOOST -DGLM_FORCE_RADIANS")

SET(libs
	${Nebula_LIBRARIES}
	${Galaxy_LIBRARIES}
	${Boost_LIBRARIES}
	python2.7
	pthread
   )

INCLUDE(cmh_library)

#ADD_SUBDIRECTORY(test)

