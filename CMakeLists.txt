cmake_minimum_required (VERSION 2.6)
include(ExternalProject)

project(nebula)

set(PROJECT_SOURCE_DIR src)

AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/neb files_src_neb) 
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/neb/actor files_src_neb_actor)
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/neb/scene files_src_neb_scene)
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/neb/network files_src_neb_network)
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/neb/packet files_src_neb_packet)

add_library(nebula 
	${files_src_neb}
	${files_src_neb_network}
	${files_src_neb_packet}
	${files_src_neb_scene}
	${files_src_neb_actor})

include_directories("${PROJECT_SOURCE_DIR}")

configure_file("${PROJECT_SOURCE_DIR}/neb/config.h.in" "${PROJECT_SOURCE_DIR}/neb/config.h")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -D_DEBUG -std=c++0x -Wall -Wno-unknown-pragmas -Wno-unused-local-typedefs -rdynamic -pthread")
set(CMAKE_INSTALL_PREFIX $ENV{HOME}/usr)


install(TARGETS nebula DESTINATION lib)

set(files
	${PROJECT_SOURCE_DIR}/neb/config.h
	${PROJECT_SOURCE_DIR}/neb/app.h
	${PROJECT_SOURCE_DIR}/neb/user.h
	${PROJECT_SOURCE_DIR}/neb/physics.h
	${PROJECT_SOURCE_DIR}/neb/vehicle_manager.h
	${PROJECT_SOURCE_DIR}/neb/simulation_callback.h
)
install(FILES ${files} DESTINATION include/neb/)

install(FILES ${PROJECT_SOURCE_DIR}/neb/packet/packet.h		DESTINATION include/neb/packet)

install(FILES ${PROJECT_SOURCE_DIR}/neb/scene/scene.h		DESTINATION include/neb/scene)

install(FILES ${PROJECT_SOURCE_DIR}/neb/camera.h		DESTINATION include/neb/)
install(FILES ${PROJECT_SOURCE_DIR}/neb/shape.h			DESTINATION include/neb/)
install(FILES ${PROJECT_SOURCE_DIR}/neb/actor/Base.h		DESTINATION include/neb/actor/)
install(FILES ${PROJECT_SOURCE_DIR}/neb/actor/empty.h		DESTINATION include/neb/actor/)
install(FILES ${PROJECT_SOURCE_DIR}/neb/actor/Actor.h		DESTINATION include/neb/actor/)
install(FILES ${PROJECT_SOURCE_DIR}/neb/actor/Rigid_Actor.h	DESTINATION include/neb/actor/)
install(FILES ${PROJECT_SOURCE_DIR}/neb/actor/Rigid_Body.h	DESTINATION include/neb/actor/)
install(FILES ${PROJECT_SOURCE_DIR}/neb/actor/Rigid_Dynamic.h	DESTINATION include/neb/actor/)
install(FILES ${PROJECT_SOURCE_DIR}/neb/actor/Rigid_Static.h	DESTINATION include/neb/actor/)
install(FILES ${PROJECT_SOURCE_DIR}/neb/actor/Controller.h	DESTINATION include/neb/actor/)

set(files
	${PROJECT_SOURCE_DIR}/neb/network/communicating.h
	${PROJECT_SOURCE_DIR}/neb/network/client.h
	${PROJECT_SOURCE_DIR}/neb/network/server.h
)

install(FILES ${files} DESTINATION include/neb/network/)


add_dependencies(nebula glutpp)

ExternalProject_Add(
        glutpp
        PREFIX "$ENV{HOME}/Programming/C++/glutpp"
        SOURCE_DIR "$ENV{HOME}/Programming/C++/glutpp"
        BUILD_IN_SOURCE 1
	BUILD_COMMAND make install
)


