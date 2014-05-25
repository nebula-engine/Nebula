cmake_minimum_required (VERSION 2.8.7)
#include(ExternalProject)

project (box)

include_directories(../../nebula/src ../../glutpp/src ../../galaxy/src ../../math/src)
link_directories(../../nebula ../../glutpp ../../galaxy ../../math)

add_executable(box src/main.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -D_DEBUG -std=c++0x -Wall -Wno-unknown-pragmas -Wno-unused-local-typedefs -rdynamic -pthread -pg")

#find_package(Nebula REQUIRED)

#MESSAGE("${NEBULA_LIBRARIES}")

#set(LIBS ${LIBS} ${MATH_LIBRARIES} ${GRU_LIBRARIES} ${GALAXY_LIBRARIES} ${NEBULA_LIBRARIES})

set(LIBS_BOOST boost_system boost_serialization boost_log boost_thread)

set(LIBS Nebula ${LIBS_BOOST})

#ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)

SET(Boost_USE_STATIC_LIBS ON)
FIND_PACKAGE(Boost 1.54 COMPONENTS log REQUIRED)

#MESSAGE("${LIBS}")

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

target_link_libraries(box ${LIBS})
target_link_libraries(box ${LIBS})

target_link_libraries(box GL GLU)
target_link_libraries(box glfw3)
target_link_libraries(box GLEW)
target_link_libraries(box freetype)
target_link_libraries(box png)
target_link_libraries(box tinyxml2)
target_link_libraries(box rt)
target_link_libraries(box pthread)
target_link_libraries(box X11)
target_link_libraries(box Xrandr)
target_link_libraries(box X11)
target_link_libraries(box ${GLFW_STATIC_LIBRARIES})

target_link_libraries(box PhysX3CHECKED)
target_link_libraries(box SimulationControllerCHECKED)
target_link_libraries(box LowLevelCHECKED)
target_link_libraries(box LowLevelClothCHECKED)
target_link_libraries(box PhysXProfileSDKCHECKED)
target_link_libraries(box PhysXVisualDebuggerSDKCHECKED)
target_link_libraries(box PhysX3ExtensionsCHECKED)
target_link_libraries(box SceneQueryCHECKED)
target_link_libraries(box PhysX3CommonCHECKED)
target_link_libraries(box PhysX3CharacterKinematicCHECKED)
target_link_libraries(box PhysX3VehicleCHECKED)
target_link_libraries(box PhysX3CookingCHECKED)
target_link_libraries(box PvdRuntimeCHECKED)
target_link_libraries(box RepX3CHECKED)
target_link_libraries(box PxTaskCHECKED)

target_link_libraries(box PhysX3CHECKED)
target_link_libraries(box SimulationControllerCHECKED)
target_link_libraries(box LowLevelCHECKED)
target_link_libraries(box LowLevelClothCHECKED)
target_link_libraries(box PhysXProfileSDKCHECKED)
target_link_libraries(box PhysX3ExtensionsCHECKED)
target_link_libraries(box SceneQueryCHECKED)
target_link_libraries(box PhysX3CommonCHECKED)
target_link_libraries(box PhysX3CharacterKinematicCHECKED)
target_link_libraries(box PhysX3VehicleCHECKED)
target_link_libraries(box PhysX3CookingCHECKED)
target_link_libraries(box PvdRuntimeCHECKED)
target_link_libraries(box RepX3CHECKED)
target_link_libraries(box PxTaskCHECKED)

INSTALL(TARGETS box DESTINATION nebula_demo)

#add_dependencies(box nebula glutpp galaxy math)

SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Charles Rymal") #required
SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MINOR "1")
SET(CPACK_PACKAGE_VERSION_PATCH "1") 

INCLUDE(CPack)


