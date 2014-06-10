#include <Nebula/Actor/RigidDynamic/Local.hh>

Neb::Actor::RigidDynamic::Local::Local() {
}
Neb::Actor::RigidDynamic::Local::Local(Neb::Actor::Util::Parent_s) {
}
void				Neb::Actor::RigidDynamic::Local::init() {
	Neb::Actor::RigidBody::Local::init();
	Neb::Actor::RigidDynamic::Base::init();
}
void				Neb::Actor::RigidDynamic::Local::release() {
	Neb::Actor::RigidBody::Local::release();
	Neb::Actor::RigidDynamic::Base::release();
}
void				Neb::Actor::RigidDynamic::Local::step(Neb::Core::TimeStep const & ts) {
	Neb::Actor::RigidBody::Local::step(ts);
	Neb::Actor::RigidDynamic::Base::step(ts);
}


