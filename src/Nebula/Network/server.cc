#include <assert.h>

#include <Galaxy-Network/server.hpp>

#include <Nebula/Util/typedef.hpp>
#include <Nebula/App/Base.hh>
#include <Nebula/Actor/Base.hh>
#include <Nebula/Scene/Base.hh>

Neb::Network::Server::Server(
		boost::asio::io_service& io_service,
		ip::tcp::endpoint const & endpoint):
	gal::net::server<Neb::Network::Communicating>(io_service, endpoint)
{
}
void		Neb::Network::Server::accept(sp::shared_ptr<Neb::Network::Communicating> client) {
	

	// exp
	//Neb::Actor::Control::RigidBody::raw_s control_raw(new neb::control::rigid_body::raw);

	/** @todo move all this to Box */

	/*
	   auto scene = app->get_scene(0);
	   assert(scene);

	   glutpp::actor::desc_s ad = scene->actors_deferred_[(char*)"player0"];
	   assert(ad);

	   auto actor = app->scenes_[0]->create_actor_local(ad);
	   auto rigidbody = actor->isRigidBody();

	   rigidbody->create_control(control_raw);

	// exp

	app->transmit_scenes(c);

	// exp

	Neb::network::control::rigid_body::create control_create;
	control_create.get_addr()->load_this(rigidbody);

	gal::net::message_s msg(new gal::net::message);

	msg->write(glutpp::network::type::CONTROL_CREATE);
	control_create.write(msg);

	c->write(msg);

	// exp
	 */
}




