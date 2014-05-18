#include <Nebula/Message/Actor/Control.hh>

void		Neb::Message::Actor::Control::RigidBody::Update::process() {

	auto actor = get_actor(control_update.get_addr());
	
	auto rigidbody = actor->isRigidBody();

	if(rigidbody) {
		auto control = rigidbody->control_;
		if(control) {
			control->raw_ = *(control_update.get_raw());

			control->print();
		} else {
			printf("control not found\n");
		}
	} else {
		printf("actor not found\n");
	}
}

