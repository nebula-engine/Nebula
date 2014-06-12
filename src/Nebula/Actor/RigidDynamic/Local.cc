#include <Nebula/Actor/RigidDynamic/Local.hh>

neb::core::actor::RigidDynamic::Local::Local() {
}
neb::core::actor::RigidDynamic::Local::Local(sp::shared_ptr<neb::core::actor::Util::Parent>) {
}
void				neb::core::actor::RigidDynamic::Local::init() {
	neb::core::actor::RigidBody::Local::init();
	neb::core::actor::RigidDynamic::Base::init();
}
void				neb::core::actor::RigidDynamic::Local::release() {
	neb::core::actor::RigidBody::Local::release();
	neb::core::actor::RigidDynamic::Base::release();
}
void				neb::core::actor::RigidDynamic::Local::step(neb::core::TimeStep const & ts) {
	neb::core::actor::RigidBody::Local::step(ts);
	neb::core::actor::RigidDynamic::Base::step(ts);
}


