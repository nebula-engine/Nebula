#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <GLFW/glfw3.h>
#include <GL/glu.h>

#include <map>

//#include <GL/glew.h>
//#include <GL/glut.h>

#include <math/color.h>

#include <glutpp/free.h>
#include <glutpp/window/desc.h>
#include <glutpp/window/window.h>
#include <glutpp/actor/actor.h>
#include <glutpp/light/light.h>
#include <glutpp/renderable.h>

template <typename... Args>
void	fatal_error(char const * c, Args ...args)
{
	char fmt[128];
	strcat(fmt, "error: ");
	strcat(fmt, c);
	strcat(fmt, "\n");
	printf(fmt, args...);
	exit(0);
}
void	fatal_error(char const * c)
{
	char fmt[128];
	strcat(fmt, "error: ");
	strcat(fmt, c);
	strcat(fmt, "\n");
	printf("%s\n",c);
	exit(0);
}
void	check_error()
{
	GLenum errCode = glGetError();
	if (errCode != GL_NO_ERROR)
	{
		//printf("%s\n",gluErrorString(errCode));
	}
}
void	checkerror(char const * msg) {

	GLenum err = glGetError();
	if(err != GL_NO_ERROR)
	{
		unsigned char const * str = gluErrorString(err);
		printf("%s: %s\n",msg,str);
		exit(0);
	}
}



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
void	glutpp::window::window::init() {
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
void	glutpp::window::window::render(double time) {
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
void	glutpp::window::window::callback_window_refresh_fun(GLFWwindow*) {
}
int glutpp::window::window::step(double time) {
	GLUTPP_DEBUG_1_FUNCTION;

	if(glfwWindowShouldClose(window_))
	{
		printf("window should close\n");
		return 1;
	}

	render(time);

	return 0;
}
void	glutpp::window::window::callback_window_size_fun(GLFWwindow* window, int w, int h) {
	GLUTPP_DEBUG_0_FUNCTION;

	raw_.w_ = w;
	raw_.h_ = h;

	resize();

	callback_window_refresh_fun(window);
}
void	glutpp::window::window::callback_window_pos_fun(GLFWwindow* window, int x, int y) {
	GLUTPP_DEBUG_0_FUNCTION;

	raw_.x_ = x;
	raw_.y_ = y;

	callback_window_refresh_fun(window);
}
void	glutpp::window::window::callback_window_close_fun(GLFWwindow* window){
	GLUTPP_DEBUG_0_FUNCTION;

}
void	glutpp::window::window::callback_mouse_button_fun(GLFWwindow* window, int button, int action, int mods){
	GLUTPP_DEBUG_0_FUNCTION;

	sig_.mouse_button_fun_(button, action, mods);
}
void	glutpp::window::window::callback_key_fun(GLFWwindow* window, int key, int scancode, int action, int mods){
	GLUTPP_DEBUG_0_FUNCTION;

	sig_.key_fun_(key, scancode, action, mods);

	switch(key)
	{
		/*	case 's':
			toggle(SHADOW);
			break;
			case 'o':
			toggle(ORTHO);
			break;
			case 'r':
			toggle(REFLECT);
			break;*/
		case GLFW_KEY_ESCAPE:
			//glfwSetWindowShouldClose(window_, 1);
			break;
	}
}
void	glutpp::window::window::resize() {

	glViewport(0, 0, raw_.w_, raw_.h_);

	renderable_->resize(raw_.w_, raw_.h_);
}

int	glutpp::window::window::set_layout(std::shared_ptr<glutpp::gui::layout> layout) {

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





