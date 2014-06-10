#include <Nebula/App/Base.hh>

#include <Nebula/Actor/RigidBody/Remote.hh>

void		Neb::Actor::RigidBody::Remote::step(Neb::Core::TimeStep const & ts) {
	Neb::Actor::RigidActor::Remote::step(ts);
	Neb::Actor::RigidBody::Base::step(ts);
}




