#include <Nebula/App/Base.hh>

#include <Nebula/Actor/RigidBody/Remote.hh>

#include <Nebula/Message/Actor/Control.hh>

void		Neb::Actor::RigidBody::Remote::step(double const & time, double const & dt) {

	auto app = Neb::App::Base::globalBase();
	
	if(control_) {
		auto message = std::make_shared<Neb::Message::Actor::Control::RigidBody::OUpdate>();
		
		message->i_ = i_;
		message->control_.ptr_ = control_;
		
		app->sendClient(message);
	}
}




