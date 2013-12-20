#include <stdio.h>
#include <stdlib.h>
#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <glfw3.h>

#include <glutpp/config.h>
#include <glutpp/master.h>
#include <glutpp/window.h>

namespace glutpp {
	master __master;
}
glutpp::master::master() {

	printf("%s\n", __PRETTY_FUNCTION__);

	glfwInit();

	glfwSetErrorCallback(static_error_fun);
}
glutpp::master::~master(){	printf("%s\n", __PRETTY_FUNCTION__);

}
std::shared_ptr<glutpp::window>		glutpp::master::get_window(GLFWwindow* window) {

	return windows_[window];

}
void	glutpp::master::static_error_fun(int error, char const * description) {
	
	printf("%s\n", description);
	exit(0);

}
void glutpp::master::static_window_pos_fun(GLFWwindow* window, int x,int y){
	__master.get_window(window)->callback_window_pos_fun(window,x,y);
}
void glutpp::master::static_window_size_fun(GLFWwindow* window, int w, int h){
	__master.get_window(window)->callback_window_size_fun(window,w,h);
}
void glutpp::master::static_window_close_fun(GLFWwindow* window){
	__master.get_window(window)->callback_window_close_fun(window);
}
void glutpp::master::static_window_refresh_fun(GLFWwindow* window){
	__master.get_window(window)->callback_window_refresh_fun(window);
}
void glutpp::master::static_mouse_button_fun(GLFWwindow* window, int button, int action, int mods){
	__master.get_window(window)->callback_mouse_button_fun(window, button, action, mods);
}
void glutpp::master::static_key_fun(GLFWwindow* window, int key, int scancode, int action, int mods){
	__master.get_window(window)->callback_key_fun(window, key, scancode, action, mods);
}
int	glutpp::master::reg(std::shared_ptr<glutpp::window> w) {

	printf("%s\n", __PRETTY_FUNCTION__);

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
	
	//if(all(glutpp::master::option::SHADERS)) create_programs();
	create_programs();
	
	return 0;
}
int	glutpp::master::create_programs() {

	printf("%s\n", __PRETTY_FUNCTION__);

	std::shared_ptr<glutpp::glsl::program> p;

	// text
	{
		p.reset(new glutpp::glsl::program);
		p->init();

		p->add_shader(GLUTPP_SHADER_DIR"/v130/text/vs.glsl", GL_VERTEX_SHADER);
		p->add_shader(GLUTPP_SHADER_DIR"/v130/text/fs.glsl", GL_FRAGMENT_SHADER);

		p->compile();

		p->add_attrib(glutpp::attrib_name::e::COOR, "coord", 0);

		p->add_uniform(glutpp::uniform_name::e::COLOR,"font_color");
		p->add_uniform(glutpp::uniform_name::e::TEX,"tex");
		
		p->locate();

		programs_[glutpp::program_name::TEXT] = p;
	}
	// quad




	// light
	{
		p.reset(new glutpp::glsl::program);
		p->init();

		p->add_shader(GLUTPP_SHADER_DIR"/v130/light/vs.glsl", GL_VERTEX_SHADER);
		p->add_shader(GLUTPP_SHADER_DIR"/v130/light/fs.glsl", GL_FRAGMENT_SHADER);

		p->compile();

		//p->add_uniform(glutpp::uniform_name::e::IMAGE, "image");

		p->add_attrib(glutpp::attrib_name::e::POSITION, "position", 1);
		p->add_attrib(glutpp::attrib_name::e::NORMAL, "normal", 2);
		//p->add_attrib(glutpp::attrib_name::e::TEXCOOR, "texcoor");

		p->add_uniform(glutpp::uniform_name::e::LIGHT_COUNT,"light_count");
		p->add_uniform(glutpp::uniform_name::e::MODEL,"model");
		p->add_uniform(glutpp::uniform_name::e::VIEW,"view");
		p->add_uniform(glutpp::uniform_name::e::PROJ,"proj");

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

	
		p->locate();

		programs_[glutpp::program_name::LIGHT] = p;
	}
}
std::shared_ptr<glutpp::glsl::program>	glutpp::master::use_program(glutpp::program_name::e name){
	auto p = get_program(name);

	p->use();

	current_ = p;

	return p;
}
std::shared_ptr<glutpp::glsl::program>	glutpp::master::current_program(){
	assert(current_);

	return current_;
}
std::shared_ptr<glutpp::glsl::program>	glutpp::master::get_program(glutpp::program_name::e name){
	auto it = programs_.find(name);

	if(it == programs_.end())
	{
		printf("program not found\n");
		exit(0);
	}

	auto p = (*it).second;

	assert(p);

	return p;
}


