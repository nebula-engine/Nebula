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
#include <glutpp/window.h>
#include <glutpp/actor.h>
#include <glutpp/light.h>
//#include <glutpp/shader.h>
//#include <glutpp/program.h>
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


glutpp::window::window(int w, int h, int x, int y, const char * title):
	w_(w), h_(h), x_(x), y_(y),
	title_(title)
{
	printf("%s\n",__PRETTY_FUNCTION__);
	
	printf(GLUTPP_INSTALL_DIR);
	printf("\n");
	
	
	__master.reg(this);
}
glutpp::window::~window()
{
	printf("%s\n",__PRETTY_FUNCTION__);

	glfwDestroyWindow(window_);
}
void	glutpp::window::init() {
	printf("%s\n",__PRETTY_FUNCTION__);
	
	printf("%s\n",glGetString(GL_SHADING_LANGUAGE_VERSION));
	
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

	
	renderable_.reset(new glutpp::renderable);
	renderable_->init(shared_from_this());
	
	checkerror("unknown");
}
void	glutpp::window::render(double time)
{
	if(renderable_) renderable_->render(time);

	glFinish();
	glfwSwapBuffers(window_);
}
void	glutpp::window::callback_window_refresh_fun(GLFWwindow*)
{
}
void	glutpp::window::step(double)
{
}
void	glutpp::window::loop()
{
	double time;
	
	resize(w_,h_);
	
	while (!glfwWindowShouldClose(window_))
	{
		time = glfwGetTime();
		
		step(time);
		
		render(time);
		
		glfwSwapBuffers(window_);
		glfwPollEvents();
	}
}
void	glutpp::window::callback_window_size_fun(GLFWwindow* window, int w, int h)
{
	w_ = w;
	h_ = h;
	
	resize(w,h);

	callback_window_refresh_fun(window);
}
void	glutpp::window::callback_window_pos_fun(GLFWwindow* window, int x, int y)
{
	x_ = x;
	y_ = y;

	callback_window_refresh_fun(window);
}
void	glutpp::window::callback_window_close_fun(GLFWwindow* window)
{
	printf("%s\n", __PRETTY_FUNCTION__);
	
	
}
void	glutpp::window::callback_mouse_button_fun(GLFWwindow* window, int button, int action, int mods)
{
	printf("%s\n", __PRETTY_FUNCTION__);
	
	sig_.mouse_button_fun_(button, action, mods);
}
void	glutpp::window::callback_key_fun(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	printf("%s\n", __PRETTY_FUNCTION__);

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
			glfwSetWindowShouldClose(window_, 1);
			break;
	}
}
void	glutpp::window::resize(int w,int h) {

	glViewport(0, 0, w_, h_);

	renderable_->resize(w,h);
}
int	glutpp::window::prepare() {

	printf("%s\n", __PRETTY_FUNCTION__);

	if(renderable_)
	{
		if(renderable_->scene_)
		{
			renderable_->scene_->prepare();
		}
	}
}
int	glutpp::window::set_scene(std::shared_ptr<scene> scene) {

	printf("%s\n", __PRETTY_FUNCTION__);

	assert(scene);
	assert(renderable_);
	
	renderable_->scene_ = scene;
	
	scene->renderable_ = renderable_;
}
int	glutpp::window::set_layout(std::shared_ptr<glutpp::gui::layout> layout) {

	printf("%s\n", __PRETTY_FUNCTION__);
	
	assert(layout);
	assert(renderable_);
	
	renderable_->layout_ = layout;
	
	layout->init(renderable_);
	layout->connect();
}
void	checkerror(char const * msg)
{
	GLenum err = glGetError();
	if(err != GL_NO_ERROR)
	{
		unsigned char const * str = gluErrorString(err);
		printf("%s: %s\n",msg,str);
		exit(0);
	}
}





