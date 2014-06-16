
#include <PhysX/core/actor/actor/local.hpp>

void		phx::core::actor::actor::local::release() {

	if(px_actor_) {
		px_actor_->release();
		px_actor_ = NULL;
	}
}
void		phx::core::actor::actor::local::step(neb::core::TimeStep const & ts) {
	
	neb::core::actor::actor::local::step(ts);
	phx::core::actor::actor::base::step(ts);


}

