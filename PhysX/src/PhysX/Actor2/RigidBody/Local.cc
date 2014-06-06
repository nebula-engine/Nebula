#include <Nebula/Actor/RigidBody/Local.hh>

void		Neb::Actor::RigidBody::Local::step(Neb::Core::TimeStep const & ts) {
	Neb::Actor::RigidBody::Base::step(ts);
	Neb::Actor::RigidActor::Local::step(ts);
}


