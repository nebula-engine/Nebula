#include <Nebula/Actor/RigidBody/Local.hh>

void		neb::core::actor::rigidbody::local::step(neb::core::TimeStep const & ts) {
	neb::core::actor::rigidbody::Base::step(ts);
	neb::core::actor::rigidactor::local::step(ts);
}


