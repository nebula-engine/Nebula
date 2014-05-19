#include <Nebula/Actor/RigidBody/Local.hh>
#include <Nebula/Actor/Control/RigidBody/Base.hh>

void		Neb::Actor::RigidBody::Local::step(double const & time, double const & dt) {
	
	Neb::Actor::RigidBody::Base::step(time, dt);
	Neb::Actor::RigidActor::Local::step(time, dt);
	
	/** @todo was step_local */
	control_->step(time, dt);
	
	add_force(dt);
}


