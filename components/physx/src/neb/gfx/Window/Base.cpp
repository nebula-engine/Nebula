#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glu.h>

#include <map>

#include <gal/log/log.hpp>

#include <neb/core/util/debug.hpp>
#include <neb/core/core/scene/util/decl.hpp>
#include <neb/core/core/actor/base.hpp>
#include <neb/core/core/light/base.hpp>

#include <neb/gfx/free.hpp>

#include <neb/gfx/opengl/png.hpp>

#include <neb/gfx/app/glfw.hpp>
#include <neb/gfx/app/__gfx_glsl.hpp>

#include <neb/gfx/camera/view/Base.hh>
#include <neb/gfx/Context/Window.hpp>
#include <neb/gfx/environ/two.hpp>
#include <neb/gfx/environ/SceneDefault.hpp>
#include <neb/gfx/window/Base.hh>
#include <neb/gfx/window/util/Parent.hh>
#include <neb/gfx/util/log.hpp>
#include <neb/gfx/environ/two.hpp>
#include <neb/gfx/environ/three.hpp>



GLFWwindow* neb::gfx::window::base::first_window_ = NULL;

neb::gfx::window::base::base():
	x_(1200),
	y_(0),
	w_(600),
	h_(600),
	window_(NULL)
{
}
neb::gfx::window::base::~base() {
}
void			neb::gfx::window::base::init(parent_t * const & p)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
	
	if(p == NULL) return;

	setParent(p);
	
	// callback
	callback_.key_press_.F1_ = [this](int,int,int,int)->int {
		printScreen();
		return 1;
	};

	
	auto app = neb::gfx::app::glfw::global();

	if(!app->flag_.any(neb::core::app::util::flag::INIT_GLFW))
	{
		std::cout << "glfw not initializaed" << std::endl;
		return;
	}
	

	auto self = std::dynamic_pointer_cast<neb::gfx::window::base>(shared_from_this());
	
	if(window_)
	{
		return;
	}


	// create window
	//
	
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	window_ = glfwCreateWindow(
			w_,
			h_,
			title_.c_str(),
			NULL,
			first_window_
			);

	if(first_window_ == NULL) {
		first_window_ = window_;
	}

	if(window_ == NULL) {
		glfwTerminate();
		LOG(lg, neb::gfx::sl, critical) << "glfwCreateWindow failed";
		exit(EXIT_FAILURE);
	}

	glfwSetWindowPos(window_, x_, y_);

	glfwMakeContextCurrent(window_);

	glfwSetWindowPosCallback(
			window_,
			neb::gfx::app::glfw::static_window_pos_fun);
	glfwSetWindowSizeCallback(
			window_,
			neb::gfx::app::glfw::static_window_size_fun);
	glfwSetWindowCloseCallback(
			window_,
			neb::gfx::app::glfw::static_window_close_fun);
	glfwSetWindowRefreshCallback(
			window_,
			neb::gfx::app::glfw::static_window_refresh_fun);
	glfwSetKeyCallback(
			window_,
			neb::gfx::app::glfw::static_key_fun);
	glfwSetMouseButtonCallback(
			window_,
			neb::gfx::app::glfw::static_mouse_button_fun);
	glfwSetCharCallback(
			window_,
			neb::gfx::app::glfw::staticCharFun);

	// add window to app's window map
	app->windows_glfw_[window_] = self;


	//if(all(neb::app::base::option::SHADERS)) create_programs();


	app->init_glew();

	auto app2 = neb::gfx::app::__gfx_glsl::global().lock();

	app2->create_programs();







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



	checkerror("unknown");
}
void		neb::gfx::window::base::release() {
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;


	glfwDestroyWindow(window_);
}
void		neb::gfx::window::base::render() {
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	assert(window_ != NULL);
	glfwMakeContextCurrent(window_);

	/** @todo rendering multiple contexts in a window */

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	typedef neb::gfx::context::util::parent C;

	auto lamb = [] (C::map_type::pointer p) {
		auto context = std::dynamic_pointer_cast<neb::gfx::context::base>(p);
		assert(context);
		context->render();
	};

	C::map_.for_each(lamb);

	glFinish();
	glfwSwapBuffers(window_);

	// screen print every frame (use for video?)
	//save_png("test.png",w_,h_);
}
void neb::gfx::window::base::callback_window_refresh_fun(GLFWwindow*) {
}
void			neb::gfx::window::base::step(gal::etc::timestep const & ts) {
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	contexts::step(ts);

	if(glfwWindowShouldClose(window_))
	{
		getParent()->erase(_M_index);
		return;
	}

}
void neb::gfx::window::base::callback_window_size_fun(GLFWwindow* window, int w, int h) {
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	w_ = w;
	h_ = h;

	resize();

	callback_window_refresh_fun(window);
}
void neb::gfx::window::base::callback_window_pos_fun(GLFWwindow* window, int x, int y) {
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	x_ = x;
	y_ = y;

	callback_window_refresh_fun(window);
}
void		neb::gfx::window::base::callback_window_close_fun(GLFWwindow* window){
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

}
void		neb::gfx::window::base::callback_mouse_button_fun(GLFWwindow* window, int button, int action, int mods) {
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	auto self = std::dynamic_pointer_cast<neb::gfx::window::base>(shared_from_this());

	sig_.mouseButtonFun_(self, button, action, mods);
}
void			neb::gfx::window::base::callback_key_fun(
		GLFWwindow* window,
		int key,
		int scancode,
		int action,
		int mods)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	auto self = std::dynamic_pointer_cast<neb::gfx::window::base>(shared_from_this());

	if(action == GLFW_PRESS)
	{
		switch(key)
		{
			case GLFW_KEY_F1:
				if(callback_.key_press_.F1_) if(callback_.key_press_.F1_(key, scancode, action, mods)) return;
				break;
		}
	}

	sig_.keyFun_(self, key, scancode, action, mods);
}
void			neb::gfx::window::base::callbackCharFun(GLFWwindow* window, unsigned int codepoint)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	auto self = std::dynamic_pointer_cast<neb::gfx::window::base>(shared_from_this());

	sig_.charFun_(self, codepoint);
}
void			neb::gfx::window::base::resize()
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	glViewport(0, 0, w_, h_);

	typedef neb::gfx::context::util::parent C;

	auto lamb = [&] (C::map_type::pointer p) {
		auto context = std::dynamic_pointer_cast<neb::gfx::context::base>(p);
		assert(context);
		context->resize(w_, h_);
	};

	C::map_.for_each(lamb);

}
std::weak_ptr<neb::gfx::context::window>		neb::gfx::window::base::createContextTwo() {

	auto self = isWindowBase();
	assert(self);

	std::weak_ptr<neb::gfx::context::window> w;
	{
		auto context = createContextWindow().lock();
		//auto context(make_shared<>(self));
		//assert(context);
		//insert(context);

		auto environ = context->createEnvironTwo().lock();

		//context->init(this);

		w = context;
	}
	assert(!w.expired());
	return w;
}
std::weak_ptr<neb::gfx::context::window>		neb::gfx::window::base::createContextThree() {

	auto self = isWindowBase();
	assert(self);

	std::weak_ptr<neb::gfx::context::window> w;
	{
		auto context = createContextWindow().lock();
		//	auto context = std::make_shared<neb::gfx::context::window>(self);
		//	assert(context);
		//	insert(context);

		auto environ = context->createEnvironSceneDefault().lock();

		context->init(this);

		//assert(environ->view_);
		//environ->view_->connect(self);

		w = context;
	}
	assert(!w.expired());
	return w;
}
std::weak_ptr<neb::gfx::context::window>		neb::gfx::window::base::createContextNormalMap() {

	auto self = isWindowBase();
	assert(self);

	std::weak_ptr<neb::gfx::context::window> w;
	{
		auto context = createContextWindow().lock();
		//	auto context = std::make_shared<neb::gfx::context::window>(self);
		//	assert(context);
		//	insert(context);

		auto environ = context->createEnvironNormalMap().lock();

		context->init(this);

		//assert(environ->view_);
		//environ->view_->connect(self);

		w = context;
	}
	assert(!w.expired());
	return w;
}
void						neb::gfx::window::base::makeCurrent() {
	assert(window_ != NULL);
	glfwMakeContextCurrent(window_);
}
glm::vec2					neb::gfx::window::base::getCursorPosNDC()
{
	return glm::vec2();
}
void						neb::gfx::window::base::printScreen()
{

	if(screenBuffer_.capacity() < (w_ * h_ * 3u)) screenBuffer_.reserve(w_*h_*3);

	glReadPixels(
			0,
			0,
			w_,
			h_,
			GL_RGB,
			GL_UNSIGNED_BYTE,
			(GLvoid *)&screenBuffer_[0]
		    );
	
	
	
	// invert pixels (stolen from SOILs source code)
	/*
	for (int j = 0; j * 2 < h_; ++j) {
		int x = j * w_ * 3;
		int y = (h_ - 1 - j) * w_ * 3;
		for (int i = w_ * 3; i > 0; --i) {
			uint8_t tmp = screenBuffer_[x];
			screenBuffer_[x] = screenBuffer_[y];
			screenBuffer_[y] = tmp;
			++x;
			++y;
		}
	}
	*/

	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time (&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer,80,"screenshot_%Y-%m-%d_%H:%M:%S.png",timeinfo);

	save_png_libpng(buffer, &screenBuffer_[0], w_, h_);

}


