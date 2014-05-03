#ifndef NEBULA_TIMER_ACTOR_RELEASE_HPP
#define NEBULA_TIMER_ACTOR_RELEASE_HPP

#include <nebula/timer/Actor/Base.hpp>

namespace neb {
	namespace Timer {
		namespace Actor {
			class Release: public neb::Timer::Actor::Base {
				public:
					Release(boost::asio::io_service& io, boost::shared_ptr<glutpp::actor::actor>, double);
					virtual void		doSomething();
			};
		}
	}
}

#endif
