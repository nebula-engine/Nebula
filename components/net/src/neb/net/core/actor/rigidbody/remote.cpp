#include <neb/app/Base.hh>

//#include <PhysX/core/actor/rigidbody/Remote.hh>
#include <PhysX/message/actor/control/rigidbody/update.hpp>
/*
void		phx::core::actor::rigidbody::remote::step(gal::etc::timestep const & ts) {
	
	neb::core::actor::rigidactor::remote::step(ts);
	neb::core::actor::rigidbody::base::step(ts);

	auto app = neb::app::base::global();
	
	if(control_) {
		auto message = std::make_shared<phx::message::actor::control::rigidbody::oupdate>();
		
		message->index_ = i_;
		message->control_.ptr_ = control_;
		
		app->sendClient(message);
	}
}


*/

