#include <Nebula/debug.hh>
#include <Nebula/Shape/Base.hh>
#include <Nebula/Actor/RigidDynamic/Base.hh>

neb::core::actor::rigiddynamic::base::base() {
}
neb::core::actor::rigiddynamic::base::base(sp::shared_ptr<neb::core::actor::util::parent> parent):
	neb::core::actor::rigidbody::base(parent)
{
	NEBULA_ACTOR_BASE_FUNC;
}
void		neb::core::actor::rigiddynamic::base::init() {
	NEBULA_ACTOR_BASE_FUNC;

	neb::core::actor::rigidbody::base::init();
	
}

