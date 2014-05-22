#include <Nebula/App/Base.hh>

#include <Nebula/Actor/RigidBody/Remote.hh>

#include <Nebula/Message/Actor/Control.hh>

void		Neb::Actor::RigidBody::Remote::step(double const & time, double const & dt) {

	Neb::Actor::RigidBody::Base::step(time, dt);
	Neb::Actor::RigidActor::Remote::step(time, dt);


	auto app = Neb::App::Base::globalBase();
	
	gal::network::omessage_s msg;

	Neb::Message::Actor::Control::RigidBody::OUpdate_s control_update;
	
	
	if(control_) {
		msg.reset(new gal::network::omessage);
		control_update.reset(new Neb::Message::Actor::Control::RigidBody::OUpdate);
		
		control_update->i_ = i_;
		control_update->control_.ptr_ = control_;
		
		control_update->serialize(msg->ar_, 0);
		
		app->send_client(msg);
	}
}




