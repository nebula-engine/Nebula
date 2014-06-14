
#include <Nebula/debug.hh>
#include <Nebula/Shape/Base.hh>
#include <Nebula/Actor/RigidStatic/Base.hh>

neb::core::actor::RigidStatic::Base::Base() {
}
neb::core::actor::RigidStatic::Base::Base(sp::shared_ptr<neb::core::actor::Util::Parent> parent):
		neb::core::actor::rigidactor::Base(parent)
{
	NEBULA_ACTOR_BASE_FUNC
}
void		neb::core::actor::RigidStatic::Base::init() {
	NEBULA_ACTOR_BASE_FUNC
}
void		neb::core::actor::RigidStatic::Base::step(neb::core::TimeStep const & ts) {
	NEBULA_ACTOR_BASE_FUNC;
}

