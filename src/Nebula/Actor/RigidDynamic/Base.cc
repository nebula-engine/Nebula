#include <Nebula/debug.hh>
#include <Nebula/Shape/Base.hh>
#include <Nebula/Actor/RigidDynamic/Base.hh>

neb::core::actor::rigiddynamic::Base::Base() {
}
neb::core::actor::rigiddynamic::Base::Base(sp::shared_ptr<neb::core::actor::Util::Parent> parent):
	neb::core::actor::RigidBody::Base(parent)
{
	NEBULA_ACTOR_BASE_FUNC;
}
void		neb::core::actor::rigiddynamic::Base::init() {
	NEBULA_ACTOR_BASE_FUNC;

	neb::core::actor::RigidBody::Base::init();
	
}

