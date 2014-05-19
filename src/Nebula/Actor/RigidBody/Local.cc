#include <Nebula/Actor/RigidBody/Local.hh>
#include <Nebula/Actor/Control/RigidBody/Base.hh>

void		Neb::Actor::RigidBody::Local::step(double dt) {
	
	Neb::Actor::RigidBody::Base::step(dt);
	Neb::Actor::RigidActor::Local::step(dt);
	
	/** @todo was step_local */
	control_->step(dt);
	
	add_force(dt);
}


