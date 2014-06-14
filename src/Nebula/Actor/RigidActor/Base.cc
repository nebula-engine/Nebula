
#include <Nebula/debug.hh>
#include <Nebula/Actor/RigidActor/Base.hh>

neb::core::actor::rigidactor::base::base() {
}
neb::core::actor::rigidactor::base::base(sp::shared_ptr<neb::core::actor::util::parent> parent): neb::core::actor::actor::base(parent) {
}
void		neb::core::actor::rigidactor::base::init() {
	neb::core::actor::actor::base::init();
}
void		neb::core::actor::rigidactor::base::release() {
	neb::core::actor::actor::base::release();
}
void		neb::core::actor::rigidactor::base::step(neb::core::TimeStep const & ts) {
	neb::core::actor::actor::base::step(ts);
}



