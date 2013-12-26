cmake_minimum_required (VERSION 2.6)


project(glutpp)

set(src
	src/glutpp/free.cpp
	src/glutpp/camera_control.cpp
	src/glutpp/master.cpp
	src/glutpp/window.cpp
	src/glutpp/scene.cpp
	src/glutpp/renderable.cpp
	src/glutpp/actor.cpp
	src/glutpp/shape.cpp
	src/glutpp/shape_desc.cpp
	src/glutpp/glsl/shader.cpp
	src/glutpp/glsl/uniform.cpp
	src/glutpp/glsl/attrib.cpp
	src/glutpp/texture.cpp
	src/glutpp/glsl/program.cpp
	src/glutpp/camera.cpp
	src/glutpp/light.cpp
	src/glutpp/desc_light.cpp
	src/glutpp/material.cpp
	src/glutpp/gui/layout.cpp
	src/glutpp/gui/object/object.cpp
	src/glutpp/gui/object/object_factory.cpp
	src/glutpp/gui/object/textview.cpp
	src/glutpp/gui/object/edittext.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -D_DEBUG -std=c++0x")


add_library(glutpp ${src})

set(PROJECT_BINARY_DIR lib)
set(PROJECT_SOURCE_DIR src)

include_directories("${PROJECT_SOURCE_DIR}")

set(CMAKE_INSTALL_PREFIX $ENV{HOME}/usr)

set(object_dir ${CMAKE_INSTALL_PREFIX}/include/glutpp/objects)
set(shader_dir ${CMAKE_INSTALL_PREFIX}/include/glutpp/glsl/shaders)

configure_file("${PROJECT_SOURCE_DIR}/glutpp/config.h.in" "${PROJECT_SOURCE_DIR}/glutpp/config.h")

install(TARGETS glutpp DESTINATION lib)

install(FILES ${PROJECT_SOURCE_DIR}/glutpp/config.h		DESTINATION include/glutpp/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/types.h		DESTINATION include/glutpp/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/free.h		DESTINATION include/glutpp/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/master.h		DESTINATION include/glutpp/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/window.h		DESTINATION include/glutpp/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/renderable.h		DESTINATION include/glutpp/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/scene.h		DESTINATION include/glutpp/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/actor.h		DESTINATION include/glutpp/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/shape.h		DESTINATION include/glutpp/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/shape_desc.h		DESTINATION include/glutpp/)



install(FILES ${PROJECT_SOURCE_DIR}/glutpp/glsl/shader.h		DESTINATION include/glutpp/glsl/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/glsl/program.h		DESTINATION include/glutpp/glsl/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/glsl/uniform.h		DESTINATION include/glutpp/glsl/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/glsl/attrib.h		DESTINATION include/glutpp/glsl/)

install(FILES ${PROJECT_SOURCE_DIR}/glutpp/texture.h			DESTINATION include/glutpp/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/camera.h			DESTINATION include/glutpp/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/camera_control.h		DESTINATION include/glutpp/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/light.h			DESTINATION include/glutpp/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/desc_light.h			DESTINATION include/glutpp/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/material.h			DESTINATION include/glutpp/)

install(FILES ${PROJECT_SOURCE_DIR}/glutpp/gui/layout.h			DESTINATION include/glutpp/gui)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/gui/object/object.h		DESTINATION include/glutpp/gui/object)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/gui/object/textview.h	DESTINATION include/glutpp/gui/object)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/gui/object/edittext.h	DESTINATION include/glutpp/gui/object)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/gui/object/object_factory.h	DESTINATION include/glutpp/gui/object)

install(FILES ${PROJECT_SOURCE_DIR}/glutpp/glsl/shaders/v130/light/vs.glsl	DESTINATION include/glutpp/glsl/shaders/v130/light/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/glsl/shaders/v130/light/fs.glsl	DESTINATION include/glutpp/glsl/shaders/v130/light/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/glsl/shaders/v130/quad/vs.glsl 	DESTINATION include/glutpp/glsl/shaders/v130/quad/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/glsl/shaders/v130/quad/fs.glsl 	DESTINATION include/glutpp/glsl/shaders/v130/quad/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/glsl/shaders/v130/text/vs.glsl 	DESTINATION include/glutpp/glsl/shaders/v130/text/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/glsl/shaders/v130/text/fs.glsl 	DESTINATION include/glutpp/glsl/shaders/v130/text/)

install(FILES ${PROJECT_SOURCE_DIR}/glutpp/objects/cube.obj DESTINATION include/glutpp/objects)



