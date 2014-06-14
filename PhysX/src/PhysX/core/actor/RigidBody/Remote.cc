#include <Nebula/App/Base.hh>

#include <Nebula/Actor/RigidBody/Remote.hh>

#include <Nebula/Message/Actor/Control.hh>

void		neb::core::actor::RigidBody::Remote::step(neb::core::TimeStep const & ts) {
	neb::core::actor::RigidActor::Remote::step(ts);
	neb::core::actor::RigidBody::Base::step(ts);

	auto app = neb::App::Base::globalBase();
	
	if(control_) {
		auto message = std::make_shared<neb::message::actor::Control::RigidBody::OUpdate>();
		
		message->index_ = i_;
		message->control_.ptr_ = control_;
		
		app->sendClient(message);
	}
}




