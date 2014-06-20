#include <Nebula/debug.hh>
#include <Nebula/core/shape/Base.hh>
#include <Nebula/core/actor/RigidDynamic/Base.hh>

//neb::core::actor::rigiddynamic::base::base() {
//}

neb::core::actor::rigiddynamic::base::base(sp::shared_ptr<neb::core::actor::util::parent> parent):
	neb::core::actor::base(parent),
	neb::core::actor::actor::base(parent),
	neb::core::actor::rigidactor::base(parent),
	neb::core::actor::rigidbody::base(parent)
{
	NEBULA_ACTOR_BASE_FUNC;
}
void		neb::core::actor::rigiddynamic::base::init() {
	NEBULA_ACTOR_BASE_FUNC;

	neb::core::actor::rigidbody::base::init();
	
}

