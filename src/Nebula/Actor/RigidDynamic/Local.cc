#include <Nebula/Actor/RigidDynamic/Local.hh>

neb::core::actor::rigiddynamic::local::local() {
}
neb::core::actor::rigiddynamic::local::local(sp::shared_ptr<neb::core::actor::Util::Parent>) {
}
void				neb::core::actor::rigiddynamic::local::init() {
	neb::core::actor::RigidBody::local::init();
	neb::core::actor::rigiddynamic::Base::init();
}
void				neb::core::actor::rigiddynamic::local::release() {
	neb::core::actor::RigidBody::local::release();
	neb::core::actor::rigiddynamic::Base::release();
}
void				neb::core::actor::rigiddynamic::local::step(neb::core::TimeStep const & ts) {
	neb::core::actor::RigidBody::local::step(ts);
	neb::core::actor::rigiddynamic::Base::step(ts);
}


