#include <PhysX/core/actor/rigidbody/local.hpp>

void		phx::core::actor::rigidbody::local::step(neb::core::TimeStep const & ts) {
	neb::core::actor::rigidbody::base::step(ts);
	neb::core::actor::rigidactor::local::step(ts);
}


