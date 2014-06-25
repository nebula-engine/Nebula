#include <assert.h>

#include <Galaxy-Network/server.hpp>

#include <neb/util/typedef.hpp>
#include <neb/app/Base.hh>
#include <neb/core/actor/base.hpp>
#include <neb/core/scene/Base.hh>

neb::Network::Server::Server(
		boost::asio::io_service& io_service,
		ip::tcp::endpoint const & endpoint):
	gal::net::server<neb::Network::Communicating>(io_service, endpoint)
{
}
void		neb::Network::Server::accept(sp::shared_ptr<neb::Network::Communicating> client) {
	

	// exp
	//sp::shared_ptr<neb::core::actor::Control::RigidBody::raw> control_raw(new neb::control::rigid_body::raw);

	/** @todo move all this to Box */

	/*
	   auto scene = app->get_scene(0);
	   assert(scene);

	   sp::shared_ptr<glutpp::actor::desc> ad = scene->actors_deferred_[(char*)"player0"];
	   assert(ad);

	   auto actor = app->scenes_[0]->create_actor_local(ad);
	   auto rigidbody = actor->isRigidBody();

	   rigidbody->create_control(control_raw);

	// exp

	app->transmit_scenes(c);

	// exp

	neb::network::control::rigid_body::create control_create;
	control_create.get_addr()->load_this(rigidbody);

	sp::shared_ptr<gal::net::message> msg(new gal::net::message);

	msg->write(glutpp::network::type::CONTROL_CREATE);
	control_create.write(msg);

	c->write(msg);

	// exp
	 */
}
void		neb::Network::Server::write(sp::shared_ptr< gal::net::omessage > omessage) {
	/** @todo impl */
}



