cmake_minimum_required (VERSION 2.6)
include(ExternalProject)

project(nebula)

set(PROJECT_SOURCE_DIR src)

add_library(nebula
	src/neb/physics.cpp
	src/neb/scene.cpp
	src/neb/view.cpp
	src/neb/shape.cpp
	src/neb/camera.cpp
	src/neb/camera_ridealong.cpp
	src/neb/actor/Base.cpp
	src/neb/actor/Actor.cpp
	src/neb/actor/Rigid_Actor.cpp
	src/neb/actor/Rigid_Body.cpp
	src/neb/actor/Rigid_Dynamic.cpp
	src/neb/actor/Rigid_Static.cpp
	src/neb/actor/Light.cpp
	src/neb/actor/Controller.cpp
)

include_directories("${PROJECT_SOURCE_DIR}")

configure_file("${PROJECT_SOURCE_DIR}/neb/config.h.in" "${PROJECT_SOURCE_DIR}/neb/config.h")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_DEBUG -std=c++0x -Wall -Wno-unknown-pragmas -rdynamic -pthread")
set(CMAKE_INSTALL_PREFIX $ENV{HOME}/usr)


install(TARGETS nebula DESTINATION lib)

install(FILES ${PROJECT_SOURCE_DIR}/neb/config.h	DESTINATION include/neb/)
install(FILES ${PROJECT_SOURCE_DIR}/neb/physics.h	DESTINATION include/neb/)
install(FILES ${PROJECT_SOURCE_DIR}/neb/scene.h DESTINATION include/neb/)
install(FILES ${PROJECT_SOURCE_DIR}/neb/view.h DESTINATION include/neb/)
install(FILES ${PROJECT_SOURCE_DIR}/neb/camera.h DESTINATION include/neb/)
install(FILES ${PROJECT_SOURCE_DIR}/neb/shape.h DESTINATION include/neb/)
install(FILES ${PROJECT_SOURCE_DIR}/neb/actor/Base.h DESTINATION include/neb/actor/)
install(FILES ${PROJECT_SOURCE_DIR}/neb/actor/Actor.h DESTINATION include/neb/actor/)
install(FILES ${PROJECT_SOURCE_DIR}/neb/actor/Rigid_Actor.h DESTINATION include/neb/actor/)
install(FILES ${PROJECT_SOURCE_DIR}/neb/actor/Rigid_Body.h DESTINATION include/neb/actor/)
install(FILES ${PROJECT_SOURCE_DIR}/neb/actor/Rigid_Dynamic.h DESTINATION include/neb/actor/)
install(FILES ${PROJECT_SOURCE_DIR}/neb/actor/Rigid_Static.h DESTINATION include/neb/actor/)
install(FILES ${PROJECT_SOURCE_DIR}/neb/actor/Light.h DESTINATION include/neb/actor/)
install(FILES ${PROJECT_SOURCE_DIR}/neb/actor/Controller.h DESTINATION include/neb/actor/)

add_dependencies(nebula glutpp)

ExternalProject_Add(
        glutpp
        PREFIX "$ENV{HOME}/Programming/C++/glutpp"
        SOURCE_DIR "$ENV{HOME}/Programming/C++/glutpp"
        BUILD_IN_SOURCE 1
	BUILD_COMMAND make install
)


