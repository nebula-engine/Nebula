cmake_minimum_required (VERSION 2.6)

project(glutpp)

set(PROJECT_BINARY_DIR lib)
set(PROJECT_SOURCE_DIR src)

AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/glutpp		files_src_glutpp)
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/glutpp/window	files_src_glutpp_window)
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/glutpp/scene		files_src_glutpp_scene)
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/glutpp/actor		files_src_glutpp_actor)
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/glutpp/shape		files_src_glutpp_shape)
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/glutpp/light		files_src_glutpp_light)
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/glutpp/glsl		files_src_glutpp_glsl)
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/glutpp/gui		files_src_glutpp_gui)
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/glutpp/gui/object	files_src_glutpp_gui_object)


add_library(glutpp
	${files_src_glutpp}
	${files_src_glutpp_window}
	${files_src_glutpp_scene}
	${files_src_glutpp_actor}
	${files_src_glutpp_shape}
	${files_src_glutpp_light}
	${files_src_glutpp_glsl}
	${files_src_glutpp_gui}
	${files_src_glutpp_gui_object}
)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -D_DEBUG -std=c++0x")

include_directories("${PROJECT_SOURCE_DIR}")

set(CMAKE_INSTALL_PREFIX $ENV{HOME}/usr)

set(object_dir ${CMAKE_INSTALL_PREFIX}/include/glutpp/objects)
set(shader_dir ${CMAKE_INSTALL_PREFIX}/include/glutpp/glsl/shaders)

configure_file("${PROJECT_SOURCE_DIR}/glutpp/config.h.in" "${PROJECT_SOURCE_DIR}/glutpp/config.h")

install(TARGETS glutpp DESTINATION lib)

install(FILES ${PROJECT_SOURCE_DIR}/glutpp/config.h		DESTINATION include/glutpp/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/free.h		DESTINATION include/glutpp/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/master.h		DESTINATION include/glutpp/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/renderable.h		DESTINATION include/glutpp/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/mesh.h		DESTINATION include/glutpp/)

install(FILES ${PROJECT_SOURCE_DIR}/glutpp/window/window.h	DESTINATION include/glutpp/window)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/window/desc.h	DESTINATION include/glutpp/window)

install(FILES ${PROJECT_SOURCE_DIR}/glutpp/scene/desc.h		DESTINATION include/glutpp/scene)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/scene/scene.h	DESTINATION include/glutpp/scene)

install(FILES ${PROJECT_SOURCE_DIR}/glutpp/actor/desc.h		DESTINATION include/glutpp/actor/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/actor/actor.h	DESTINATION include/glutpp/actor/)

install(FILES ${PROJECT_SOURCE_DIR}/glutpp/shape/shape.h	DESTINATION include/glutpp/shape)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/shape/desc.h		DESTINATION include/glutpp/shape)



install(FILES ${PROJECT_SOURCE_DIR}/glutpp/glsl/shader.h		DESTINATION include/glutpp/glsl/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/glsl/program.h		DESTINATION include/glutpp/glsl/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/glsl/uniform.h		DESTINATION include/glutpp/glsl/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/glsl/attrib.h		DESTINATION include/glutpp/glsl/)

install(FILES ${PROJECT_SOURCE_DIR}/glutpp/texture.h			DESTINATION include/glutpp/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/camera.h			DESTINATION include/glutpp/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/camera_control.h		DESTINATION include/glutpp/)

install(FILES ${PROJECT_SOURCE_DIR}/glutpp/light/light.h		DESTINATION include/glutpp/light)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/light/desc.h			DESTINATION include/glutpp/light)

install(FILES ${PROJECT_SOURCE_DIR}/glutpp/material.h			DESTINATION include/glutpp/)

install(FILES ${PROJECT_SOURCE_DIR}/glutpp/gui/layout.h			DESTINATION include/glutpp/gui)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/gui/object/object.h		DESTINATION include/glutpp/gui/object)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/gui/object/textview.h	DESTINATION include/glutpp/gui/object)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/gui/object/edittext.h	DESTINATION include/glutpp/gui/object)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/gui/object/object_factory.h	DESTINATION include/glutpp/gui/object)


install(FILES ${PROJECT_SOURCE_DIR}/glutpp/glsl/shaders/v130/light/vs.glsl	DESTINATION include/glutpp/glsl/shaders/v130/light/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/glsl/shaders/v130/light/fs.glsl	DESTINATION include/glutpp/glsl/shaders/v130/light/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/glsl/shaders/v130/image/vs.glsl	DESTINATION include/glutpp/glsl/shaders/v130/image/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/glsl/shaders/v130/image/fs.glsl	DESTINATION include/glutpp/glsl/shaders/v130/image/)

install(FILES ${PROJECT_SOURCE_DIR}/glutpp/glsl/shaders/v130/quad/vs.glsl 	DESTINATION include/glutpp/glsl/shaders/v130/quad/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/glsl/shaders/v130/quad/fs.glsl 	DESTINATION include/glutpp/glsl/shaders/v130/quad/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/glsl/shaders/v130/text/vs.glsl 	DESTINATION include/glutpp/glsl/shaders/v130/text/)
install(FILES ${PROJECT_SOURCE_DIR}/glutpp/glsl/shaders/v130/text/fs.glsl 	DESTINATION include/glutpp/glsl/shaders/v130/text/)


install(FILES ${PROJECT_SOURCE_DIR}/glutpp/objects/cube.obj DESTINATION include/glutpp/objects)



