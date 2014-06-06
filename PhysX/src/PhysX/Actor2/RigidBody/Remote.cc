#include <Nebula/App/Base.hh>

#include <Nebula/Actor/RigidBody/Remote.hh>

#include <Nebula/Message/Actor/Control.hh>

void		Neb::Actor::RigidBody::Remote::step(Neb::Core::TimeStep const & ts) {
	Neb::Actor::RigidActor::Remote::step(ts);
	Neb::Actor::RigidBody::Base::step(ts);

	auto app = Neb::App::Base::globalBase();
	
	if(control_) {
		auto message = std::make_shared<Neb::Message::Actor::Control::RigidBody::OUpdate>();
		
		message->index_ = i_;
		message->control_.ptr_ = control_;
		
		app->sendClient(message);
	}
}




