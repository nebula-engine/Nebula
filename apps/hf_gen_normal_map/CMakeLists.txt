CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)

INCLUDE($ENV{HOME}/.config.cmake)

FIND_PACKAGE(CMakeHelper)

PROJECT(hf_gen_normal_map)
INCLUDE(../../config.cmake)
INCLUDE(cmh_build_config)

INCLUDE(../../external/glfw.cmake)

FIND_PACKAGE(PhysX)
FIND_PACKAGE(galaxy 0 COMPONENTS
	std
	log
	console)
FIND_PACKAGE(nebula 0 COMPONENTS
	core
	gfx
	physx
	python
	final
	)

set(libs
	nebula_final_0
	nebula_physx_0
	nebula_core_0
	galaxy_std_0
	galaxy_log_0
	galaxy_console_0
	${glfw_LIBRARIES}
	${physx_LIBRARIES}
	/usr/lib/x86_64-linux-gnu/libboost_serialization.so.1.55.0
	/usr/lib/x86_64-linux-gnu/libboost_system.so.1.55.0
	/usr/lib/x86_64-linux-gnu/libboost_thread.so.1.55.0
	/usr/lib/x86_64-linux-gnu/libboost_python-py27.so.1.55.0
	dl
	python2.7
	)

ADD_DEFINITIONS("-DGLM_FORCE_RADIANS")

message(STATUS "libs ${libs}")

INCLUDE(cmh_executable)


