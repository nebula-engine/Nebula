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

#include <neb/net/server.hh>
#include <neb/net/client.hh>

#include <neb/gfx/window/Base.hh>
#include <neb/gfx/Context/Base.hh>
#include <neb/gfx/GUI/Object/terminal.hh>


#include <neb/net/server.hh>
#include <neb/net/client.hh>

#include <neb/app/Base.hh>
//#include <neb/Game/user.hh>
//#include <neb/Physics.hh>
#include <neb/core/scene/base.hpp>
//#include <neb/simulation_callback.hh>
#include <neb/core/shape/base.hpp>
//#include <neb/core/actor/Control/RigidBody/Base.hh>
#include <neb/core/actor/RigidDynamic/Base.hh>

/*
namespace box
{
	enum box
	{
		WINDOW_0,
		WINDOW_1,
		SCENE_0,
		LAYOUT_HOME,
		LAYOUT_GAME,
	};

	namespace layouts
	{
		namespace home
		{
			class local_game: public glutpp::gui::object::textview
			{
				public:
					virtual int	mouse_button_fun(int button, int action, int mods)
					{
						return 1;
					}
			};
			class network_game: public glutpp::gui::object::textview
			{
				public:
					virtual int	mouse_button_fun(int button, int action, int mods)
					{
						return 1;
					}
			};
		}
		namespace game
		{
			class exit: public glutpp::gui::object::textview
			{
				public:
					virtual int	mouse_button_fun(int button, int action, int mods)
					{
						return 1;
					}
			};
		}
	}
	class object_factory: public glutpp::gui::object::object_factory
	{
		public:
			virtual sp::shared_ptr<glutpp::gui::object::object>	create(tinyxml2::XMLElement* element) {

				assert(element);

				std::shared_ptr<glutpp::gui::object::object> object;

				char const * buf = element->Attribute("type");
				assert(buf);

				if(strcmp(buf, "home_local_game") == 0)
				{
					object.reset(new layouts::home::local_game);
				}
				else if(strcmp(buf, "home_network_game") == 0)
				{
					object.reset(new layouts::home::network_game);
				}
				else if(strcmp(buf, "game_exit") == 0)
				{
					object.reset(new layouts::game::exit);
				}
				else
				{
					object = glutpp::gui::object::object_factory::create(element);
				}

				object->load_xml(element);

				return object;
			}
	};
}
*/


int	client_main(char const * addr, short unsigned int port) {
	
	auto app = neb::app::base::globalBase();
	
	assert(app);
	
	//app->create_window(600, 600, 200, 100, "box");
	
	//app->reset_client(addr, port);
	
	//app->loop();
	
	return 0;	
}
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
	typedef neb::WrapperTyped<A> W;
	
	auto app = neb::app::base::globalBase();
	
	W wrap;

	app->loadXml<W>(std::string("player0.xml"), wrap);
	
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
int	server_main(short unsigned int port) {

	auto app = neb::app::base::globalBase();

	app->reset_server(port);
	
	typedef neb::util::parent< neb::core::scene::base > S;
	typedef neb::util::parent< neb::gfx::window::base > W;

	typedef neb::WrapperTyped<neb::core::scene::base>	Wrapper;

	{
		// Scene
		Wrapper wrap;
		
		app->loadXml<Wrapper>(std::string("../scene.xml"), wrap);
		
		auto scene = wrap.ptr_;
		
		
		
		app->S::insert(scene);
		
		//app->load_layout(box::LAYOUT_HOME, "../layout_home.xml");
		//app->load_layout(box::LAYOUT_GAME, "../layout_game.xml");
		
		// Window
		sp::shared_ptr<neb::gfx::window::base> window(new neb::gfx::window::base);
		
		window->w_ = 600;
		window->h_ = 600;
		window->x_ = 200;
		window->y_ = 100;
		window->title_ = "box";
	
		app->W::insert(window);
		
		// Context
		sp::shared_ptr<neb::gfx::context::base> context(new neb::gfx::context::base);
		
		context->scene_ = scene;

		// Player
		create_player(window, scene);
		
		// vehicle
		//app->scenes_[box::SCENE_0]->create_vehicle();
	}
	app->loop();

	return 0;
}
int	main(int argc, char const ** argv)
{
	if(argc < 2)
	{
		printf("usage:\n");
		printf("    %s <mode> <port>\n", argv[0]);
		printf("    %s h\n", argv[0]);
		return 1;
	}

	if(strcmp(argv[1], "h") == 0)
	{
		//printf("size\n");
		//printf("glutpp::shape_desc    %i\n", (int)sizeof(glutpp::shape::desc));
		//printf("neb::actor::desc      %i\n", (int)sizeof(glutpp::actor::desc));
		return 0;
	}

	if(argc < 3)
	{
		printf("usage: %s <mode> <port>\n", argv[0]);
		return 1;
	}

	neb::init();

	//neb::app::base::global()->object_factory_.reset(new box::object_factory);
	//neb::app::base::global()->raw_factory_.reset(new neb::actor::raw_factory);

	
	if(strcmp(argv[1], "s") == 0)
	{
		return server_main(atoi(argv[2]));
	}
	else if(strcmp(argv[1], "c") == 0)
	{
		return client_main("127.0.0.1", atoi(argv[2]));
	}


	return 0;
}



