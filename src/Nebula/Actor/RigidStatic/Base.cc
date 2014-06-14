
#include <Nebula/debug.hh>
#include <Nebula/Shape/Base.hh>
#include <Nebula/Actor/RigidStatic/Base.hh>

neb::core::actor::RigidStatic::base::base() {
}
neb::core::actor::RigidStatic::base::base(sp::shared_ptr<neb::core::actor::util::parent> parent):
		neb::core::actor::rigidactor::base(parent)
{
	NEBULA_ACTOR_BASE_FUNC
}
void		neb::core::actor::RigidStatic::base::init() {
	NEBULA_ACTOR_BASE_FUNC
}
void		neb::core::actor::RigidStatic::base::step(neb::core::TimeStep const & ts) {
	NEBULA_ACTOR_BASE_FUNC;
}

