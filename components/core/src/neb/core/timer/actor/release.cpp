#include <gal/log/log.hpp>

#include <neb/core/timer/Actor/Release.hpp>
#include <neb/core/core/actor/base.hpp>
#include <neb/core/util/debug.hpp>
#include <neb/core/util/log.hpp>


neb::Timer::actor::Release::Release(
		shared_ptr<neb::core::core::actor::base> actor, double seconds):
	neb::Timer::actor::base::base(actor, seconds)
{
	LOG(lg, neb::core::sl, debug) << __PRETTY_FUNCTION__;

}
void		neb::Timer::actor::Release::doSomething() {
	
	LOG(lg, neb::core::sl, debug) << __PRETTY_FUNCTION__;
	
	auto actor(actor_.lock());
	
	// actor was released after timer start
	if(!actor) return;
	
	auto parent = actor->parent_.lock();
	assert(parent);
	
	parent->erase(actor->i_);
}



