cmake_minimum_required (VERSION 2.6)
include(ExternalProject)

project(nebula)

set(PROJECT_SOURCE_DIR src)

add_library(nebula
	src/neb/app.cpp
	src/neb/user.cpp
	src/neb/physics.cpp
	src/neb/scene.cpp
	src/neb/simulation_callback.cpp
	src/neb/view.cpp
	src/neb/shape.cpp
	src/neb/camera.cpp
	src/neb/camera_ridealong.cpp
	src/neb/packet/basic.cpp
	src/neb/actor/desc.cpp
	src/neb/actor/Base.cpp
	src/neb/actor/Actor.cpp
	src/neb/actor/Rigid_Actor.cpp
	src/neb/actor/Rigid_Body.cpp
	src/neb/actor/Rigid_Dynamic.cpp
	src/neb/actor/Rigid_Static.cpp
	src/neb/actor/Light.cpp
	src/neb/actor/Controller.cpp
	src/neb/network/server.cpp
	src/neb/network/client.cpp
	src/neb/network/communicating.cpp
)

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
	${PROJECT_SOURCE_DIR}/neb/scene.h
	${PROJECT_SOURCE_DIR}/neb/simulation_callback.h
)

install(FILES ${files} DESTINATION include/neb/)

install(FILES ${PROJECT_SOURCE_DIR}/neb/packet/basic.h		DESTINATION include/neb/packet)
install(FILES ${PROJECT_SOURCE_DIR}/neb/packet/packet.h		DESTINATION include/neb/packet)


install(FILES ${PROJECT_SOURCE_DIR}/neb/view.h			DESTINATION include/neb/)
install(FILES ${PROJECT_SOURCE_DIR}/neb/camera.h		DESTINATION include/neb/)
install(FILES ${PROJECT_SOURCE_DIR}/neb/shape.h			DESTINATION include/neb/)
install(FILES ${PROJECT_SOURCE_DIR}/neb/actor/desc.h		DESTINATION include/neb/actor/)
install(FILES ${PROJECT_SOURCE_DIR}/neb/actor/Base.h		DESTINATION include/neb/actor/)
install(FILES ${PROJECT_SOURCE_DIR}/neb/actor/Actor.h		DESTINATION include/neb/actor/)
install(FILES ${PROJECT_SOURCE_DIR}/neb/actor/Rigid_Actor.h	DESTINATION include/neb/actor/)
install(FILES ${PROJECT_SOURCE_DIR}/neb/actor/Rigid_Body.h	DESTINATION include/neb/actor/)
install(FILES ${PROJECT_SOURCE_DIR}/neb/actor/Rigid_Dynamic.h	DESTINATION include/neb/actor/)
install(FILES ${PROJECT_SOURCE_DIR}/neb/actor/Rigid_Static.h	DESTINATION include/neb/actor/)
install(FILES ${PROJECT_SOURCE_DIR}/neb/actor/Light.h		DESTINATION include/neb/actor/)
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


