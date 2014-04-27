#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glu.h>

#include <map>

//#include <GL/glew.h>
//#include <GL/glut.h>

#include <math/color.hpp>

#include <gru/free.hpp>
#include <gru/window/desc.hpp>
#include <gru/window/window.hpp>
#include <gru/actor/actor.hpp>
#include <gru/light/light.hpp>
#include <gru/renderable.hpp>








glutpp::window::window::window(glutpp::window::desc_s desc) {
	GLUTPP_DEBUG_0_FUNCTION;

	raw_ = desc->raw_;

	printf(GLUTPP_INSTALL_DIR);
	printf("\n");

}
glutpp::window::window::~window() {
	GLUTPP_DEBUG_0_FUNCTION;

	glfwDestroyWindow(window_);
}
unsigned int glutpp::window::window::f() {
	return raw_.flag_;
}
void glutpp::window::window::f(unsigned int flag) {
	raw_.flag_ = flag;
}
void glutpp::window::window::set_scene(glutpp::scene::scene_s scene) {

	GLUTPP_DEBUG_0_FUNCTION;

	assert(scene);
	assert(renderable_);

	renderable_->scene_ = scene;
}
void glutpp::window::window::init() {
	GLUTPP_DEBUG_0_FUNCTION;

	//printf("%s\n",glGetString(GL_SHADING_LANGUAGE_VERSION));

	//Check for necessary extensions
	if(!GL_ARB_depth_texture || !GL_ARB_shadow)
	{
		printf("I require ARB_depth_texture and ARB_shadow extensionsn\n");
		exit(0);//return false;
	}

	//Shading states
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//Depth states

	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_NORMALIZE);


	renderable_.reset(new glutpp::renderable(shared_from_this()));
	renderable_->init(shared_from_this());

	checkerror("unknown");
}
void glutpp::window::window::render(double time) {
	GLUTPP_DEBUG_1_FUNCTION;

	glfwMakeContextCurrent(window_);

	if(renderable_) {
		renderable_->render(time, shared_from_this());
	} else {
		printf("no renderable\n");
	}

	glFinish();
	glfwSwapBuffers(window_);
}
void glutpp::window::window::callback_window_refresh_fun(GLFWwindow*) {
}
void glutpp::window::window::step(double time) {
	GLUTPP_DEBUG_1_FUNCTION;

	if(glfwWindowShouldClose(window_))
	{
		set(flag::e::SHOULD_RELEASE);
		return;
	}

	render(time);
}
void glutpp::window::window::callback_window_size_fun(GLFWwindow* window, int w, int h) {
	GLUTPP_DEBUG_0_FUNCTION;

	raw_.w_ = w;
	raw_.h_ = h;

	resize();

	callback_window_refresh_fun(window);
}
void glutpp::window::window::callback_window_pos_fun(GLFWwindow* window, int x, int y) {
	GLUTPP_DEBUG_0_FUNCTION;

	raw_.x_ = x;
	raw_.y_ = y;

	callback_window_refresh_fun(window);
}
void glutpp::window::window::callback_window_close_fun(GLFWwindow* window){
	GLUTPP_DEBUG_0_FUNCTION;

}
void glutpp::window::window::callback_mouse_button_fun(GLFWwindow* window, int button, int action, int mods) {
	GLUTPP_DEBUG_0_FUNCTION;
	
	sig_.mouse_button_fun_(button, action, mods);
}
void glutpp::window::window::callback_key_fun(GLFWwindow* window, int key, int scancode, int action, int mods) {
	GLUTPP_DEBUG_0_FUNCTION;
	
	sig_.key_fun_(key, scancode, action, mods);
	
}
void glutpp::window::window::resize() {

	glViewport(0, 0, raw_.w_, raw_.h_);

	renderable_->resize(raw_.w_, raw_.h_);
}
void glutpp::window::window::set_layout(glutpp::gui::layout_s layout) {

	printf("%s\n", __PRETTY_FUNCTION__);

	assert(layout);
	assert(renderable_);

	renderable_->layout_ = layout;

	layout->init(renderable_);
	layout->connect();
}
void glutpp::window::window::i(int ni) {

	i_ = ni;
}





