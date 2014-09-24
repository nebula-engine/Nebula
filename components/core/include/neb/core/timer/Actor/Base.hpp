#ifndef __NEBULA_TIMER_ACTOR_BASE_
#define __NEBULA_TIMER_ACTOR_BASE_


#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <neb/core/core/actor/util/decl.hpp>

namespace neb {
	namespace Timer {
		namespace actor {
			class base:
				public std::enable_shared_from_this<base>
			{
				public:
					base(std::shared_ptr<neb::core::core::actor::base> actor, double);
					virtual ~base();

					/**
					 *
					 * what to do when timer expires
					 */
					virtual void						doSomething() = 0;

					void 							activate();

					boost::asio::deadline_timer				timer_;

					std::weak_ptr<neb::core::core::actor::base>		actor_;

					double							time_;
			};

		}
	}
}

#endif
