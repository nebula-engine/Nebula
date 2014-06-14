#include <Nebula/App/Base.hh>

#include <Nebula/Actor/RigidBody/Remote.hh>

#include <PhysX/message/actor/control/rigidbody/update.hpp>

void		neb::core::actor::rigidbody::Remote::step(neb::core::TimeStep const & ts) {
	neb::core::actor::rigidactor::Remote::step(ts);
	neb::core::actor::rigidbody::Base::step(ts);

	auto app = neb::App::Base::global();
	
	if(control_) {
		auto message = std::make_shared<px::message::actor::control::rigidbody::oupdate>();
		
		message->index_ = i_;
		message->control_.ptr_ = control_;
		
		app->sendClient(message);
	}
}




