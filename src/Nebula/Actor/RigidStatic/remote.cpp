
#include <Nebula/Actor/RigidStatic/remote.hpp>

	
neb::core::actor::rigidstatic::remote::remote(sp::shared_ptr<neb::core::actor::util::parent> parent):
		neb::core::actor::base(parent),
		neb::core::actor::actor::base(parent),
		neb::core::actor::rigidactor::base(parent),
		neb::core::actor::remote(parent),
		neb::core::actor::actor::remote(parent),
		neb::core::actor::rigidactor::remote(parent),
		neb::core::actor::rigidstatic::base(parent)
{
	//NEBULA_ACTOR_BASE_FUNC
}
void		neb::core::actor::rigidstatic::remote::init() {
	//NEBULA_ACTOR_BASE_FUNC
}
void		neb::core::actor::rigidstatic::remote::release() {
	//NEBULA_ACTOR_BASE_FUNC
}
void		neb::core::actor::rigidstatic::remote::step(neb::core::TimeStep const & ts) {
	//NEBULA_ACTOR_BASE_FUNC;
}

