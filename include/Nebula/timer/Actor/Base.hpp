#ifndef __NEBULA_TIMER_ACTOR_BASE_
#define __NEBULA_TIMER_ACTOR_BASE_


#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>


//#include <Nebula/config.hh> // Nebula/config.hpp.in
#include <Nebula/Actor/Util/Types.hh>

/** @todo replace types with inheritance and possibly shared library support */

namespace neb {
	namespace Timer {
		namespace actor {
			class base {
				public:
					base(sp::shared_ptr<neb::core::actor::base> actor, double);


					virtual void					doSomething() = 0;

					void  activate();
					
					//neb::Timer::actor::Type         type_;
					boost::asio::deadline_timer			timer_;
					
					sp::shared_ptr<neb::core::actor::base>			actor_;
			};

		}
	}
}

#endif
