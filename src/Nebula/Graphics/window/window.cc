#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glu.h>

#include <map>

//#include <GL/glew.h>
//#include <GL/glut.h>

#include <Nebula/Scene/Types.hpp>

#include <Nebula/free.hpp>
#include <Nebula/Actor/Base.hpp>

#include <Nebula/renderable.hpp>
#include <Nebula/Graphics/window/desc.hpp>
#include <Nebula/Graphics/window/window.hpp>
#include <Nebula/Graphics/light/light.hpp>

/** @todo get rid of my unique ptr class. Just use private member and be careful not to pass around shared ptrs to things */

Neb::window::window::window(Neb::window::desc_s desc) {
	GLUTPP_DEBUG_0_FUNCTION;

	raw_ = desc->raw_;

	printf(GLUTPP_INSTALL_DIR);
	printf("\n");

}
Neb::window::window::~window() {
	GLUTPP_DEBUG_0_FUNCTION;

	glfwDestroyWindow(window_);
}
unsigned int const &	Neb::window::window::f() const {
	return raw_.flag_;
}
void Neb::window::window::f(unsigned int const & flag) {
	raw_.flag_ = flag;
}
void		Neb::window::window::set_scene(Neb::Scene::scene_s & scene) {

	GLUTPP_DEBUG_0_FUNCTION;

	assert(scene);
	assert(renderable_);
	
	renderable_->moveScene(std::move(scene));
}
void Neb::window::window::init() {
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


	renderable_.reset(new Neb::renderable(shared_from_this()));
	renderable_->init(shared_from_this());

	checkerror("unknown");
}
void Neb::window::window::render(double time) {
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
void Neb::window::window::callback_window_refresh_fun(GLFWwindow*) {
}
void Neb::window::window::step(double time) {
	GLUTPP_DEBUG_1_FUNCTION;

	if(glfwWindowShouldClose(window_))
	{
		set(flag::e::SHOULD_RELEASE);
		return;
	}

	render(time);
}
void Neb::window::window::callback_window_size_fun(GLFWwindow* window, int w, int h) {
	GLUTPP_DEBUG_0_FUNCTION;

	raw_.w_ = w;
	raw_.h_ = h;

	resize();

	callback_window_refresh_fun(window);
}
void Neb::window::window::callback_window_pos_fun(GLFWwindow* window, int x, int y) {
	GLUTPP_DEBUG_0_FUNCTION;

	raw_.x_ = x;
	raw_.y_ = y;

	callback_window_refresh_fun(window);
}
void Neb::window::window::callback_window_close_fun(GLFWwindow* window){
	GLUTPP_DEBUG_0_FUNCTION;

}
void Neb::window::window::callback_mouse_button_fun(GLFWwindow* window, int button, int action, int mods) {
	GLUTPP_DEBUG_0_FUNCTION;
	
	sig_.mouse_button_fun_(button, action, mods);
}
void Neb::window::window::callback_key_fun(GLFWwindow* window, int key, int scancode, int action, int mods) {
	GLUTPP_DEBUG_0_FUNCTION;
	
	sig_.key_fun_(key, scancode, action, mods);
	
}
void Neb::window::window::resize() {

	glViewport(0, 0, raw_.w_, raw_.h_);

	renderable_->resize(raw_.w_, raw_.h_);
}
void		Neb::window::window::set_layout(Neb::gui::layout_s & layout) {

	printf("%s\n", __PRETTY_FUNCTION__);

	assert(layout);
	assert(renderable_);
	
	renderable_->moveLayout(std::move(layout));
	
	layout->init(renderable_);
	layout->connect();
}
void		Neb::window::window::i(int const & ni) {

	i_ = ni;
}





