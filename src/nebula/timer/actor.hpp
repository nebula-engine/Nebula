#ifndef __NEBULA_TIMER_ACTOR__
#define __NEBULA_TIMER_ACTOR__

//#include <galaxy/timer/timer.hpp>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>


#include <nebula/config.hpp>

/** @todo replace types with inheritance and possibly shared library support */

namespace neb {
	namespace Timer {
		class Actor {
			public:
				enum Type {
					NONE = 0,
					RELEASE,
				};

				Actor(boost::asio::io_service& io, boost::shared_ptr<glutpp::actor::actor> actor):
					timer_(io, boost::posix_time::seconds(1)),
					actor_(actor)
			{
				timer_.async_wait(boost::bind(&neb::Timer::Actor::doSomething, this));
			}
				virtual void		doSomething() = 0;
				
				
				//neb::Actor::Base_s, neb::Timer::Actor::Type, double);

				void  activate();

				//neb::Timer::Actor::Type         type_;
				boost::asio::deadline_timer			timer_;


				boost::weak_ptr<glutpp::actor::actor>              actor_;
		};
	}
}

#endif
