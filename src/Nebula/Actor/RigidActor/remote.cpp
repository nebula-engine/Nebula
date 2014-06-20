

#include <Nebula/core/actor/RigidActor/Remote.hh>

neb::core::actor::rigidactor::remote::remote(sp::shared_ptr<neb::core::actor::util::parent> parent):
	neb::core::actor::base(parent),
	neb::core::actor::actor::base(parent),
	neb::core::actor::rigidactor::base(parent),
	neb::core::actor::remote(parent),
	neb::core::actor::actor::remote(parent)
{
}
void		neb::core::actor::rigidactor::remote::step(neb::core::TimeStep const & ts) {
	neb::core::actor::actor::remote::step(ts);
	neb::core::actor::rigidactor::base::step(ts);
}


