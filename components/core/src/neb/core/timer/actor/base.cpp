#include <gal/log/log.hpp>

#include <neb/core/timer/Actor/Base.hpp>
#include <neb/core/core/actor/base.hpp>
#include <neb/core/util/debug.hpp>
#include <neb/core/util/log.hpp>

#include <neb/core/app/__base.hpp>


neb::Timer::actor::base::base(std::shared_ptr<neb::core::core::actor::base> actor, double seconds):
	timer_(neb::core::app::__base::global()->ios_, boost::posix_time::seconds(seconds)),
	actor_(actor)
{
	LOG(lg, neb::core::sl, debug) << __PRETTY_FUNCTION__;

	assert(!neb::core::app::__base::global()->ios_.stopped());
	
	// cannot do this: shared_from_this shouldnt be used in ctor??
	
	//timer_.async_wait(boost::bind(&neb::Timer::actor::base::doSomething, shared_from_this()));

}
neb::Timer::actor::base::~base() {
	LOG(lg, neb::core::sl, debug) << __PRETTY_FUNCTION__;
	
}
void		neb::Timer::actor::base::activate()
{
	LOG(lg, neb::core::sl, debug) << __PRETTY_FUNCTION__;

	timer_.async_wait(boost::bind(&neb::Timer::actor::base::doSomething, shared_from_this()));
}



