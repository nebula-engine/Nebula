

#include <Nebula/core/actor/RigidActor/Local.hh>

neb::core::actor::rigidactor::local::local(sp::shared_ptr<neb::core::actor::util::parent> parent):
	neb::core::actor::base(parent),
	neb::core::actor::actor::base(parent),
	neb::core::actor::rigidactor::base(parent),
	neb::core::actor::local(parent),
	neb::core::actor::actor::local(parent)
{
}
void		neb::core::actor::rigidactor::local::step(gal::std::timestep const & ts) {
	neb::core::actor::actor::local::step(ts);
	neb::core::actor::rigidactor::base::step(ts);
}


