CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)

INCLUDE("$ENV{HOME}/.config.cmake")

#SET(install_file "${PROJECT_SOURCE_DIR}/FindNebula.cmake")
SET(install_file "${PROJECT_SOURCE_DIR}/NebulaConfig.cmake")

install(FILES
	${install_file}
	DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Nebula" COMPONENT dev)


