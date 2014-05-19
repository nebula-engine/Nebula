#include <Nebula/App/Base.hh>

#include <Nebula/Actor/RigidBody/Remote.hh>

#include <Nebula/Message/Actor/Control.hh>

void		Neb::Actor::RigidBody::Remote::stepRigidBodyDerived(double time) {

	auto app = Neb::App::Base::globalBase();
	
	gal::network::omessage_s msg;

	Neb::Message::Actor::Control::RigidBody::OUpdate_s control_update;
	
	
	if(control_) {
		msg.reset(new gal::network::omessage);
		control_update.reset(new Neb::Message::Actor::Control::RigidBody::OUpdate);
		
		control_update->addr_.load_this(isActorBase());
		control_update->control_.ptr_ = control_;
		
		control_update->serialize(msg->ar_, 0);
		
		app->send_client(msg);
	}
}




