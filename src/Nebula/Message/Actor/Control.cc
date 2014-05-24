
#include <Nebula/Actor/RigidBody/Base.hh>
#include <Nebula/Actor/Control/RigidBody/Base.hh>

#include <Nebula/Message/Actor/Control.hh>

void		Neb::Message::Actor::Control::RigidBody::IUpdate::process() {

	//auto actor = get_actor(control_update.get_addr());
	
	auto actor = std::dynamic_pointer_cast<Neb::Actor::Base>(Neb::Util::Shared::registry_.get(i_));
	
	auto rigidbody = actor->isActorRigidBody();

	if(rigidbody) {
		auto control = rigidbody->control_;
		if(control) {
			control->operator=(*control_.ptr_);
		} else {
			printf("control not found\n");
		}
	} else {
		printf("actor not found\n");
	}
}




