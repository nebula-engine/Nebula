#ifndef __NEBULA_TIMER_ACTOR_BASE_
#define __NEBULA_TIMER_ACTOR_BASE_


#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>


#include <nebula/config.hpp> // nebula/config.hpp.in

/** @todo replace types with inheritance and possibly shared library support */

namespace neb {
	namespace Timer {
		namespace Actor {
			class Base {
				public:
					Base(boost::asio::io_service& io, boost::shared_ptr<glutpp::actor::actor>, double);


					virtual void					doSomething() = 0;

					void  activate();
					
					//neb::Timer::Actor::Type         type_;
					boost::asio::deadline_timer			timer_;
					
					boost::weak_ptr<glutpp::actor::actor>		actor_;
			};

		}
	}
}

#endif
