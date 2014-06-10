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

#include <Nebula/Network/server.hh>
#include <Nebula/Network/client.hh>

#include <Nebula/Graphics/Window/Base.hh>
#include <Nebula/Graphics/Context/Base.hh>
#include <Nebula/Graphics/GUI/Object/terminal.hh>


#include <Nebula/Network/server.hh>
#include <Nebula/Network/client.hh>

#include <Nebula/App/Base.hh>
//#include <Nebula/Game/user.hh>
//#include <Nebula/Physics.hh>
#include <Nebula/Scene/Base.hh>
//#include <Nebula/simulation_callback.hh>
#include <Nebula/Shape/Base.hh>
//#include <Nebula/Actor/Control/RigidBody/Base.hh>
#include <Nebula/Actor/RigidDynamic/Base.hh>
#include <Nebula/Util/wrapper.hpp>



/*void	create_player(glutpp::window::window_s wnd, glutpp::scene::scene_s scene) {
	
	auto rigidbody = create_player_actor(scene);

	// so you can fire
	rigidbody->connect(wnd);

	// control
	neb::control::rigid_body::raw_s raw;
	
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
Neb::Actor::RigidBody::Base_s create_player_actor(Neb::Scene::Base_s scene) {

	typedef Neb::Actor::Base A;
	
	auto app = Neb::App::Base::globalBase();
	
	neb::std::wrapper wrap;

	app->loadXml(std::string("player0.xml"), wrap);
	
	//glutpp::actor::desc_s ad = scene->actors_deferred_[(char*)"player0"];
	//assert(ad);
	
	scene->insert(wrap.ptr_);
	
	
	//auto rigidbody = actor->isRigidBody();
	
	auto rigidbody = wrap.ptr_->isActorRigidBody();

	assert(rigidbody);

	return rigidbody;
}
void	create_player(Neb::Graphics::Window::Base_s wnd, Neb::Scene::Base_s scene) {
	
	auto rigidbody = create_player_actor(scene);

	// so you can fire
	rigidbody->connect(wnd);

	// control
	Neb::Actor::Control::RigidBody::Manual_s control;
	
	
	
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
	
	Neb::init();
	
	//Neb::App::Base::global()->object_factory_.reset(new box::object_factory);
	//Neb::App::Base::global()->raw_factory_.reset(new neb::actor::raw_factory);
	
	//int	client_main(char const * addr, short unsigned int port) {
	
	auto app = Neb::App::Base::globalBase();
	
	assert(app);
	
	//app->create_window(600, 600, 200, 100, "box");
	
	//app->reset_client(addr, port);
	
	//app->loop();
	

	return 0;
}



