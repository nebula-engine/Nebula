#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <glfw3.h>

#include <gal/std/terminal/command.hpp>
#include <gal/std/terminal/command_set.hpp>

#include <Galaxy-Network/message.hpp>

#include <Galaxy-Log/log.hpp>

#include <Nebula/config.hh>
//#include <Nebula/actor/event.hh>
#include <Nebula/gfx/Context/Base.hh>
#include <Nebula/gfx/window/Base.hh>
#include <Nebula/gfx/GUI/Object/terminal.hh>

#include <Nebula/core/actor/RigidBody/Base.hh>
#include <Nebula/app/Base.hh>
#include <Nebula/net/server.hh>
#include <Nebula/net/client.hh>

#include <Nebula/message/Scene/Create.hpp>
#include <Nebula/message/Actor/Event/Base.hh>
#include <Nebula/core/scene/Base.hh>


/** @todo since std smart pointers dont have ref counted unique pointers, owned objects must be stored as shared pointers.
 * to avoid unwanted shared_ptrs to owned objects, care must be taken when passing these objects around.
 * better documentation inside function bodies should be used to let me know what a shared_ptr is being used (how it 
 * should be treated.
 */

sp::shared_ptr<neb::app::base>	neb::app::base::g_app_;


neb::app::base::base() {
}
neb::app::base::~base() {
}
void				neb::app::base::init() {
	
	neb::app::__core::init();
	neb::app::__gfx::init();
	neb::app::__gfx_glsl::init();
	neb::app::__net::init();


	
	// glfw
	glfwInit();
	
	glfwSetErrorCallback(static_error_fun);

	flag_.set(neb::app::util::flag::INIT_GLFW);
	
	
	// font
	//FT_Library ft;
	if(FT_Init_FreeType(&ft_))
	{
		printf("could not find freetype library\n");
		exit(0);
	}
	//NEBULA_DEBUG_0_FUNCTION;






	// command set
	
	command_set_ = sp::make_shared<gal::std::command_set>();

	command_set_->init();	
	
	// exit command
	
	auto cmd_exit = sp::make_shared<gal::std::command>();

	cmd_exit->func_ = [&] (sp::shared_ptr<gal::std::terminal> term, bpo::variables_map vm) {
		sp::shared_ptr<neb::app::base> app = neb::app::base::global();
		app->flag_.set(neb::app::util::flag::SHOULD_RELEASE);
	};

	command_set_->map_["exit"] = cmd_exit;
	
	

}
void				neb::app::base::init_glew() {
	if(!flag_.any(neb::app::util::flag::INIT_GLEW)) {

		GLenum err = glewInit();
		if (err != GLEW_OK)
		{
			printf("GLEW: %s\n", glewGetErrorString(err));
			exit(EXIT_FAILURE);
		}

		flag_.set(neb::app::util::flag::INIT_GLEW);
	}
}
sp::shared_ptr<neb::app::base>		neb::app::base::global() {
	//sp::shared_ptr<neb::app::base> shared = std::dynamic_pointer_cast<neb::app::base>(g_app_);
	assert(g_app_);
	return g_app_;
}
void		neb::app::base::step(gal::std::timestep const & ts) {
	//NEBULA_DEBUG_1_FUNCTION;

	neb::core::scene::util::parent::step(ts);

	neb::gfx::window::util::parent::step(ts);


}
neb::core::pose			neb::app::base::getPose() {
	return neb::core::pose();
}
neb::core::pose			neb::app::base::getPoseGlobal() {
	return neb::core::pose();
}
int			neb::app::base::loop() {
	//NEBULA_DEBUG_1_FUNCTION;


	while(!flag_.any(neb::app::util::flag::E::SHOULD_RELEASE)) {
		ts_.time = glfwGetTime();
		ts_.dt = ts_.time - ts_.last;
		ts_.last = ts_.time;
		ts_.frame++;

		step(ts_);

		glfwPollEvents();
	}


	if(server_) server_->close();
	if(client_) client_->close();

	return 0;
}
void		neb::app::base::transmit_scenes(sp::shared_ptr<neb::Network::Communicating> c) {
	//NEBULA_DEBUG_0_FUNCTION;

	assert(c);

	typedef neb::core::scene::util::parent S;

	S::map_.for_each<0>([&] (S::map_type::iterator<0> it) {
			auto scene = sp::dynamic_pointer_cast<neb::core::scene::base>(it->ptr_);
			assert(scene);

			auto msg = sp::make_shared<gal::net::omessage>();

			neb::message::scene::Create scene_create;

			scene_create.load(scene);

			/** @todo why?!?!?!? */
			//msg->ar_ << scene_create;

			c->write(msg);
			});
}



/*sp::shared_ptr<neb::gfx::window::base>		neb::app::base::Main_Window() {
  sp::shared_ptr<neb::gfx::window::base> w;

  if(!window_main_.expired())
  {
  w = window_main_.lock();
  return w;
  }

  return w;
  }
  void neb::app::base::Main_Window(sp::shared_ptr<neb::gfx::window::base> w) {
  assert(w);
  window_main_ = w;
  }*/
sp::shared_ptr<neb::gfx::window::base>		neb::app::base::get_window(GLFWwindow* window) {
	auto it = windows_glfw_.find(window);

	assert(it != windows_glfw_.end());

	return it->second;
}



/*void		neb::app::base::command(sp::shared_ptr<neb::gfx::gui::object::terminal> term, ::std::string str) {

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
	::std::map< ::std::string, sp::shared_ptr<gal::std::command> > m;
	
	// a help function
	auto help = sp::make_shared<gal::std::command>();
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

void		neb::app::base::loadXml(::std::string filename, neb::std::wrapper& w) {
	::std::ifstream ifs;
	
	ifs.open(filename, ::std::ifstream::in);
	
	boost::archive::polymorphic_xml_iarchive ar(ifs);
	
	ar >> boost::serialization::make_nvp("wrapper",w);
}






