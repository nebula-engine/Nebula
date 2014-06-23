#include <gal/log/log.hpp>

#include <Nebula/app/Base.hh>
#include <Nebula/timer/Actor/Base.hpp>
#include <Nebula/core/actor/Base.hh>


neb::Timer::actor::base::base(sp::shared_ptr<neb::core::actor::base> actor, double seconds):
	timer_(neb::app::base::global()->ios_, boost::posix_time::seconds(seconds)),
	actor_(actor)
{
	BOOST_LOG_CHANNEL_SEV(lg, "neb timer", debug) << __PRETTY_FUNCTION__;

	assert(!neb::app::base::global()->ios_.stopped());
	
	// cannot do this: shared_from_this shouldnt be used in ctor??
	
	//timer_.async_wait(boost::bind(&neb::Timer::actor::base::doSomething, shared_from_this()));

}
neb::Timer::actor::base::~base() {
	BOOST_LOG_CHANNEL_SEV(lg, "neb timer", debug) << __PRETTY_FUNCTION__;
	
}
void		neb::Timer::actor::base::activate() {
	BOOST_LOG_CHANNEL_SEV(lg, "neb timer", debug) << __PRETTY_FUNCTION__;
	
	timer_.async_wait(boost::bind(&neb::Timer::actor::base::doSomething, shared_from_this()));
	
}



