#include <Nebula/App/Base.hh>

#include <Nebula/Actor/RigidBody/Remote.hh>

void		neb::core::actor::rigidbody::Remote::step(neb::core::TimeStep const & ts) {
	neb::core::actor::rigidactor::Remote::step(ts);
	neb::core::actor::rigidbody::Base::step(ts);
}




