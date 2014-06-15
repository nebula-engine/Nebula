#include <Nebula/debug.hh>

#include <Nebula/Actor/Actor/Local.hh>

void		neb::core::actor::actor::local::release() {

	if(px_actor_) {
		px_actor_->release();
		px_actor_ = NULL;
	}
}
void		phx::actor::actor::local::step(neb::core::TimeStep const & ts) {
	
	neb::core::actor::actor::local::step(ts);
	phx::actor::actor::base::step(ts);


}

