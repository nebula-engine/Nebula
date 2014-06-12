

#include <Nebula/Actor/RigidActor/Local.hh>

void		neb::core::actor::RigidActor::Local::step(neb::core::TimeStep const & ts) {
	neb::core::actor::actor::Local::step(ts);
	neb::core::actor::RigidActor::Base::step(ts);
}


