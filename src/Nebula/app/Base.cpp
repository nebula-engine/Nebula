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
neb::core::pose				neb::app::base::getPose() {
	return neb::core::pose();
}
neb::core::pose				neb::app::base::getPoseGlobal() {
	return neb::core::pose();
}
void					neb::app::base::loop1() {

	auto self(sp::dynamic_pointer_cast<neb::app::base>(shared_from_this()));
	assert(self);
	
	//::std::thread t(::std::bind(&neb::app::base::loop2, self));
	
	
	while(!flag_.any(neb::app::util::flag::E::SHOULD_RELEASE)) {

		::std::cout << "loop1" << ::std::endl;

		ts_.step(glfwGetTime());

		step1(ts_);
		step2(ts_);
		
		//::std::this_thread::yield();
	}
	
	//t.join();
	
	if(server_) server_->close();
	if(client_) client_->close();

}
void					neb::app::base::loop2() {

	gal::std::timestep ts;

	while(!flag_.any(neb::app::util::flag::E::SHOULD_RELEASE)) {

		::std::cout << "loop2" << ::std::endl;

		ts.step(glfwGetTime());

		step2(ts);

		::std::this_thread::yield();
	}


}
void					neb::app::base::step1(gal::std::timestep const & ts) {

	neb::core::scene::util::parent::step(ts);

}
void					neb::app::base::step2(gal::std::timestep const & ts) {

	neb::gfx::window::util::parent::step(ts);

	glfwPollEvents();
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
sp::shared_ptr<neb::gfx::window::base>		neb::app::base::get_window(GLFWwindow* window) {
	auto it = windows_glfw_.find(window);

	assert(it != windows_glfw_.end());

	return it->second;
}
void		neb::app::base::loadXml(::std::string filename, neb::std::wrapper& w) {
	::std::ifstream ifs;

	ifs.open(filename, ::std::ifstream::in);

	boost::archive::polymorphic_xml_iarchive ar(ifs);

	ar >> boost::serialization::make_nvp("wrapper",w);
}






