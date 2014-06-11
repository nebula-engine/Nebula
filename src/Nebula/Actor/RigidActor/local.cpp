

#include <Nebula/Actor/RigidActor/Local.hh>

void		Neb::Actor::RigidActor::Local::step(Neb::Core::TimeStep const & ts) {
	Neb::Actor::Actor::Local::step(ts);
	Neb::Actor::RigidActor::Base::step(ts);
}


