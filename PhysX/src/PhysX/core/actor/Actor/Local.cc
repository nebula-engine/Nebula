#include <Nebula/debug.hh>

#include <Nebula/Actor/Actor/Local.hh>

void		neb::Actor::Actor::Local::release() {

	if(px_actor_) {
		px_actor_->release();
		px_actor_ = NULL;
	}
}
void		px::Actor::Actor::Local::step(neb::core::TimeStep const & ts) {
	
	neb::Actor::Actor::Local::step(ts);
	px::Actor::Actor::Base::step(ts);


}

