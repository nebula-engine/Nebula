
#include <PhysX/core/actor/actor/local.hpp>

phx::core::actor::actor::local::local(sp::shared_ptr<phx::core::actor::util::parent> parent):
	neb::core::actor::base(parent),
	neb::core::actor::actor::base(parent),
	neb::core::actor::local(parent),
	neb::core::actor::actor::local(parent),
	phx::core::actor::base(parent),
	phx::core::actor::local(parent),
	phx::core::actor::actor::base(parent)
{}
void		phx::core::actor::actor::local::init() {
	
	neb::core::actor::actor::local::init();
	phx::core::actor::actor::base::init();
	
}
/*void		phx::core::actor::actor::local::release() {

	neb::core::actor::actor::local::release();
	phx::core::actor::actor::base::release();

	if(px_actor_) {
		px_actor_->release();
		px_actor_ = NULL;
	}
}*/
void		phx::core::actor::actor::local::step(gal::std::timestep const & ts) {
	
	neb::core::actor::actor::local::step(ts);
	phx::core::actor::actor::base::step(ts);


}

