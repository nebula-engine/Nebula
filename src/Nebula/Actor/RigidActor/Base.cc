
#include <Nebula/debug.hh>
#include <Nebula/Actor/RigidActor/Base.hh>

neb::core::actor::RigidActor::Base::Base() {
}
neb::core::actor::RigidActor::Base::Base(sp::shared_ptr<neb::core::actor::Util::Parent> parent): neb::core::actor::actor::Base(parent) {
}
void		neb::core::actor::RigidActor::Base::init() {
	neb::core::actor::actor::Base::init();
}
void		neb::core::actor::RigidActor::Base::release() {
	neb::core::actor::actor::Base::release();
}
void		neb::core::actor::RigidActor::Base::step(neb::core::TimeStep const & ts) {
	neb::core::actor::actor::Base::step(ts);
}



