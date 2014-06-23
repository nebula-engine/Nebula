
#include <Nebula/debug.hh>
#include <Nebula/core/shape/Base.hh>
#include <Nebula/core/actor/RigidStatic/local.hpp>

	
neb::core::actor::rigidstatic::local::local(sp::shared_ptr<neb::core::actor::util::parent> parent):
		neb::core::actor::base(parent),
		neb::core::actor::actor::base(parent),
		neb::core::actor::rigidactor::base(parent),
		neb::core::actor::local(parent),
		neb::core::actor::actor::local(parent),
		neb::core::actor::rigidactor::local(parent),
		neb::core::actor::rigidstatic::base(parent)
{
	NEBULA_ACTOR_BASE_FUNC
}
void		neb::core::actor::rigidstatic::local::init() {
	NEBULA_ACTOR_BASE_FUNC
}
void		neb::core::actor::rigidstatic::local::release() {
	NEBULA_ACTOR_BASE_FUNC
}
void		neb::core::actor::rigidstatic::local::step(gal::std::timestep const & ts) {
	NEBULA_ACTOR_BASE_FUNC;
}

