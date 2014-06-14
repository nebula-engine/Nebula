
#include <Nebula/App/Base.hh>
#include <Nebula/timer/Actor/Base.hpp>
#include <Nebula/Actor/Base.hh>


neb::Timer::actor::base::base(sp::shared_ptr<neb::core::actor::base> actor, double seconds):
	timer_(neb::App::base::global()->ios_, boost::posix_time::seconds(seconds)),
	actor_(actor)
{
	timer_.async_wait(boost::bind(&neb::Timer::actor::base::doSomething, this));
}





