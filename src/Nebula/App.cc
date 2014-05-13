#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <glfw3.h>

#include <Nebula/config.hh>
#include <Nebula/Graphics/window/desc.hh>
#include <Nebula/Graphics/window/window.hh>
#include <Nebula/Memory/smart_ptr.hh>

//#include <Nebula/actor/event.hh>

#include <Nebula/renderable.hh>
#include <Nebula/Graphics/window/desc.hh>
#include <Nebula/Graphics/window/window.hh>
//#include <Nebula/scene/desc.hh>
#include <Nebula/network/message.hh>
//#include <Nebula/master.hh>


#include <Nebula/Actor/rigid_body/rigid_body.hh>

#include <Nebula/control/rigid_body/control.hh>

#include <Nebula/App.hh>

#include <Nebula/network/message.hh>
#include <Nebula/physics.hh>

/** @todo since std smart pointers dont have ref counted unique pointers, owned objects must be stored as shared pointers.
 * to avoid unwanted shared_ptrs to owned objects, care must be taken when passing these objects around.
 * better documentation inside function bodies should be used to let me know what a shared_ptr is being used (how it 
 * should be treated.
 */

Neb::App::App():
	windows_(Neb::App::global()->factories_.window_),
	flag_(0) {
	NEBULA_DEBUG_0_FUNCTION;
}
void Neb::App::f(unsigned int flag) {
	flag_ = flag;
}
unsigned int Neb::App::f() {
	return flag_;
}
void Neb::App::init() {
	NEBULA_DEBUG_0_FUNCTION;
}
Neb::weak_ptr<glutpp::window::window>			Neb::App::create_window(int w, int h, int x, int y, char const * title) {
	NEBULA_DEBUG_0_FUNCTION;

	boost::shared_ptr<glutpp::window::desc> wd(new glutpp::window::desc(w,h,x,y,title));
	
	auto window = glutpp::master::Global()->create_window<glutpp::window::window>(wd);
	
	//printf("window use count = %i\n", (int)window.use_count());
	
	window->resize();
	
	//windows_.push_back(window);

	//printf("window use count = %i\n", (int)window.use_count());

	return window;
}
Neb::scene::scene_s Neb::App::load_scene_local(glutpp::scene::desc_s sd) {
	NEBULA_DEBUG_0_FUNCTION;

	Neb::scene::scene_s scene(new Neb::scene::scene(shared_from_this()));
	
	scene->init(sd);
	scene->user_type_ = Neb::scene::scene::LOCAL;
	
	scenes_.push_back(scene);
	
	return scene;
}
Neb::scene::scene_s Neb::App::load_scene_remote(glutpp::scene::desc_s sd) {
	NEBULA_DEBUG_0_FUNCTION;

	Neb::scene::scene_s scene(new Neb::scene::scene(shared_from_this()));
	
	scene->init(sd);
	scene->user_type_ = Neb::scene::scene::REMOTE;
	
	int i = scene->i();//desc_->raw_.i_;

	assert(i != -1);
	
	scenes_[i] = scene;
	
	return scene;
}
void Neb::App::load_layout(int name, char const * filename) {

	tinyxml2::XMLDocument document;
	if(document.LoadFile(filename))
	{
		fprintf(stderr, "error loading file %s\n", filename);
		abort();
	}

	tinyxml2::XMLElement* element = document.FirstChildElement("layout");

	std::shared_ptr<glutpp::gui::layout> layout(new glutpp::gui::layout);
	layout->load_xml(element);

	layouts_[name] = layout;
}
int	Neb::App::activate_scene(int name_window, int name_scene) {	
	NEBULA_DEBUG_0_FUNCTION;

	auto w = windows_.find(name_window);
	auto s = scenes_.find(name_scene);

	assert(w != windows_.end());
	assert(s != scenes_.end());

	w->second->set_scene(s->second);

	return 0;
}
int	Neb::App::activate_layout(int name_window, int name_layout) {
	NEBULA_DEBUG_0_FUNCTION;

	auto w = windows_.find(name_window);
	auto l = layouts_.find(name_layout);

	assert(w != windows_.end());
	assert(l != layouts_.end());

	w->second->set_layout(l->second);

	return 0;
}
int Neb::App::step(double time) {
	NEBULA_DEBUG_1_FUNCTION;

	std::shared_ptr<Neb::scene::scene> scene;

	for(auto it = scenes_.begin(); it != scenes_.end();)
	{
		scene = it->second;
		assert(scene);

		if(scene->all(glutpp::scene::flag::SHOULD_RELEASE))
		{
			scene->release();

			it = scenes_.erase(it);
		}
		else
		{
			scene->step(time);

			++it;	
		}
	}

	// windows
	for(auto it = windows_.begin(); it != windows_.end();)
	{
		auto w = it->second;
		assert(w);

		if(w->all(glutpp::window::window::flag::e::SHOULD_RELEASE))
		{

			printf("erase\n");
			it = windows_.erase(it);
		}
		else
		{
			w->step(time);

			it++;
		}
	}

	// timer
	timer_set_.step(time);
	std::cout << "timer " << timer_set_.set_.size() << std::endl;
	
	return 0;
}
int	Neb::App::loop() {
	NEBULA_DEBUG_1_FUNCTION;

	double time;

	while(!any(Neb::App::flag::e::SHOULD_RELEASE))
	{	
		time = glfwGetTime();

		step(time);

		glfwPollEvents();
	}


	if(server_) server_->close();
	if(client_) client_->close();

	return 0;
}
void Neb::App::set_should_release() {
	set(Neb::App::flag::e::SHOULD_RELEASE);
}
glutpp::window::window_s Neb::App::get_window(int i) {
	glutpp::window::window_s window;
	auto it = windows_.find(i);
	if(it != windows_.end())
	{
		return it->second;
	}

	return window;
}
Neb::scene::scene_s Neb::App::get_scene(int name) {
	NEBULA_DEBUG_1_FUNCTION;

	auto s = scenes_[name];

	assert(s);

	return s;
}
Neb::scene::scene_s Neb::App::get_scene(glutpp::scene::addr_s addr) {
	NEBULA_DEBUG_1_FUNCTION;

	assert(addr);

	auto vec = addr->get_vec();

	assert(vec->vec_.size() == 1);

	auto s = scenes_[vec->vec_.at(0)];

	assert(s);

	return s;
}
Neb::Actor::Base_s Neb::App::get_actor(glutpp::actor::addr_s addr) {

	Neb::Actor::Base_s actor;

	auto scene = get_scene(addr->get_scene_addr());
	assert(scene);

	auto vec = addr->get_vec();
	if(!vec->vec_.empty())
	{
		actor = scene->get_actor(addr);
	}

	return actor;
}
int Neb::App::transmit_scenes(std::shared_ptr<Neb::network::communicating> c) {
	NEBULA_DEBUG_0_FUNCTION;

	assert(c);

	int type = glutpp::network::type::SCENE_CREATE;

	for(auto it = scenes_.begin(); it != scenes_.end(); ++it) {
		auto s = it->second;
		assert(s);

		gal::network::message_s msg(new gal::network::message);

		msg->write(&type, sizeof(int));

		glutpp::network::scene::create scene_create;

		scene_create.load(s);
		scene_create.write(msg);

		c->write(msg);
	}

	return 0;
}
void Neb::App::reset_server(unsigned short port) {
	NEBULA_DEBUG_0_FUNCTION;
	server_.reset(new Neb::network::server(shared_from_this(), port, 10));
}
void Neb::App::reset_client(char const * addr, unsigned short port) {
	NEBULA_DEBUG_0_FUNCTION;
	client_.reset(new Neb::network::client(shared_from_this(), addr, port));
	client_->start();
}
void Neb::App::send_server(gal::network::message::shared_t msg)  {
	NEBULA_DEBUG_1_FUNCTION;

	if(server_)
	{
		server_->write(msg);
	}
	else
	{
		printf("WARNING: no server\n");
	}
}
void Neb::App::send_client(gal::network::message::shared_t msg)  {
	NEBULA_DEBUG_1_FUNCTION;

	if(client_)
	{
		client_->write(msg);
	}
	else
	{
		printf("WARNING: no server\n");
	}
}
void Neb::App::recv_scene_create(gal::network::message_s msg) {

}
void Neb::App::recv_actor_create(gal::network::message_s msg) {

}
void Neb::App::recv_actor_update(gal::network::message_s msg) {

}
void Neb::App::recv_actor_event(gal::network::message_s msg) {

	glutpp::network::actor::event actor_event;
	actor_event.read(msg);

	auto actor = get_actor(actor_event.get_addr());
	assert(actor);
	auto scene = actor->get_scene();
	assert(scene);

	int type = actor_event.get_event()->type_;

	switch(type)
	{
		case glutpp::actor::event::type::e::FIRE:
			scene->fire(actor);
			break;
		default:
			printf("DEBUG: unknown event type %i\n", type);
			break;
	}
}
void Neb::App::recv_control_create(gal::network::message_s msg) {

}
void Neb::App::recv_control_update(gal::network::message_s msg) {

	Neb::network::control::rigid_body::update control_update;
	control_update.read(msg);

	auto actor = get_actor(control_update.get_addr());
	
	auto rigidbody = actor->isRigidBody();

	if(rigidbody) {
		auto control = rigidbody->control_;
		if(control)
		{
			control->raw_ = *(control_update.get_raw());

			control->print();
		}
		else
		{
			printf("control not found\n");
		}
	} else {
		printf("actor not found\n");
	}
}



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
Neb::weak_ptr<glutpp::window::window>		glutpp::master::get_window(GLFWwindow* window) {
	auto it = windows_.find(window);
	
	Neb::weak_ptr<glutpp::window::window> w(it->second);
	
	//Neb::weak_ptr<glutpp::window::window> w(windows_[window]);
	
	return w;
}
void glutpp::master::static_error_fun(int error, char const * description) {
	printf("%s\n", description);
	exit(0);
}
void glutpp::master::static_window_pos_fun(GLFWwindow* window, int x, int y){
	GLUTPP_DEBUG_0_FUNCTION;

	auto w = master::Global()->get_window(window);
	
	w->callback_window_pos_fun(window,x,y);
}
void glutpp::master::static_window_size_fun(GLFWwindow* window, int width, int h){
	GLUTPP_DEBUG_0_FUNCTION;
	auto w = master::Global()->get_window(window);
	w->callback_window_size_fun(window, width, h);
}
void glutpp::master::static_window_close_fun(GLFWwindow* window){
	GLUTPP_DEBUG_0_FUNCTION;
	auto w = master::Global()->get_window(window);
	w->callback_window_close_fun(window);
}
void glutpp::master::static_window_refresh_fun(GLFWwindow* window) {
	GLUTPP_DEBUG_0_FUNCTION;

	auto w = master::Global()->get_window(window);
	w->callback_window_refresh_fun(window);
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
GLFWwindow*		glutpp::master::reg(glutpp::window::window_s w) {
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

	return g;
}

void	glutpp::master::create_programs() {

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

		//p->add_uniform("COLOR","font_color");
		//p->add_uniform("TEX","tex");

		p->scanUniforms();
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

		/*
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
		 */
		p->scanUniforms();
		p->locate();

		programs_[glutpp::program_name::LIGHT] = p;


	}

	//light and image
	{
		p.reset(new glutpp::glsl::program);
		p->init();

		p->add_shader(GLUTPP_SHADER_DIR"/v130/image/vs.glsl", GL_VERTEX_SHADER);
		p->add_shader(GLUTPP_SHADER_DIR"/v130/image/fs.glsl", GL_FRAGMENT_SHADER);

		p->compile();



		p->add_attrib(glutpp::attrib_name::e::POSITION, "position", 1);
		p->add_attrib(glutpp::attrib_name::e::NORMAL, "normal", 2);
		p->add_attrib(glutpp::attrib_name::e::TEXCOOR, "texcoor", 3);

		/*
		   p->add_uniform(glutpp::uniform_name::e::IMAGE, "image");


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
		 */
		p->scanUniforms();
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
	assert(actor_raw_factory_);
	return actor_raw_factory_;
}
void glutpp::master::Command(std::string str) {

}



