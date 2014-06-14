

#include <Nebula/Actor/RigidActor/Local.hh>

void		neb::core::actor::rigidactor::local::step(neb::core::TimeStep const & ts) {
	neb::core::actor::actor::local::step(ts);
	neb::core::actor::rigidactor::Base::step(ts);
}


