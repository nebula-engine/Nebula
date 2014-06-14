#include <Nebula/App/Base.hh>

//#include <PhysX/core/actor/rigidbody/Remote.hh>
#include <PhysX/message/actor/control/rigidbody/update.hpp>
/*
void		px::core::actor::rigidbody::remote::step(neb::core::TimeStep const & ts) {
	
	neb::core::actor::rigidactor::Remote::step(ts);
	neb::core::actor::rigidbody::base::step(ts);

	auto app = neb::App::base::global();
	
	if(control_) {
		auto message = std::make_shared<px::message::actor::control::rigidbody::oupdate>();
		
		message->index_ = i_;
		message->control_.ptr_ = control_;
		
		app->sendClient(message);
	}
}


*/

