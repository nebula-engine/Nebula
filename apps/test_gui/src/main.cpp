
#include <glm/gtc/matrix_transform.hpp>

#include <gal/console/base.hpp>

#include <gal/etc/stopwatch.hpp>

#include <neb/fnd/context/Window.hpp>
#include <neb/fnd/environ/SceneDefault.hpp>
#include <neb/fnd/environ/Two.hpp>
#include <neb/fnd/net/msg/Code.hpp>
#include <neb/fnd/net/msg/game/game/List.hpp>
#include <neb/fnd/core/actor/rigidbody/Base.hpp>
#include <neb/fnd/core/actor/rigidbody/desc.hpp>
#include <neb/fnd/core/shape/cuboid/desc.hpp>

//#include <neb/fnd/app/Base00.hpp>
#include <neb/fnd1/app/Base00.hpp>

int			main(int ac, char ** av)
{
	// terminal
	auto app = neb::fnd1::app::Base00::s_init(ac, av);

	auto window = app->create_window().lock();

	auto context = window->createContextWindow().lock();

	auto environ = context->createEnvironTwo().lock();

	auto layout = app->create_layout(window, environ).lock();

	// create game
	neb::fnd::game::game::Desc gd;
	gd._M_net_type = 1;

	auto game = app->create_game(gd);

	auto m = game->create_map_dll("../mod/maze/build/dynamic/libnebula_ext_maze.so");

	auto scene = m->create_scene();

	// server stuff

	app->create_server_1(20000);

	// client stuff

	//m1.set_data(15)

	auto m0 = app->create_msg_code();
	
	auto after_connect = [&] (std::shared_ptr<neb::fnd::net::comm::Base> c)
	{
		auto app = c->get_fnd_app();
		auto c0 = neb::fnd::net::msg::Code::Codes::REQUEST_GAME_LIST;
		
		m0->_M_code = c0;
		c->send(m0);
	};

	auto after_m0_response = [] (std::shared_ptr<neb::fnd::net::msg::Base> m, std::shared_ptr<neb::fnd::net::comm::Base> c) {
		auto app = c->get_fnd_app();

		auto c1 = neb::fnd::net::msg::Code::Codes::REQUEST_GAME_JOIN;
		auto m1 = app->create_msg_code();
		m1->_M_code = c1;
		
		auto m2 = std::dynamic_pointer_cast<neb::fnd::net::msg::game::game::List>(m);
		assert(m2);

		for(auto i : m2->_M_data) {
			printf("\t%i\n", i._M_index);
		}

		if(!m2->_M_data.empty()) {
			auto i = m2->_M_data[0];
			m1->write(&i._M_index, sizeof(gal::object_index));
			c->send(m1);
		} else {
			abort();
		}
	};

	m0->set_func_after_response(after_m0_response);

	auto c = app->create_client("127.0.0.1", 20000, after_connect);

	// gui stuff
	
	//auto windows = app->get_windows();
	
	//auto window = app->P_W::fornt(); //windows[0];

	//context = window->createContextWindow().lock();

	auto e1 = context->createEnvironSceneDefault().lock();

	neb::fnd::core::actor::rigidbody::Desc ad;
	neb::fnd::core::shape::cuboid::Desc sd;
	auto actor_player = std::dynamic_pointer_cast<neb::fnd::core::actor::rigidbody::Base>(scene->createActorRigidDynamicCuboid(ad, sd).lock());
	
	m->spawn_actor(actor_player);

	auto weap = actor_player->createWeaponSimpleProjectile(window, 0.2, 10.0, 5.0);

	auto control = actor_player->createControlManual(window);

	e1->create_view_ridealong(actor_player);

	e1->set_drawable(scene);

	app->loop();
}


