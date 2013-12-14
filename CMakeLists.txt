cmake_minimum_required (VERSION 2.6)


project(glutpp)

set(src
	src/glutpp/camera_control.cpp
	src/glutpp/master.cpp
	src/glutpp/window.cpp
	src/glutpp/scene.cpp
	src/glutpp/renderable.cpp
	src/glutpp/object.cpp
	src/glutpp/shader.cpp
	src/glutpp/uniform.cpp
	src/glutpp/attribute.cpp
	src/glutpp/texture.cpp
	src/glutpp/program.cpp
	src/glutpp/camera.cpp
	src/glutpp/light.cpp
	src/glutpp/material.cpp
	src/glutpp/gui/layout.cpp
	src/glutpp/gui/object/object.cpp
	src/glutpp/gui/object/button.cpp
	src/glutpp/gui/object/textview.cpp
	src/glutpp/gui/object/edittext.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_DEBUG -std=c++0x")


add_library(glutpp ${src})

set(PROJECT_BINARY_DIR lib)
set(PROJECT_SOURCE_DIR src)

include_directories("${PROJECT_SOURCE_DIR}")

set(CMAKE_INSTALL_PREFIX $ENV{HOME}/usr)

set(object_dir ${CMAKE_INSTALL_PREFIX}/include/glutpp/objects)
set(shader_dir ${CMAKE_INSTALL_PREFIX}/include/glutpp/shaders)

configure_file("${PROJECT_SOURCE_DIR}/glutpp/config.h.in" "${PROJECT_SOURCE_DIR}/glutpp/config.h")

install(TARGETS glutpp DESTINATION lib)

install(FILES ${PROJECT_SOURCE_DIR}/glutpp/config.h DESTINATION include/glutpp/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/master.h DESTINATION include/glutpp/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/window.h DESTINATION include/glutpp/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/object.h DESTINATION include/glutpp/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/shader.h DESTINATION include/glutpp/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/texture.h DESTINATION include/glutpp/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/program.h DESTINATION include/glutpp/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/uniform.h DESTINATION include/glutpp/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/attribute.h DESTINATION include/glutpp/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/camera.h DESTINATION include/glutpp/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/camera_control.h DESTINATION include/glutpp/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/light.h DESTINATION include/glutpp/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/material.h DESTINATION include/glutpp/)

install(FILES ${PROJECT_SOURCE_DIR}/glutpp/gui/layout.h DESTINATION include/glutpp/gui)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/gui/object/object.h DESTINATION include/glutpp/gui/object)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/gui/object/button.h DESTINATION include/glutpp/gui/object)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/gui/object/textview.h DESTINATION include/glutpp/gui/object)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/gui/object/edittext.h DESTINATION include/glutpp/gui/object)

install(FILES ${PROJECT_SOURCE_DIR}/glutpp/shaders/prog_0/vs.glsl DESTINATION include/glutpp/shaders/prog_0)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/shaders/prog_0/fs.glsl DESTINATION include/glutpp/shaders/prog_0)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/shaders/prog1/vs.glsl DESTINATION include/glutpp/shaders/prog1)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/shaders/prog1/fs.glsl DESTINATION include/glutpp/shaders/prog1)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/shaders/exp_map/vs.glsl DESTINATION include/glutpp/shaders/exp_map)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/shaders/exp_map/fs.glsl DESTINATION include/glutpp/shaders/exp_map)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/shaders/prog3/vs.glsl DESTINATION include/glutpp/shaders/prog3)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/shaders/prog3/fs.glsl DESTINATION include/glutpp/shaders/prog3)

install(FILES ${PROJECT_SOURCE_DIR}/glutpp/objects/cube.obj DESTINATION include/glutpp/objects)



