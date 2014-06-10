
#include <Nebula/debug.hh>
#include <Nebula/Actor/RigidActor/Base.hh>

Neb::Actor::RigidActor::Base::Base() {
}
Neb::Actor::RigidActor::Base::Base(Neb::Actor::Util::Parent_s parent): Neb::Actor::Actor::Base(parent) {
}
void		Neb::Actor::RigidActor::Base::init() {
	Neb::Actor::Actor::Base::init();
}
void		Neb::Actor::RigidActor::Base::release() {
	Neb::Actor::Actor::Base::release();
}
void		Neb::Actor::RigidActor::Base::step(Neb::Core::TimeStep const & ts) {
	Neb::Actor::Actor::Base::step(ts);
}



