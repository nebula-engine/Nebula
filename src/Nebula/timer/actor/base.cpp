
#include <Nebula/app/Base.hh>
#include <Nebula/timer/Actor/Base.hpp>
#include <Nebula/core/actor/Base.hh>


neb::Timer::actor::base::base(sp::shared_ptr<neb::core::actor::base> actor, double seconds):
	timer_(neb::app::base::global()->ios_, boost::posix_time::seconds(seconds)),
	actor_(actor)
{
	timer_.async_wait(boost::bind(&neb::Timer::actor::base::doSomething, this));
}




