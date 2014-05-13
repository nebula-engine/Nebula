
#include <nebula/timer/Actor/Base.hpp>
#include <nebula/actor/Base.hpp>


Actor(boost::asio::io_service& io, boost::shared_ptr<glutpp::actor::actor> actor, double seconds):
	timer_(io, boost::posix_time::seconds(seconds)),
	actor_(actor)
{
	timer_.async_wait(boost::bind(&neb::Timer::Actor::doSomething, this));
}
void neb::Timer::Actor::activate() {

	if(actor_.expired()) return;

	auto a = actor_.lock();

	switch(type_)
	{
		case RELEASE:
			a->set(glutpp::actor::actor::flag::SHOULD_RELEASE);
			break;
		default:
			break;
	}

}

