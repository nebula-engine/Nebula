CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)

INCLUDE($ENV{HOME}/.config.cmake)

FIND_PACKAGE(CMakeHelper)

PROJECT(test_array_continuous)
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
	physx
	python
	final
	)

set(libs
	nebula_final_0_so_db
	nebula_physx_0_so_db
	nebula_core_0_so_db
	galaxy_std_0_so_db
	galaxy_log_0_so_db
	galaxy_console_0_so_db
	${glfw_LIBRARIES}
	/scratch/usr/lib/libboost_serialization.so.1.55.0
	/scratch/usr/lib/libboost_system.so.1.55.0
	/scratch/usr/lib/libboost_thread.so.1.55.0
	)

ADD_DEFINITIONS("-DGLM_FORCE_RADIANS")

message(STATUS "libs ${libs}")

INCLUDE(cmh_executable)


