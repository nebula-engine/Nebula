#ifndef __NEBULA_TIMER_ACTOR_BASE_
#define __NEBULA_TIMER_ACTOR_BASE_


#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>


//#include <Nebula/config.hh> // Nebula/config.hpp.in
#include <Nebula/core/actor/Util/Types.hh>

/** @todo replace types with inheritance and possibly shared library support */

namespace neb {
	namespace Timer {
		namespace actor {
			class base:
				public sp::enable_shared_from_this<base>
			{
				public:
					base(sp::shared_ptr<neb::core::actor::base> actor, double);
					virtual ~base();

					/**
					 *
					 * what to do when timer expires
					 */
					virtual void						doSomething() = 0;

					void 							activate();

					boost::asio::deadline_timer				timer_;

					sp::weak_ptr<neb::core::actor::base>			actor_;

					double							time_;
			};

		}
	}
}

#endif
