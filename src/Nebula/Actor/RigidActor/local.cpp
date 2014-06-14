

#include <Nebula/Actor/RigidActor/Local.hh>

void		neb::core::actor::RigidActor::local::step(neb::core::TimeStep const & ts) {
	neb::core::actor::actor::local::step(ts);
	neb::core::actor::RigidActor::Base::step(ts);
}


