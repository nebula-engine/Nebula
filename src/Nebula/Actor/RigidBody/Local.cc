#include <Nebula/Actor/RigidBody/Local.hh>

void		neb::core::actor::RigidBody::local::step(neb::core::TimeStep const & ts) {
	neb::core::actor::RigidBody::Base::step(ts);
	neb::core::actor::RigidActor::local::step(ts);
}


