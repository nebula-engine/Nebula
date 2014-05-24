
#include <Nebula/App/Base.hh>
#include <Nebula/timer/Actor/Base.hpp>
#include <Nebula/Actor/Base.hh>


Neb::Timer::Actor::Base::Base(Neb::Actor::Base_s actor, double seconds):
	timer_(Neb::App::Base::globalBase()->ios_, boost::posix_time::seconds(seconds)),
	actor_(actor)
{
	timer_.async_wait(boost::bind(&Neb::Timer::Actor::Base::doSomething, this));
}





