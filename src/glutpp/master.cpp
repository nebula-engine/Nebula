#include <stdio.h>
#include <stdlib.h>
#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <glfw3.h>

#include <glutpp/master.h>
#include <glutpp/window.h>

namespace glutpp
{
	master __master;
}
glutpp::master::master()
{
	// Create dummy variables 

	const char * dummy_argv[1];
	dummy_argv[0] = "run";
	int dummy_argc = 1;

	// Initialize GLUT


	
	glfwInit();// 
}
glutpp::master::~master()
{

}
glutpp::window*	glutpp::master::get_window(GLFWwindow* window)
{
	return windows_[window];
}
void glutpp::master::static_window_pos_fun(GLFWwindow* window, int x,int y)
{
	__master.get_window(window)->callback_window_pos_fun(window,x,y);
}
void glutpp::master::static_window_size_fun(GLFWwindow* window, int w, int h)
{
	__master.get_window(window)->callback_window_size_fun(window,w,h);
}
void glutpp::master::static_window_close_fun(GLFWwindow* window)
{
	__master.get_window(window)->callback_window_close_fun(window);
}
void glutpp::master::static_window_refresh_fun(GLFWwindow* window)
{
	__master.get_window(window)->callback_window_refresh_fun(window);
}
void glutpp::master::static_mouse_button_fun(GLFWwindow* window, int button, int action, int mods)
{
	__master.get_window(window)->callback_mouse_button_fun(window, button, action, mods);
}
void glutpp::master::static_key_fun(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	__master.get_window(window)->callback_key_fun(window, key, scancode, action, mods);
}
/*
   void glutpp::master::static_window_refresh_fun(GLFWwindow* window)
   {
   __master.get_window(window)->CallBackDisplayFunc();
   }
 */
/*
   void glutpp::master::CallBackIdleFunc(void)
   {	
   if(currentIdleWindow_ == NULL) return;

   glutSetWindow(currentIdleWindow);
   viewPorts[currentIdleWindow]->CallBackIdleFunc();

   }*//*
	 void glutpp::master::CallBackKeyboardFunc(unsigned char key, int x, int y)
	 {
	 int windowID = glutGetWindow();
	 viewPorts[windowID]->CallBackKeyboardFunc(key, x, y);
	 }
	 void glutpp::master::CallBackKeyboardUpFunc(unsigned char key, int x, int y)
	 {
	 int windowID = glutGetWindow();
	 viewPorts[windowID]->CallBackKeyboardUpFunc(key, x, y);
	 }
	 void glutpp::master::CallBackMotionFunc(int x, int y)
	 {
	 int windowID = glutGetWindow();
	 viewPorts[windowID]->CallBackMotionFunc(x, y);
	 }
	 void glutpp::master::CallBackMouseFunc(int button, int state, int x, int y)
	 {
	 int windowID = glutGetWindow();
	 viewPorts[windowID]->CallBackMouseFunc(button, state, x, y);
	 }
	 void glutpp::master::CallBackPassiveMotionFunc(int x, int y)
	 {
	 int windowID = glutGetWindow();
	 viewPorts[windowID]->CallBackPassiveMotionFunc(x, y);
	 }
	 void glutpp::master::CallBackReshapeFunc(int w, int h)
	 {
	 int windowID = glutGetWindow();
	 viewPorts[windowID]->CallBackReshapeFunc(w, h);
	 }
	 void glutpp::master::CallBackSpecialFunc(int key, int x, int y)
	 {
	 int windowID = glutGetWindow();
	 viewPorts[windowID]->CallBackSpecialFunc(key, x, y);
	 }   
	 void glutpp::master::CallBackVisibilityFunc(int visible)
	 {
	 int windowID = glutGetWindow();
	 viewPorts[windowID]->CallBackVisibilityFunc(visible);
	 }
	 void glutpp::master::static_CallBackDisplayFunc(void)
	 {
	 GLFWwindow* window = glfwGetCurrentContext();
	 if(window == NULL) return;

	 __master.windows_[window]->CallBackDisplayFunc();
	 }
	 void glutpp::master::static_CallBackIdleFunc(void)
	 {	
	 if(currentIdleWindow_ == NULL) return;

	 glutSetWindow(currentIdleWindow);
	 viewPorts[currentIdleWindow]->CallBackIdleFunc();

	 }
	 void glutpp::master::static_key_fun(GLFWwindow* window, int key, int scancode, int action, int mods)
	 {
	 __master.(key,scancode,);
	 }
	 void glutpp::master::static_CallBackKeyboardUpFunc(unsigned char key, int x, int y)
	 {
	 __master.
	 int windowID = glutGetWindow();
	 viewPorts[windowID]->CallBackKeyboardUpFunc(key, x, y);
	 }*/
/*
   void glutpp::master::static_CallBackMotionFunc(int x, int y)
   {
   __master.
   int windowID = glutGetWindow();
   viewPorts[windowID]->CallBackMotionFunc(x, y);
   }
   void glutpp::master::static_CallBackMouseFunc(int button, int state, int x, int y)
   {
   __master.
   int windowID = glutGetWindow();
   viewPorts[windowID]->CallBackMouseFunc(button, state, x, y);
   }
   void glutpp::master::static_CallBackPassiveMotionFunc(int x, int y)
   {
   __master.
   int windowID = glutGetWindow();
   viewPorts[windowID]->CallBackPassiveMotionFunc(x, y);
   }
   void glutpp::master::static_CallBackReshapeFunc(int w, int h)
   {
   __master.
   int windowID = glutGetWindow();
   viewPorts[windowID]->CallBackReshapeFunc(w, h);
   }
   void glutpp::master::static_CallBackSpecialFunc(int key, int x, int y)
   {
   __master.
   int windowID = glutGetWindow();
   viewPorts[windowID]->CallBackSpecialFunc(key, x, y);
   }   
   void glutpp::master::static_CallBackVisibilityFunc(int visible)
   {
   __master.
   int windowID = glutGetWindow();
   viewPorts[windowID]->CallBackVisibilityFunc(visible);
   }
 */
void	glutpp::master::reg(glutpp::window* w)
{
	GLFWwindow* g = glfwCreateWindow(w->w_, w->h_, w->title_, NULL, NULL);

	if(g == NULL)
	{
		glfwTerminate();
		printf("error\n");
		exit(EXIT_FAILURE);
	}
	
	w->window_ = g;
	
	windows_[g] = w;
	
	glfwMakeContextCurrent(g);
	
	glfwSetWindowPosCallback(g, static_window_pos_fun);
	glfwSetWindowSizeCallback(g, static_window_size_fun);
	glfwSetWindowCloseCallback(g, static_window_close_fun);
	glfwSetWindowRefreshCallback(g, static_window_refresh_fun);

	glfwSetKeyCallback(g, static_key_fun);
	glfwSetMouseButtonCallback(g, static_mouse_button_fun);

	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		printf("GLEW: %s\n", glewGetErrorString(err));
		exit(EXIT_FAILURE);
	}

	// font
	//FT_Library ft;
	if(FT_Init_FreeType(&ft_))
	{
		printf("could not find freetype library\n");
		exit(0);
	}
}
int	glutpp::master::create_programs()
{
	std::shared_ptr<glutpp::glsl::program> p;
	
	// text
	p.reset(new glutpp::glsl::program);
	p->init();
	
	p->add_shader(GLUTPP_SHADER_DIR"/text/vs.glsl", GL_VERTEX_SHADER);
	p->add_shader(GLUTPP_SHADER_DIR"/text/fs.glsl", GL_FRAGMENT_SHADER);
	
	p->compile();
	
	programs_[glutpp::program_name::TEXT] = p;
	
	// quad
	
	// light
	p.reset(new glutpp::glsl::program);
	p->init();
	
	p->add_shader(GLUTPP_SHADER_DIR"/text/vs.glsl", GL_VERTEX_SHADER);
	p->add_shader(GLUTPP_SHADER_DIR"/text/fs.glsl", GL_FRAGMENT_SHADER);
	
	p->compile();
	
	//p->add_uniform(glutpp::uniform_name::e::IMAGE, "image");
	
	p->add_attrib(glutpp::attrib_name::e::POSITION, "position");
	p->add_attrib(glutpp::attrib_name::e::NORMAL, "normal");
	p->add_attrib(glutpp::attrib_name::e::TEXCOOR, "texcoor");

	
	p->add_uniform(glutpp::uniform_name::e::FRONT_AMBIENT,"front.ambient");
	p->add_uniform(glutpp::uniform_name::e::FRONT_DIFFUSE,"front.diffuse");
	p->add_uniform(glutpp::uniform_name::e::FRONT_SPECULAR,"front.specular");
	p->add_uniform(glutpp::uniform_name::e::FRONT_EMISSION,"front.emission");
	p->add_uniform(glutpp::uniform_name::e::FRONT_SHININESS,"front.shininess");


	p->add_uniform(glutpp::uniform_name::e::LIGHT_POSITION, "lights", "position");
	p->add_uniform(glutpp::uniform_name::e::LIGHT_AMBIENT, "lights","ambient");
	p->add_uniform(glutpp::uniform_name::e::LIGHT_DIFFUSE, "lights","diffuse");
	p->add_uniform(glutpp::uniform_name::e::LIGHT_SPECULAR, "lights","specular");
	p->add_uniform(glutpp::uniform_name::e::LIGHT_SPOT_DIRECTION, "lights","spot_direction");
	p->add_uniform(glutpp::uniform_name::e::LIGHT_SPOT_CUTOFF, "lights","spot_cutoff");
	p->add_uniform(glutpp::uniform_name::e::LIGHT_SPOT_EXPONENT, "lights","spot_exponent");
	p->add_uniform(glutpp::uniform_name::e::LIGHT_SPOT_LIGHT_COS_CUTOFF, "lights","spot_light_cos_cutoff");
	p->add_uniform(glutpp::uniform_name::e::LIGHT_ATTEN_CONST, "lights","atten_const");
	p->add_uniform(glutpp::uniform_name::e::LIGHT_ATTEN_LINEAR, "lights","atten_linear");
	p->add_uniform(glutpp::uniform_name::e::LIGHT_ATTEN_QUAD, "lights","atten_quad");



	programs_[glutpp::program_name::TEXT] = p;

}
/*
   void glutpp::master::CallGlutMainLoop(void)
   {
   glutMainLoop();
   }

   void glutpp::master::DisableIdleFunction(void)
   {
   idleFunctionEnabled = 0;
   }
   void glutpp::master::EnableIdleFunction(void)
   {
   idleFunctionEnabled = 1;
   }
   int glutpp::master::IdleFunctionEnabled(void)
   {
// Is idle function enabled?

return(idleFunctionEnabled);
}
int glutpp::master::IdleSetToCurrentWindow(void)
{
// Is current idle window same as current window?

return( currentIdleWindow == glutGetWindow() );
}
void glutpp::master::SetIdleToCurrentWindow(void)
{
currentIdleWindow = glutGetWindow();
}

namespace glutpp
{
master __master;
}

 */
