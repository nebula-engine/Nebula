CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)

INCLUDE("$ENV{HOME}/.config.cmake")

#SET(install_file "${PROJECT_SOURCE_DIR}/FindGalaxy.cmake")
SET(install_file "${PROJECT_SOURCE_DIR}/GalaxyConfig.cmake")

install(FILES
	${install_file}
	DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Galaxy" COMPONENT dev)


