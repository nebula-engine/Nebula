#include <assert.h>

#include <nebula/app.hpp>
#include <nebula/scene/scene.hpp>
#include <nebula/network/message.hpp>
#include <nebula/network/server.hpp>

neb::network::server::server(neb::app_s app, unsigned short port, int len):
	gal::network::server(port, len),
	app_(app)
{
}
void neb::network::server::callback_accept(int s) {
	NEBULA_DEBUG_0_FUNCTION;
	
	assert(!app_.expired());
	auto app = app_.lock();

	std::shared_ptr<neb::network::communicating> c(new neb::network::communicating(app, s));
	c->start();
	
	
	// exp
	neb::control::rigid_body::raw_s control_raw(new neb::control::rigid_body::raw);
	
	auto scene = app->get_scene(0);
	assert(scene);
	
	glutpp::actor::desc_s ad = scene->actors_deferred_[(char*)"player0"];
        assert(ad);
	
        auto actor = app->scenes_[0]->create_actor_local(ad);
        auto rigidbody = actor->to_rigid_body();
	
	rigidbody->create_control(control_raw);
	
	// exp
	
	app->transmit_scenes(c);
	
	// exp

	neb::network::control::rigid_body::create control_create;
	control_create.get_addr()->load_this(rigidbody);
	
	gal::network::message_s msg(new gal::network::message);
	
	msg->write(glutpp::network::type::CONTROL_CREATE);
	control_create.write(msg);
	
	c->write(msg);
	
	// exp
	
	clients_.push_back(c);
}




