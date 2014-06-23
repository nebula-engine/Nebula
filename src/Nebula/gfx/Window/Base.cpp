#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glu.h>

#include <map>

//#include <GL/glew.h>
//#include <GL/glut.h>

#include <Galaxy-Log/log.hpp>

#include <Nebula/core/scene/Util/Types.hh>

#include <Nebula/free.hh>
#include <Nebula/core/actor/Base.hh>
#include <Nebula/app/Base.hh>
#include <Nebula/gfx/Context/Base.hh>
#include <Nebula/core/light/Base.hh>
#include <Nebula/gfx/window/Base.hh>
#include <Nebula/gfx/window/util/Parent.hh>


neb::gfx::window::base::base():
	x_(0),
	y_(0),
	w_(600),
	h_(600)
{
}
neb::gfx::window::base::base(sp::shared_ptr<neb::gfx::window::util::parent> parent):
	parent_(parent),
	x_(0),
	y_(0),
	w_(600),
	h_(600)
{
}
neb::gfx::window::base::~base() {
}
void neb::gfx::window::base::init() {
	neb::std::shared::init();
	
	BOOST_LOG_CHANNEL_SEV(lg, "neb", debug) << __PRETTY_FUNCTION__;

	auto app = neb::app::base::global();
	assert(app);
	
	assert(app->flag_.any(neb::app::util::flag::INIT_GLFW));

	self_ = sp::dynamic_pointer_cast<neb::gfx::window::base>(shared_from_this());
	
	// create window
	window_ = glfwCreateWindow(
			w_,
			h_,
			title_.c_str(),
			NULL,
			NULL);

	if(window_ == NULL) {
		glfwTerminate();
		BOOST_LOG_CHANNEL_SEV(lg, "neb gfx", critical) << "glfwCreateWindow failed";
		exit(EXIT_FAILURE);
	}



	glfwMakeContextCurrent(window_);

	glfwSetWindowPosCallback(
			window_,
			neb::app::base::static_window_pos_fun);
	glfwSetWindowSizeCallback(
			window_,
			neb::app::base::static_window_size_fun);
	glfwSetWindowCloseCallback(
			window_,
			neb::app::base::static_window_close_fun);
	glfwSetWindowRefreshCallback(
			window_,
			neb::app::base::static_window_refresh_fun);
	glfwSetKeyCallback(
			window_,
			neb::app::base::static_key_fun);
	glfwSetMouseButtonCallback(
			window_,
			neb::app::base::static_mouse_button_fun);

	// add window to app's window map
	app->windows_glfw_[window_] = self_;
	
	
	//if(all(neb::app::base::option::SHADERS)) create_programs();
	app->init_glew();
	app->create_programs();

	





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
	glfwDestroyWindow(window_);
}
void		neb::gfx::window::base::render() {

	glfwMakeContextCurrent(window_);

	/** @todo rendering multiple contexts in a window */

	
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	
	
	typedef neb::gfx::context::util::parent C;

	C::map_.for_each<0>([] (C::map_type::iterator<0> it) {
			auto context = sp::dynamic_pointer_cast<neb::gfx::context::base>(it->ptr_);
			assert(context);
			context->render();
			});

	glFinish();
	glfwSwapBuffers(window_);
}
void neb::gfx::window::base::callback_window_refresh_fun(GLFWwindow*) {
}
void			neb::gfx::window::base::step(gal::std::timestep const & ts) {
	//GLUTPP_DEBUG_1_FUNCTION;

	BOOST_LOG_CHANNEL_SEV(lg, "neb gfx window", debug) << __PRETTY_FUNCTION__;


	neb::gfx::context::util::parent::step(ts);


	if(glfwWindowShouldClose(window_)) {
		parent_->erase(i_);
		return;
	}
	
	
	
	/** @todo wtf is this doing here?? */
	render();
}
void neb::gfx::window::base::callback_window_size_fun(GLFWwindow* window, int w, int h) {
	GLUTPP_DEBUG_0_FUNCTION;

	w_ = w;
	h_ = h;

	resize();

	callback_window_refresh_fun(window);
}
void neb::gfx::window::base::callback_window_pos_fun(GLFWwindow* window, int x, int y) {
	GLUTPP_DEBUG_0_FUNCTION;

	x_ = x;
	y_ = y;

	callback_window_refresh_fun(window);
}
void neb::gfx::window::base::callback_window_close_fun(GLFWwindow* window){
	GLUTPP_DEBUG_0_FUNCTION;

}
void neb::gfx::window::base::callback_mouse_button_fun(GLFWwindow* window, int button, int action, int mods) {
	GLUTPP_DEBUG_0_FUNCTION;
	
	sig_.mouse_button_fun_(self_, button, action, mods);
}
void neb::gfx::window::base::callback_key_fun(GLFWwindow* window, int key, int scancode, int action, int mods) {
	GLUTPP_DEBUG_0_FUNCTION;
	
	sig_.key_fun_(self_, key, scancode, action, mods);

}
void neb::gfx::window::base::resize() {


	glViewport(0, 0, w_, h_);

	typedef neb::gfx::context::util::parent C;

	C::map_.for_each<0>([&] (C::map_type::iterator<0> it) {
			auto context = sp::dynamic_pointer_cast<neb::gfx::context::base>(it->ptr_);
			assert(context);
			context->resize(w_, h_);
			});

}




