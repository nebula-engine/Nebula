#include <PhysX/core/actor/rigidbody/local.hpp>


phx::core::actor::rigidbody::local::local(sp::shared_ptr<phx::core::actor::util::parent> parent):
	neb::core::actor::base(parent),
	neb::core::actor::actor::base(parent),
	neb::core::actor::rigidactor::base(parent),
	neb::core::actor::rigidbody::base(parent),
	neb::core::actor::local(parent),
	neb::core::actor::actor::local(parent),
	neb::core::actor::rigidactor::local(parent),
	neb::core::actor::rigidbody::local(parent),
	phx::core::actor::base(parent),
	phx::core::actor::actor::base(parent),
	phx::core::actor::rigidactor::base(parent),
	phx::core::actor::local(parent),
	phx::core::actor::actor::local(parent),
	phx::core::actor::rigidactor::local(parent)
{}
void		phx::core::actor::rigidbody::local::step(neb::core::TimeStep const & ts) {
	neb::core::actor::rigidbody::base::step(ts);
	neb::core::actor::rigidactor::local::step(ts);
}


