#include <Nebula/App/Base.hh>

#include <Nebula/Actor/RigidBody/Remote.hh>

void		neb::core::actor::RigidBody::Remote::step(neb::core::TimeStep const & ts) {
	neb::core::actor::RigidActor::Remote::step(ts);
	neb::core::actor::RigidBody::Base::step(ts);
}




