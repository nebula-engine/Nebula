#include <stdio.h>
#include <stdlib.h>
#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <glfw3.h>

#include <gru/config.hpp>
#include <gru/master.hpp>
#include <gru/window/desc.hpp>
#include <gru/window/window.hpp>

glutpp::window::window_w	glutpp::master::window_main_;// = glutpp::window::window_s;
glutpp::master_s		glutpp::master::g_master_;

glutpp::master::master() {
	GLUTPP_DEBUG_0_FUNCTION;

	glfwInit();

	glfwSetErrorCallback(static_error_fun);
}
glutpp::master::~master() {
	GLUTPP_DEBUG_0_FUNCTION;
}
glutpp::master_s glutpp::master::Global() {
	assert(g_master_);
	return g_master_;
}
void glutpp::master::Global(glutpp::master_s m) {
	assert(m);
	g_master_ = m;
}
glutpp::window::window_s glutpp::master::Main_Window() {
	glutpp::window::window_s w;
	
	if(!window_main_.expired())
	{
		w = window_main_.lock();
		return w;
	}

	return w;
}
void glutpp::master::Main_Window(glutpp::window::window_s w) {
	assert(w);
	window_main_ = w;
}
unsigned int glutpp::master::master::f() {
	return flag_;
}
void glutpp::master::master::f(unsigned int flag) {
	flag_ = flag;
}
glutpp::window::window_s glutpp::master::get_window(GLFWwindow* window) {
	auto w = windows_[window];

	if(w.expired()) {
		return glutpp::window::window_s();
	}
	else {
		return w.lock();
	}
}
void glutpp::master::static_error_fun(int error, char const * description) {
	printf("%s\n", description);
	exit(0);
}
void glutpp::master::static_window_pos_fun(GLFWwindow* window, int x, int y){
	GLUTPP_DEBUG_0_FUNCTION;

	auto w = master::Global()->get_window(window);
	assert(w);
	if(w) w->callback_window_pos_fun(window,x,y);
}
void glutpp::master::static_window_size_fun(GLFWwindow* window, int w, int h){
	GLUTPP_DEBUG_0_FUNCTION;

	auto wnd = master::Global()->get_window(window);
	assert(w);
	if(wnd) wnd->callback_window_size_fun(window,w,h);
}
void glutpp::master::static_window_close_fun(GLFWwindow* window){
	GLUTPP_DEBUG_0_FUNCTION;
	
	auto w = master::Global()->get_window(window);
	assert(w);
	if(w) w->callback_window_close_fun(window);
}
void glutpp::master::static_window_refresh_fun(GLFWwindow* window) {
	GLUTPP_DEBUG_0_FUNCTION;

	auto w = master::Global()->get_window(window);
	assert(w);
	if(w) w->callback_window_refresh_fun(window);
}
void glutpp::master::static_mouse_button_fun(GLFWwindow* window, int button, int action, int mods){
	GLUTPP_DEBUG_0_FUNCTION;
	
	auto wm = Global()->Main_Window();
	
	if(wm) {
		wm = window_main_.lock();
		wm->callback_mouse_button_fun(window, button, action, mods);
	} else {
		fprintf(stderr, "main window not set %p\n", wm.get());
		abort();
	}
}
void glutpp::master::static_key_fun(GLFWwindow* window, int key, int scancode, int action, int mods){
	GLUTPP_DEBUG_0_FUNCTION;

	auto wm = Global()->Main_Window();
	
	if(wm) {
		wm = window_main_.lock();
		wm->callback_key_fun(window, key, scancode, action, mods);
	} else {
		fprintf(stderr, "main window not set %p\n", wm.get());
		abort();
	}
}
int glutpp::master::reg(glutpp::window::window_s w) {
	GLUTPP_DEBUG_0_FUNCTION;

	GLFWwindow* g = glfwCreateWindow(
			w->raw_.w_,
			w->raw_.h_,
			w->raw_.title_,
			NULL,
			NULL);

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
char const * shaderTypeString(GLenum type) {
	std::map<GLenum,char const *> m;

	m[GL_FLOAT]		="float";
	m[GL_FLOAT_VEC2]	="vec2";
	m[GL_FLOAT_VEC3]	="vec3";
	m[GL_FLOAT_VEC4]	="vec4";
	m[GL_DOUBLE]		="double";
	m[GL_DOUBLE_VEC2]	="dvec2";
	m[GL_DOUBLE_VEC3]	="dvec3";
	m[GL_DOUBLE_VEC4] 	="dvec4";
	/*
	   GL_INT 	int
	   GL_INT_VEC2 	ivec2​
	   GL_INT_VEC3 	ivec3​
	   GL_INT_VEC4 	ivec4​
	   GL_UNSIGNED_INT 	unsigned int​
	   GL_UNSIGNED_INT_VEC2 	uvec2​
	   GL_UNSIGNED_INT_VEC3 	uvec3​
	   GL_UNSIGNED_INT_VEC4 	uvec4​
	   GL_BOOL 	bool
	   GL_BOOL_VEC2 	bvec2​
	   GL_BOOL_VEC3 	bvec3​
	   GL_BOOL_VEC4 	bvec4​
	   GL_FLOAT_MAT2 	mat2​
	   GL_FLOAT_MAT3 	mat3​
	   GL_FLOAT_MAT4 	mat4​
	   GL_FLOAT_MAT2x3 	mat2x3
	   GL_FLOAT_MAT2x4 	mat2x4​
	   GL_FLOAT_MAT3x2 	mat3x2​
	   GL_FLOAT_MAT3x4 	mat3x4​
	   GL_FLOAT_MAT4x2 	mat4x2​
	   GL_FLOAT_MAT4x3 	mat4x3​
	   GL_DOUBLE_MAT2 	dmat2​
	   GL_DOUBLE_MAT3 	dmat3​
	   GL_DOUBLE_MAT4 	dmat4​
	   GL_DOUBLE_MAT2x3 	dmat2x3​
	   GL_DOUBLE_MAT2x4 	dmat2x4​
	   GL_DOUBLE_MAT3x2 	dmat3x2​
	   GL_DOUBLE_MAT3x4 	dmat3x4​
	   GL_DOUBLE_MAT4x2 	dmat4x2​
	   GL_DOUBLE_MAT4x3 	dmat4x3​
	   GL_SAMPLER_1D 	sampler1D​
	   GL_SAMPLER_2D 	sampler2D​
	   GL_SAMPLER_3D 	sampler3D​
	   GL_SAMPLER_CUBE 	samplerCube​
	   GL_SAMPLER_1D_SHADOW 	sampler1DShadow​
	   GL_SAMPLER_2D_SHADOW 	sampler2DShadow​
	   GL_SAMPLER_1D_ARRAY 	sampler1DArray​
	   GL_SAMPLER_2D_ARRAY 	sampler2DArray​
	   GL_SAMPLER_1D_ARRAY_SHADOW 	sampler1DArrayShadow​
	   GL_SAMPLER_2D_ARRAY_SHADOW 	sampler2DArrayShadow​
	   GL_SAMPLER_2D_MULTISAMPLE 	sampler2DMS​
	   GL_SAMPLER_2D_MULTISAMPLE_ARRAY 	sampler2DMSArray​
	   GL_SAMPLER_CUBE_SHADOW 	samplerCubeShadow​
	   GL_SAMPLER_BUFFER 	samplerBuffer​
	   GL_SAMPLER_2D_RECT 	sampler2DRect​
	   GL_SAMPLER_2D_RECT_SHADOW 	sampler2DRectShadow​
	   GL_INT_SAMPLER_1D 	isampler1D​
	   GL_INT_SAMPLER_2D 	isampler2D​
	   GL_INT_SAMPLER_3D 	isampler3D​
	   GL_INT_SAMPLER_CUBE 	isamplerCube​
	   GL_INT_SAMPLER_1D_ARRAY 	isampler1DArray​
	   GL_INT_SAMPLER_2D_ARRAY 	isampler2DArray​
	   GL_INT_SAMPLER_2D_MULTISAMPLE 	isampler2DMS​
	   GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 	isampler2DMSArray​
	   GL_INT_SAMPLER_BUFFER 	isamplerBuffer​
	   GL_INT_SAMPLER_2D_RECT 	isampler2DRect​
	   GL_UNSIGNED_INT_SAMPLER_1D 	usampler1D​
	   GL_UNSIGNED_INT_SAMPLER_2D 	usampler2D​
	   GL_UNSIGNED_INT_SAMPLER_3D​ 	usampler3D​
	   GL_UNSIGNED_INT_SAMPLER_CUBE​ 	usamplerCube​
	   GL_UNSIGNED_INT_SAMPLER_1D_ARRAY​ 	usampler2DArray​
	   GL_UNSIGNED_INT_SAMPLER_2D_ARRAY​ 	usampler2DArray​
	   GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE​ 	usampler2DMS​
	   GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY​ 	usampler2DMSArray​
	   GL_UNSIGNED_INT_SAMPLER_BUFFER​ 	usamplerBuffer​
	   GL_UNSIGNED_INT_SAMPLER_2D_RECT​ 	usampler2DRect​
	   */
	auto it = m.find(type);

	if(it != m.end()) return it->second;

	return "unknown";
}
void	glutpp::master::create_programs() {

	printf("%s\n", __PRETTY_FUNCTION__);

	std::shared_ptr<glutpp::glsl::program> p;

	// text
	{
		p.reset(new glutpp::glsl::program);
		p->init();

		p->add_shader(GLUTPP_SHADER_DIR"/v430/text/vs.glsl", GL_VERTEX_SHADER);
		p->add_shader(GLUTPP_SHADER_DIR"/v430/text/fs.glsl", GL_FRAGMENT_SHADER);

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

		p->add_shader(GLUTPP_SHADER_DIR"/v430/light/vs.glsl", GL_VERTEX_SHADER);
		p->add_shader(GLUTPP_SHADER_DIR"/v430/light/fs.glsl", GL_FRAGMENT_SHADER);

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

		p->scanUniforms();
	}

	//light and image
	{
		p.reset(new glutpp::glsl::program);
		p->init();

		p->add_shader(GLUTPP_SHADER_DIR"/v430/image/vs.glsl", GL_VERTEX_SHADER);
		p->add_shader(GLUTPP_SHADER_DIR"/v430/image/fs.glsl", GL_FRAGMENT_SHADER);

		p->compile();

		p->add_uniform(glutpp::uniform_name::e::IMAGE, "image");

		p->add_attrib(glutpp::attrib_name::e::POSITION, "position", 1);
		p->add_attrib(glutpp::attrib_name::e::NORMAL, "normal", 2);
		p->add_attrib(glutpp::attrib_name::e::TEXCOOR, "texcoor", 3);

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

		programs_[glutpp::program_name::IMAGE] = p;
	}

}
std::shared_ptr<glutpp::glsl::program> glutpp::master::use_program(glutpp::program_name::e name){
	auto p = get_program(name);

	p->use();

	current_ = p;

	return p;
}
std::shared_ptr<glutpp::glsl::program> glutpp::master::current_program(){
	assert(current_);

	return current_;
}
std::shared_ptr<glutpp::glsl::program> glutpp::master::get_program(glutpp::program_name::e name){
	auto it = programs_.find(name);

	if(it == programs_.end())
	{
		printf("program '%i' not found\n", name);
		exit(0);
	}

	auto p = (*it).second;

	assert(p);

	return p;
}
glutpp::actor::raw_factory_s glutpp::master::get_raw_factory() {
	assert(raw_factory_);
	return raw_factory_;
}
void glutpp::master::Command(std::string str) {

}



