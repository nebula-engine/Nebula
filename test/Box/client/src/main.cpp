/* 
 * - cleanly destroy actors and scenes (so that scene can be reset in-game)
 * - automate connection of camera (and other objects) to devices (via JSL::Master)
 * - cleanly exit (JSL read threads, glut windows)
 * - create terminal (via GUL)
 * - make command line revolve around objects (ex. command to change camera mode or target would be directed to the camera)
 *   - help command to print list of objects listening to terminal
 *   - another idea: have program listen to actual terminal (/dev/ttyX)
 * - focus tracking for windows to suspend signals when appropriate
 */

#include <functional>

#include <Nebula/net/server.hh>
#include <Nebula/net/client.hh>

#include <Nebula/gfx/window/Base.hh>
#include <Nebula/gfx/Context/Base.hh>
#include <Nebula/gfx/GUI/Object/terminal.hh>


#include <Nebula/net/server.hh>
#include <Nebula/net/client.hh>

#include <Nebula/app/Base.hh>
//#include <Nebula/Game/user.hh>
//#include <Nebula/Physics.hh>
#include <Nebula/core/scene/Base.hh>
//#include <Nebula/simulation_callback.hh>
#include <Nebula/core/shape/Base.hh>
//#include <Nebula/core/actor/Control/RigidBody/Base.hh>
#include <Nebula/core/actor/RigidDynamic/Base.hh>
#include <Nebula/util/wrapper.hpp>



/*void	create_player(sp::shared_ptr<glutpp::window::window> wnd, sp::shared_ptr<glutpp::scene::scene> scene) {
	
	auto rigidbody = create_player_actor(scene);

	// so you can fire
	rigidbody->connect(wnd);

	// control
	sp::shared_ptr<neb::control::rigid_body::raw> raw;
	
	app->create_window(600, 600, 200, 100, "box");
	app->create_window(600, 600, 200, 100, "box second");

	//rigidbody->create_control(raw);
	
	// user
	//std::shared_ptr<neb::user> user(new neb::user);	
	//user->set_control(control);
	//user->connect(wnd);
	
	app->activate_scene(box::WINDOW_0, box::SCENE_0);
	app->activate_scene(box::WINDOW_1, box::SCENE_0);
	//app->activate_layout(box::LAYOUT_GAME);

}*/
sp::shared_ptr<neb::Actor::RigidBody::base> create_player_actor(sp::shared_ptr<neb::core::scene::base> scene) {

	typedef neb::Actor::base A;
	
	auto app = neb::app::base::globalBase();
	
	neb::std::wrapper wrap;

	app->loadXml(std::string("player0.xml"), wrap);
	
	//sp::shared_ptr<glutpp::actor::desc> ad = scene->actors_deferred_[(char*)"player0"];
	//assert(ad);
	
	scene->insert(wrap.ptr_);
	
	
	//auto rigidbody = actor->isRigidBody();
	
	auto rigidbody = wrap.ptr_->isActorRigidBody();

	assert(rigidbody);

	return rigidbody;
}
void	create_player(sp::shared_ptr<neb::gfx::window::base> wnd, sp::shared_ptr<neb::core::scene::base> scene) {
	
	auto rigidbody = create_player_actor(scene);

	// so you can fire
	rigidbody->connect(wnd);

	// control
	sp::shared_ptr<neb::Actor::Control::RigidBody::Manual> control;
	
	
	
	rigidbody->control_ = control;
	
	//app->prepare();
	// user
	//std::shared_ptr<neb::user> user(new neb::user);	
	//user->set_control(control);
	//user->connect(wnd);
	

}
int	main(int argc, char const ** argv) {

	if(argc < 2) {
		printf("usage: %s <port>\n", argv[0]);
		return 1;
	}
	
	neb::init();
	
	//neb::app::base::global()->object_factory_.reset(new box::object_factory);
	//neb::app::base::global()->raw_factory_.reset(new neb::actor::raw_factory);
	
	//int	client_main(char const * addr, short unsigned int port) {
	
	auto app = neb::app::base::globalBase();
	
	assert(app);
	
	//app->create_window(600, 600, 200, 100, "box");
	
	//app->reset_client(addr, port);
	
	//app->loop();
	

	return 0;
}



