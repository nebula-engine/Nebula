
#include <Nebula/App/Base.hh>
#include <Nebula/timer/Actor/Base.hpp>
#include <Nebula/Actor/Base.hh>


neb::Timer::actor::Base::Base(sp::shared_ptr<neb::core::actor::Base> actor, double seconds):
	timer_(neb::App::Base::global()->ios_, boost::posix_time::seconds(seconds)),
	actor_(actor)
{
	timer_.async_wait(boost::bind(&neb::Timer::actor::Base::doSomething, this));
}





