#include <Nebula/debug.hh>
#include <Nebula/Shape/Base.hh>
#include <Nebula/Actor/RigidDynamic/Base.hh>

Neb::Actor::RigidDynamic::Base::Base() {
}
Neb::Actor::RigidDynamic::Base::Base(Neb::Actor::Util::Parent_s parent):
	Neb::Actor::RigidBody::Base(parent)
{
	NEBULA_ACTOR_BASE_FUNC;
}
void		Neb::Actor::RigidDynamic::Base::init() {
	NEBULA_ACTOR_BASE_FUNC;

	Neb::Actor::RigidBody::Base::init();
	
}

