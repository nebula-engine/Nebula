#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <glfw3.h>

#include <Galaxy-Network/message.hpp>

#include <Galaxy-Log/log.hpp>

#include <Nebula/config.hh>


//#include <Nebula/actor/event.hh>

#include <Nebula/Graphics/Context/Base.hh>
#include <Nebula/Graphics/Window/Base.hh>


#include <Nebula/Actor/RigidBody/Base.hh>

#include <Nebula/App/Base.hh>


#include <Nebula/Network/server.hh>
#include <Nebula/Network/client.hh>

#include <Nebula/Message/Scene/Create.hpp>
#include <Nebula/Message/Actor/Event/Base.hh>
#include <Nebula/Scene/Base.hh>

/** @todo since std smart pointers dont have ref counted unique pointers, owned objects must be stored as shared pointers.
 * to avoid unwanted shared_ptrs to owned objects, care must be taken when passing these objects around.
 * better documentation inside function bodies should be used to let me know what a shared_ptr is being used (how it 
 * should be treated.
 */

sp::shared_ptr<Neb::App::Base>	Neb::App::Base::g_app_;

Neb::Graphics::Window::Base_w	Neb::App::Base::window_main_;// = Neb::window::window_s;

Neb::App::Base::Base() {
}
Neb::App::Base::~Base() {
}
void				Neb::App::Base::init() {

	glfwInit();

	glfwSetErrorCallback(static_error_fun);
	

	
	// font
	//FT_Library ft;
	if(FT_Init_FreeType(&ft_))
	{
		printf("could not find freetype library\n");
		exit(0);
	}
	//NEBULA_DEBUG_0_FUNCTION;
}
void				Neb::App::Base::init_glew() {
	if(!flag_.any(Neb::App::Util::Flag::INIT_GLEW)) {

		GLenum err = glewInit();
		if (err != GLEW_OK)
		{
			printf("GLEW: %s\n", glewGetErrorString(err));
			exit(EXIT_FAILURE);
		}

		flag_.set(Neb::App::Util::Flag::INIT_GLEW);
	}
}
Neb::App::Base_s		Neb::App::Base::globalBase() {
	//Neb::App::Base_s shared = std::dynamic_pointer_cast<Neb::App::Base>(g_app_);
	assert(g_app_);
	return g_app_;
}
/*
   Neb::Graphics::Window::Base>			Neb::App::Base::create_window(int w, int h, int x, int y, char const * title) {
//NEBULA_DEBUG_0_FUNCTION;

boost::shared_ptr<Neb::window::desc> wd(new Neb::window::desc(w,h,x,y,title));

auto window = Neb::App::Base::Global()->create_window<Neb::Graphics::Window::Base>(wd);

//printf("window use count = %i\n", (int)window.use_count());

window->resize();

//windows_.push_back(window);

//printf("window use count = %i\n", (int)window.use_count());

return window;
}*/
/*Neb::Scene::scene_s Neb::App::Base::load_scene_local(Neb::scene::desc_s sd) {
//NEBULA_DEBUG_0_FUNCTION;

Neb::Scene::scene_s scene(new Neb::scene::scene(shared_from_this()));

scene->init(sd);
scene->user_type_ = Neb::Scene::scene::LOCAL;

scenes_.push_back(scene);

return scene;
}
Neb::Scene::scene_s Neb::App::Base::load_scene_remote(Neb::scene::desc_s sd) {
//NEBULA_DEBUG_0_FUNCTION;

Neb::Scene::scene_s scene(new Neb::scene::scene(shared_from_this()));

scene->init(sd);
scene->user_type_ = Neb::Scene::scene::REMOTE;

int i = scene->i();//desc_->raw_.i_;

assert(i != -1);

scenes_[i] = scene;

return scene;
}*//*
      void Neb::App::Base::load_layout(int name, char const * filename) {

      tinyxml2::XMLDocument document;
      if(document.LoadFile(filename))
      {
      fprintf(stderr, "error loading file %s\n", filename);
      abort();
      }

      tinyxml2::XMLElement* element = document.FirstChildElement("layout");

      std::shared_ptr<Neb::gui::layout> layout(new Neb::gui::layout);
      layout->load_xml(element);

      layouts_[name] = layout;
      }*//*
	    int	Neb::App::Base::activate_scene(int name_window, int name_scene) {	
//NEBULA_DEBUG_0_FUNCTION;

auto w = windows_.find(name_window);
auto s = scenes_.find(name_scene);

assert(w != windows_.end());
assert(s != scenes_.end());

w->second->set_scene(s->second);

return 0;
}
int	Neb::App::Base::activate_layout(int name_window, int name_layout) {
//NEBULA_DEBUG_0_FUNCTION;

auto w = windows_.find(name_window);
auto l = layouts_.find(name_layout);

assert(w != windows_.end());
assert(l != layouts_.end());

w->second->set_layout(l->second);

return 0;
}*/
void		Neb::App::Base::step(Neb::Core::TimeStep const & ts) {
	//NEBULA_DEBUG_1_FUNCTION;

	Neb::Scene::Util::Parent::step(ts);

	Neb::Graphics::Window::Util::Parent::step(ts);


}
mat4			Neb::App::Base::getPose() {
	return mat4();
}
mat4			Neb::App::Base::getPoseGlobal() {
	return mat4();
}
int			Neb::App::Base::loop() {
	//NEBULA_DEBUG_1_FUNCTION;

	static Neb::Core::TimeStep ts;

	while(!flag_.any(Neb::App::Util::Flag::E::SHOULD_RELEASE)) {
		ts.time = glfwGetTime();
		ts.dt = ts.time - ts.last;
		ts.last = ts.time;
		ts.frame++;

		step(ts);

		glfwPollEvents();
	}


	if(server_) server_->close();
	if(client_) client_->close();

	return 0;
}
void		Neb::App::Base::transmit_scenes(Neb::Network::Communicating_s c) {
	//NEBULA_DEBUG_0_FUNCTION;

	assert(c);

	typedef Neb::Scene::Util::Parent S;

	S::map_.for_each<0>([&] (S::map_type::iterator<0> it) {
			auto scene = sp::dynamic_pointer_cast<Neb::Scene::Base>(it->ptr_);
			assert(scene);

			auto msg = sp::make_shared<gal::net::omessage>();

			Neb::Message::Scene::Create scene_create;

			scene_create.load(scene);

			/** @todo why?!?!?!? */
			//msg->ar_ << scene_create;

			c->write(msg);
			});
}
void Neb::App::Base::reset_server(ip::tcp::endpoint const & endpoint) {
	//NEBULA_DEBUG_0_FUNCTION;
	server_.reset(new Neb::Network::Server(ios_, endpoint));
}
void Neb::App::Base::reset_client(ip::tcp::resolver::iterator endpoint_iterator) {
	//NEBULA_DEBUG_0_FUNCTION;
	client_.reset(new Neb::Network::Client(ios_, endpoint_iterator));
}


/*Neb::Graphics::Window::Base_s		Neb::App::Base::Main_Window() {
  Neb::Graphics::Window::Base_s w;

  if(!window_main_.expired())
  {
  w = window_main_.lock();
  return w;
  }

  return w;
  }
  void Neb::App::Base::Main_Window(Neb::Graphics::Window::Base_s w) {
  assert(w);
  window_main_ = w;
  }*/
Neb::Graphics::Window::Base_s		Neb::App::Base::get_window(GLFWwindow* window) {
	auto it = windows_glfw_.find(window);

	assert(it != windows_glfw_.end());

	return it->second;
}

void					Neb::App::Base::static_error_fun(int error, char const * description) {
	printf("%s\n", description);
	exit(0);
}
void					Neb::App::Base::static_window_pos_fun(GLFWwindow* window, int x, int y){
	GLUTPP_DEBUG_0_FUNCTION;

	auto w = Neb::App::Base::globalBase()->get_window(window);

	w->callback_window_pos_fun(window,x,y);
}
void					Neb::App::Base::static_window_size_fun(GLFWwindow* window, int width, int h){
	GLUTPP_DEBUG_0_FUNCTION;

	auto w = Neb::App::Base::globalBase()->get_window(window);

	w->callback_window_size_fun(window, width, h);
}
void					Neb::App::Base::static_window_close_fun(GLFWwindow* window){
	GLUTPP_DEBUG_0_FUNCTION;

	auto w = Neb::App::Base::globalBase()->get_window(window);

	w->callback_window_close_fun(window);
}
void					Neb::App::Base::static_window_refresh_fun(GLFWwindow* window) {
	GLUTPP_DEBUG_0_FUNCTION;

	auto w = Neb::App::Base::globalBase()->get_window(window);

	w->callback_window_refresh_fun(window);
}
void					Neb::App::Base::static_mouse_button_fun(GLFWwindow* window, int button, int action, int mods){
	GLUTPP_DEBUG_0_FUNCTION;

	auto w = Neb::App::Base::globalBase()->get_window(window);

	w->callback_mouse_button_fun(window, button, action, mods);
}
void Neb::App::Base::static_key_fun(GLFWwindow* window, int key, int scancode, int action, int mods){
	GLUTPP_DEBUG_0_FUNCTION;

	auto w = Neb::App::Base::globalBase()->get_window(window);

	w->callback_key_fun(window, key, scancode, action, mods);
}
void	Neb::App::Base::create_programs() {

	printf("%s\n", __PRETTY_FUNCTION__);

	std::shared_ptr<Neb::glsl::program> p;

	// text
	{
		p.reset(new Neb::glsl::program);
		p->init();

		p->add_shader(GLUTPP_SHADER_DIR"/v130/text/vs.glsl", GL_VERTEX_SHADER);
		p->add_shader(GLUTPP_SHADER_DIR"/v130/text/fs.glsl", GL_FRAGMENT_SHADER);

		p->compile();

		p->add_attrib(Neb::attrib_name::e::COOR, "coord", 0);

		//p->add_uniform("COLOR","font_color");
		//p->add_uniform("TEX","tex");

		p->scanUniforms();
		p->locate();

		programs_[Neb::program_name::TEXT] = p;
	}
	// quad




	// light
	{
		p.reset(new Neb::glsl::program);
		p->init();

		p->add_shader(GLUTPP_SHADER_DIR"/v130/light/vs.glsl", GL_VERTEX_SHADER);
		p->add_shader(GLUTPP_SHADER_DIR"/v130/light/fs.glsl", GL_FRAGMENT_SHADER);

		p->compile();

		//p->add_uniform(Neb::uniform_name::e::IMAGE, "image");

		p->add_attrib(Neb::attrib_name::e::POSITION, "position", 1);
		p->add_attrib(Neb::attrib_name::e::NORMAL, "normal", 2);

		//p->add_attrib(Neb::attrib_name::e::TEXCOOR, "texcoor");

		p->scanUniforms();
		p->locate();

		programs_[Neb::program_name::LIGHT] = p;


	}

	//light and image
	{
		p.reset(new Neb::glsl::program);
		p->init();

		p->add_shader(GLUTPP_SHADER_DIR"/v130/image/vs.glsl", GL_VERTEX_SHADER);
		p->add_shader(GLUTPP_SHADER_DIR"/v130/image/fs.glsl", GL_FRAGMENT_SHADER);

		p->compile();



		p->add_attrib(Neb::attrib_name::e::POSITION, "position", 1);
		p->add_attrib(Neb::attrib_name::e::NORMAL, "normal", 2);
		p->add_attrib(Neb::attrib_name::e::TEXCOOR, "texcoor", 3);

		/*
		   p->add_uniform(Neb::uniform_name::e::IMAGE, "image");


		   p->add_uniform(Neb::uniform_name::e::LIGHT_COUNT,"light_count");
		   p->add_uniform(Neb::uniform_name::e::MODEL,"model");
		   p->add_uniform(Neb::uniform_name::e::VIEW,"view");
		   p->add_uniform(Neb::uniform_name::e::PROJ,"proj");

		   p->add_uniform(Neb::uniform_name::e::FRONT_AMBIENT,"front.ambient");
		   p->add_uniform(Neb::uniform_name::e::FRONT_DIFFUSE,"front.diffuse");
		   p->add_uniform(Neb::uniform_name::e::FRONT_SPECULAR,"front.specular");
		   p->add_uniform(Neb::uniform_name::e::FRONT_EMISSION,"front.emission");
		   p->add_uniform(Neb::uniform_name::e::FRONT_SHININESS,"front.shininess");

		   p->add_uniform(Neb::uniform_name::e::LIGHT_POSITION, "lights", "position");
		   p->add_uniform(Neb::uniform_name::e::LIGHT_AMBIENT, "lights","ambient");
		   p->add_uniform(Neb::uniform_name::e::LIGHT_DIFFUSE, "lights","diffuse");
		   p->add_uniform(Neb::uniform_name::e::LIGHT_SPECULAR, "lights","specular");
		   p->add_uniform(Neb::uniform_name::e::LIGHT_SPOT_DIRECTION, "lights","spot_direction");
		   p->add_uniform(Neb::uniform_name::e::LIGHT_SPOT_CUTOFF, "lights","spot_cutoff");
		   p->add_uniform(Neb::uniform_name::e::LIGHT_SPOT_EXPONENT, "lights","spot_exponent");
		   p->add_uniform(Neb::uniform_name::e::LIGHT_SPOT_LIGHT_COS_CUTOFF, "lights","spot_light_cos_cutoff");
		   p->add_uniform(Neb::uniform_name::e::LIGHT_ATTEN_CONST, "lights","atten_const");
		   p->add_uniform(Neb::uniform_name::e::LIGHT_ATTEN_LINEAR, "lights","atten_linear");
		   p->add_uniform(Neb::uniform_name::e::LIGHT_ATTEN_QUAD, "lights","atten_quad");
		 */
		p->scanUniforms();
		p->locate();

		programs_[Neb::program_name::IMAGE] = p;
	}

}
std::shared_ptr<Neb::glsl::program> Neb::App::Base::use_program(Neb::program_name::e name){
	auto p = get_program(name);

	p->use();

	current_ = p;

	return p;
}
std::shared_ptr<Neb::glsl::program> Neb::App::Base::current_program(){
	assert(current_);

	return current_;
}
std::shared_ptr<Neb::glsl::program> Neb::App::Base::get_program(Neb::program_name::e name){
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
void		Neb::App::Base::command(std::string str) {

}
void		Neb::App::Base::sendServer(sp::shared_ptr< gal::net::omessage > msg)  {
	//NEBULA_DEBUG_1_FUNCTION;

	if(server_) {
		server_->write(msg);
	} else {
		BOOST_LOG_CHANNEL_SEV(lg, "neb", debug) << "no server";
	}
}
void		Neb::App::Base::sendClient(sp::shared_ptr< gal::net::omessage > msg)  {
	//NEBULA_DEBUG_1_FUNCTION;

	if(client_) {
		client_->write(msg);
	} else {
		BOOST_LOG_CHANNEL_SEV(lg, "neb", debug) << "no client";
	}
}
void		Neb::App::Base::sendClient(sp::shared_ptr< Neb::Message::OBase > message) {
	assert(message);

	neb::std::wrapper wrap(message);

	auto buffer = std::make_shared<gal::net::omessage>();

	/** @todo boost serial warning */
	//buffer->ar_ << wrapper;

	sendClient(buffer);
}
void		Neb::App::Base::sendServer(sp::shared_ptr< Neb::Message::OBase > message) {
	assert(message);

	neb::std::wrapper wrapper(message);

	auto buffer = std::make_shared<gal::net::omessage>();

	/** @todo boost serial warning */
	//buffer->ar_ << wrapper;

	sendServer(buffer);
}
void		Neb::App::Base::loadXml(std::string filename, neb::std::wrapper& w) {
	std::ifstream ifs;
	ifs.open(filename, std::ifstream::in);
	boost::archive::polymorphic_xml_iarchive ar(ifs);
	ar >> boost::serialization::make_nvp("wrapper",w);
}






