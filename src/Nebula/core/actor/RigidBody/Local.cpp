#include <Nebula/core/actor/RigidBody/Local.hh>

neb::core::actor::rigidbody::local::local(sp::shared_ptr<neb::core::actor::util::parent> parent):
	neb::core::actor::base(parent),
	neb::core::actor::actor::base(parent),
	neb::core::actor::rigidactor::base(parent),
	neb::core::actor::local(parent),
	neb::core::actor::actor::local(parent),
	neb::core::actor::rigidactor::local(parent),
	neb::core::actor::rigidbody::base(parent)
{
}
void		neb::core::actor::rigidbody::local::step(gal::std::timestep const & ts) {
	neb::core::actor::rigidbody::base::step(ts);
	neb::core::actor::rigidactor::local::step(ts);
}


