
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
	auto app = neb::fnd1::app::Base00::s_init(ac, av);

	// create game
	neb::fnd::game::game::Desc gd;
	gd._M_net_type = 1;

	auto game = app->create_game(gd);

	auto m = game->create_map_dll(
			"../mod/maze/build/dynamic/libnebula_ext_maze.so");

	auto scene = m->create_scene();

	// server stuff

	app->create_server_1(20000);

	// client stuff

	//m1.set_data(15)
	/*
	neb::fnd::core::actor::rigidbody::Desc ad;
	neb::fnd::core::shape::cuboid::Desc sd;
	auto actor_player = std::dynamic_pointer_cast<neb::fnd::core::actor::rigidbody::Base>(scene->createActorRigidDynamicCuboid(ad, sd).lock());
	
	m->spawn_actor(actor_player);
*/
	app->loop();
}


