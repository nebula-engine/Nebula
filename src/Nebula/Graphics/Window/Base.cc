#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glu.h>

#include <map>

//#include <GL/glew.h>
//#include <GL/glut.h>

#include <Nebula/Scene/Util/Types.hh>

#include <Nebula/free.hh>
#include <Nebula/Actor/Base.hh>

#include <Nebula/Graphics/Context/Base.hh>
#include <Nebula/Graphics/Light/Base.hh>
#include <Nebula/Graphics/Window/Base.hh>
#include <Nebula/Graphics/Window/Util/Parent.hh>

/** @todo get rid of my unique ptr class. Just use private member and be careful not to pass around shared ptrs to things */

Neb::Graphics::Window::Base::Base() {
}
Neb::Graphics::Window::Base::Base(Neb::Graphics::Window::Util::Parent_s parent) {
	//GLUTPP_DEBUG_0_FUNCTION;
}
Neb::Graphics::Window::Base::~Base() {
	//GLUTPP_DEBUG_0_FUNCTION;

	glfwDestroyWindow(window_);
}
void Neb::Graphics::Window::Base::init() {
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


	//renderable_.reset(new Neb::renderable(shared_from_this()));
	//renderable_->init(shared_from_this());

	checkerror("unknown");
}
void Neb::Graphics::Window::Base::render(double time) {
	GLUTPP_DEBUG_1_FUNCTION;

	glfwMakeContextCurrent(window_);
	
	/** @todo rendering multiple contexts in a window */

	typedef Neb::Util::Parent<Neb::Graphics::Context::Base> C;

	C::map_.for_each([&] (C::map_type::const_iterator it) {
		it->second.ptr_->render(time, isWindowBase());
	});

	glFinish();
	glfwSwapBuffers(window_);
}
void Neb::Graphics::Window::Base::callback_window_refresh_fun(GLFWwindow*) {
}
void			Neb::Graphics::Window::Base::step(double const & time, double const & dt) {
	//GLUTPP_DEBUG_1_FUNCTION;

	if(glfwWindowShouldClose(window_)) {
		parent_->release(i_);
		return;
	}
	
	render(time);
}
void Neb::Graphics::Window::Base::callback_window_size_fun(GLFWwindow* window, int w, int h) {
	GLUTPP_DEBUG_0_FUNCTION;

	w_ = w;
	h_ = h;

	resize();

	callback_window_refresh_fun(window);
}
void Neb::Graphics::Window::Base::callback_window_pos_fun(GLFWwindow* window, int x, int y) {
	GLUTPP_DEBUG_0_FUNCTION;

	x_ = x;
	y_ = y;

	callback_window_refresh_fun(window);
}
void Neb::Graphics::Window::Base::callback_window_close_fun(GLFWwindow* window){
	GLUTPP_DEBUG_0_FUNCTION;

}
void Neb::Graphics::Window::Base::callback_mouse_button_fun(GLFWwindow* window, int button, int action, int mods) {
	GLUTPP_DEBUG_0_FUNCTION;
	
	sig_.mouse_button_fun_(button, action, mods);
}
void Neb::Graphics::Window::Base::callback_key_fun(GLFWwindow* window, int key, int scancode, int action, int mods) {
	GLUTPP_DEBUG_0_FUNCTION;
	
	sig_.key_fun_(key, scancode, action, mods);
	
}
void Neb::Graphics::Window::Base::resize() {

	glViewport(0, 0, w_, h_);
	
	typedef Neb::Util::Parent<Neb::Graphics::Context::Base> C;

	C::map_.for_each([&] (C::map_type::const_iterator it) {
		it->second.ptr_->resize(w_, h_);
	});
	
}




