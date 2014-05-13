#ifndef __NEBULA_TIMER_ACTOR_BASE_
#define __NEBULA_TIMER_ACTOR_BASE_


#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>


#include <Nebula/config.hpp> // Nebula/config.hpp.in
#include <Nebula/Actor/Util/Types.hh>

/** @todo replace types with inheritance and possibly shared library support */

namespace Neb {
	namespace Timer {
		namespace Actor {
			class Base {
				public:
					Base(boost::asio::io_service& io, boost::shared_ptr<Neb::Actor::Base>, double);


					virtual void					doSomething() = 0;

					void  activate();
					
					//neb::Timer::Actor::Type         type_;
					boost::asio::deadline_timer			timer_;
					
					boost::weak_ptr<Neb::Actor::Base>		actor_;
			};

		}
	}
}

#endif
