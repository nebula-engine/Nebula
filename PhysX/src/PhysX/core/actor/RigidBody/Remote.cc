#include <Nebula/App/Base.hh>

#include <Nebula/Actor/RigidBody/Remote.hh>

#include <Nebula/Message/Actor/Control.hh>

void		neb::Actor::RigidBody::Remote::step(neb::core::TimeStep const & ts) {
	neb::Actor::RigidActor::Remote::step(ts);
	neb::Actor::RigidBody::Base::step(ts);

	auto app = neb::App::Base::globalBase();
	
	if(control_) {
		auto message = std::make_shared<neb::Message::Actor::Control::RigidBody::OUpdate>();
		
		message->index_ = i_;
		message->control_.ptr_ = control_;
		
		app->sendClient(message);
	}
}




