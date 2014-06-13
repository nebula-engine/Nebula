#include <Nebula/Actor/RigidBody/Local.hh>

void		neb::Actor::RigidBody::Local::step(neb::core::TimeStep const & ts) {
	neb::Actor::RigidBody::Base::step(ts);
	neb::Actor::RigidActor::Local::step(ts);
}


