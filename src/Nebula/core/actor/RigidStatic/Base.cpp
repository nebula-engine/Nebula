
#include <Nebula/debug.hh>
#include <Nebula/core/shape/Base.hh>
#include <Nebula/core/actor/RigidStatic/Base.hh>

	
neb::core::actor::rigidstatic::base::base(sp::shared_ptr<neb::core::actor::util::parent> parent):
		neb::core::actor::base(parent),
		neb::core::actor::actor::base(parent),
		neb::core::actor::rigidactor::base(parent)
{
	NEBULA_ACTOR_BASE_FUNC
}
void		neb::core::actor::rigidstatic::base::init() {
	NEBULA_ACTOR_BASE_FUNC
}
void		neb::core::actor::rigidstatic::base::step(neb::core::TimeStep const & ts) {
	NEBULA_ACTOR_BASE_FUNC;
}

