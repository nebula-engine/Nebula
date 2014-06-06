
#include <Nebula/debug.hh>
#include <Nebula/Shape/Base.hh>
#include <Nebula/Actor/RigidStatic/Base.hh>

Neb::Actor::RigidStatic::Base::Base() {
}
Neb::Actor::RigidStatic::Base::Base(Neb::Actor::Util::Parent_s parent):
		Neb::Actor::RigidActor::Base(parent)
{
	NEBULA_ACTOR_BASE_FUNC
}
void		Neb::Actor::RigidStatic::Base::init() {
	NEBULA_ACTOR_BASE_FUNC
}
void		Neb::Actor::RigidStatic::Base::step(Neb::Core::TimeStep const & ts) {
	NEBULA_ACTOR_BASE_FUNC;
}

