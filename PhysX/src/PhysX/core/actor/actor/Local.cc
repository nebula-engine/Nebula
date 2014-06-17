
#include <PhysX/core/actor/actor/local.hpp>

phx::core::actor::actor::local::local(sp::shared_ptr<phx::core::actor::util::parent> parent):
	neb::core::actor::base(parent),
	neb::core::actor::local(parent),
	neb::core::actor::actor::base(parent),
	neb::core::actor::actor::local(parent)
	phx::core::actor::base(parent),
	phx::core::actor::local(parent),
	phx::core::actor::actor::base(parent)
{}
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

