#include <gal/log/log.hpp>

#include <Nebula/app/Base.hh>
#include <Nebula/timer/Actor/Release.hpp>
#include <Nebula/core/actor/Base.hh>
#include <Nebula/debug.hh>


neb::Timer::actor::Release::Release(sp::shared_ptr<neb::core::actor::base> actor, double seconds):
	neb::Timer::actor::base::base(actor, seconds)
{
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb timer", debug) << __PRETTY_FUNCTION__;

}
void		neb::Timer::actor::Release::doSomething() {
	
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb timer", debug) << __PRETTY_FUNCTION__;
	
	auto actor(actor_.lock());
	
	// actor was released after timer start
	if(!actor) return;
	
	auto parent = actor->parent_.lock();
	assert(parent);
	
	parent->erase(actor->i_);
	
}



