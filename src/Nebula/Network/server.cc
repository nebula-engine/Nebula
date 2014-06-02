#include <assert.h>

#include <Nebula/App/Base.hh>
#include <Nebula/Scene/Base.hh>
#include <Nebula/network/message.hh>
#include <Nebula/network2/server.hh>

Neb::Network::Server::Server(unsigned short port, int len):
	gal::network::server(port, len)
{
}
void Neb::Network::Server::callback_accept(int s) {
	//NEBULA_DEBUG_0_FUNCTION;
	
	

	auto c = std::make_shared<Neb::Network::Communicating>(s);
	c->start();
	
	
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
	
	gal::network::message_s msg(new gal::network::message);
	
	msg->write(glutpp::network::type::CONTROL_CREATE);
	control_create.write(msg);
	
	c->write(msg);
	
	// exp
	*/
	clients_.push_back(c);
}




