
#include <Nebula/app/Base.hh>
#include <Nebula/timer/Actor/Release.hpp>
#include <Nebula/core/actor/Base.hh>


neb::Timer::actor::Release::Release(sp::shared_ptr<neb::core::actor::base> actor, double seconds):
	neb::Timer::actor::base::base(actor, seconds)
{
}
void		neb::Timer::actor::Release::doSomething() {
	assert(actor_);
	
	auto parent = actor_->parent_.lock();
	assert(parent);
	
	parent->erase(actor_->i_);
	
}



