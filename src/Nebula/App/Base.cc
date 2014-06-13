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
#include <Nebula/Graphics/GUI/Object/terminal.hh>

#include <Nebula/Actor/RigidBody/Base.hh>
#include <Nebula/App/Base.hh>
#include <Nebula/Network/server.hh>
#include <Nebula/Network/client.hh>

#include <Nebula/Message/Scene/Create.hpp>
#include <Nebula/Message/Actor/Event/Base.hh>
#include <Nebula/Scene/Base.hh>
#include <Nebula/Util/command.hpp>
#include <Nebula/Util/command_set.hpp>

/** @todo since std smart pointers dont have ref counted unique pointers, owned objects must be stored as shared pointers.
 * to avoid unwanted shared_ptrs to owned objects, care must be taken when passing these objects around.
 * better documentation inside function bodies should be used to let me know what a shared_ptr is being used (how it 
 * should be treated.
 */

sp::shared_ptr<neb::App::Base>	neb::App::Base::g_app_;


neb::App::Base::Base() {
}
neb::App::Base::~Base() {
}
void				neb::App::Base::init() {

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






	// command set
	
	command_set_ = sp::make_shared<neb::util::command_set>();

	command_set_->init();	
	
	// exit command
	
	auto cmd_exit = sp::make_shared<neb::util::command>();

	cmd_exit->func_ = [&] (sp::shared_ptr<neb::util::terminal> term, bpo::variables_map vm) {
		sp::shared_ptr<neb::App::Base> app = neb::App::Base::global();
		app->flag_.set(neb::App::Util::Flag::SHOULD_RELEASE);
	};

	command_set_->map_["exit"] = cmd_exit;
	
	

}
void				neb::App::Base::init_glew() {
	if(!flag_.any(neb::App::Util::Flag::INIT_GLEW)) {

		GLenum err = glewInit();
		if (err != GLEW_OK)
		{
			printf("GLEW: %s\n", glewGetErrorString(err));
			exit(EXIT_FAILURE);
		}

		flag_.set(neb::App::Util::Flag::INIT_GLEW);
	}
}
sp::shared_ptr<neb::App::Base>		neb::App::Base::global() {
	//sp::shared_ptr<neb::App::Base> shared = std::dynamic_pointer_cast<neb::App::Base>(g_app_);
	assert(g_app_);
	return g_app_;
}
void		neb::App::Base::step(neb::core::TimeStep const & ts) {
	//NEBULA_DEBUG_1_FUNCTION;

	neb::Scene::Util::Parent::step(ts);

	neb::gfx::Window::Util::Parent::step(ts);


}
mat4			neb::App::Base::getPose() {
	return mat4();
}
mat4			neb::App::Base::getPoseGlobal() {
	return mat4();
}
int			neb::App::Base::loop() {
	//NEBULA_DEBUG_1_FUNCTION;

	static neb::core::TimeStep ts;

	while(!flag_.any(neb::App::Util::Flag::E::SHOULD_RELEASE)) {
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
void		neb::App::Base::transmit_scenes(sp::shared_ptr<neb::Network::Communicating> c) {
	//NEBULA_DEBUG_0_FUNCTION;

	assert(c);

	typedef neb::Scene::Util::Parent S;

	S::map_.for_each<0>([&] (S::map_type::iterator<0> it) {
			auto scene = sp::dynamic_pointer_cast<neb::Scene::Base>(it->ptr_);
			assert(scene);

			auto msg = sp::make_shared<gal::net::omessage>();

			neb::Message::Scene::Create scene_create;

			scene_create.load(scene);

			/** @todo why?!?!?!? */
			//msg->ar_ << scene_create;

			c->write(msg);
			});
}



/*sp::shared_ptr<neb::gfx::Window::Base>		neb::App::Base::Main_Window() {
  sp::shared_ptr<neb::gfx::Window::Base> w;

  if(!window_main_.expired())
  {
  w = window_main_.lock();
  return w;
  }

  return w;
  }
  void neb::App::Base::Main_Window(sp::shared_ptr<neb::gfx::Window::Base> w) {
  assert(w);
  window_main_ = w;
  }*/
sp::shared_ptr<neb::gfx::Window::Base>		neb::App::Base::get_window(GLFWwindow* window) {
	auto it = windows_glfw_.find(window);

	assert(it != windows_glfw_.end());

	return it->second;
}



/*void		neb::App::Base::command(sp::shared_ptr<neb::gfx::gui::object::terminal> term, ::std::string str) {

	// split
	
	::std::istringstream iss(str);
	
	::std::vector< ::std::string > tokens;

	::std::copy(
			::std::istream_iterator< ::std::string >(iss),
			::std::istream_iterator< ::std::string >(),
			::std::back_inserter< ::std::vector< ::std::string > >(tokens));
	
	if(tokens.empty()) return;
	
	int ac = tokens.size();
	char const ** av = new char const *[ac];
	char const ** pc = av;
	for(auto t : tokens) {
		*pc = t.c_str();
		pc++;
	}
	
	
	// future class members...
	::std::map< ::std::string, sp::shared_ptr<neb::util::command> > m;
	
	// a help function
	auto help = sp::make_shared<neb::util::command>();
	help->func_ = [] (sp::shared_ptr<neb::gfx::gui::object::terminal> term, bpo::variables_map vm) {
		term->lines_.push_back("exit");
		term->lines_.push_back("help");
	};
	
	// a way out

	
	// find command
	auto it = m.find(tokens.front());
	
	if(it != m.end()) {
		it->second->operator()(term,ac,av);
	} else {
		term->lines_.push_back(tokens.front() + ": Command not found.");
	}
	
}*/

void		neb::App::Base::loadXml(::std::string filename, neb::std::wrapper& w) {
	::std::ifstream ifs;
	
	ifs.open(filename, ::std::ifstream::in);
	
	boost::archive::polymorphic_xml_iarchive ar(ifs);
	
	ar >> boost::serialization::make_nvp("wrapper",w);
}






