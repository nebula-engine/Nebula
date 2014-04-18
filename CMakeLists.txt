cmake_minimum_required (VERSION 2.6)

project(gru)

set(LIB_NAME gru)
set(PROJECT_NAME GRU)
set(PROJECT_name gru)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -D_DEBUG -std=c++0x")

include_directories("${PROJECT_SOURCE_DIR}/src")

set(CMAKE_INSTALL_PREFIX $ENV{HOME}/usr)

set(object_dir ${CMAKE_INSTALL_PREFIX}/include/glutpp/objects)
set(shader_dir ${CMAKE_INSTALL_PREFIX}/include/glutpp/glsl/shaders)

set(INSTALL_LIB_DIR ${CMAKE_INSTALL_PREFIX})
set(INSTALL_BIN_DIR ${CMAKE_INSTALL_PREFIX})
set(INSTALL_INCLUDE_DIR ${CMAKE_INSTALL_PREFIX}/include/math)
set(INSTALL_CMAKE_DIR ${CMAKE_INSTALL_PREFIX}/lib/${LIB_NAME})


# common methods for static library
# =================================
include(../cmake/static_library.cmake)


install(FILES ${PROJECT_SOURCE_DIR}/glutpp/glsl/shaders/v130/light/vs.glsl	DESTINATION include/glutpp/glsl/shaders/v130/light/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/glsl/shaders/v130/light/fs.glsl	DESTINATION include/glutpp/glsl/shaders/v130/light/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/glsl/shaders/v130/image/vs.glsl	DESTINATION include/glutpp/glsl/shaders/v130/image/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/glsl/shaders/v130/image/fs.glsl	DESTINATION include/glutpp/glsl/shaders/v130/image/)

install(FILES ${PROJECT_SOURCE_DIR}/glutpp/glsl/shaders/v130/quad/vs.glsl 	DESTINATION include/glutpp/glsl/shaders/v130/quad/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/glsl/shaders/v130/quad/fs.glsl 	DESTINATION include/glutpp/glsl/shaders/v130/quad/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/glsl/shaders/v130/text/vs.glsl 	DESTINATION include/glutpp/glsl/shaders/v130/text/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/glsl/shaders/v130/text/fs.glsl 	DESTINATION include/glutpp/glsl/shaders/v130/text/)


install(FILES ${PROJECT_SOURCE_DIR}/glutpp/objects/cube.obj DESTINATION include/glutpp/objects)



