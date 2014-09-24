#ifndef NEBULA_TIMER_ACTOR_RELEASE_HPP
#define NEBULA_TIMER_ACTOR_RELEASE_HPP

#include <neb/core/timer/Actor/Base.hpp>

namespace neb {
	namespace Timer {
		namespace actor {
			class Release: public neb::Timer::actor::base {
				public:
					Release(std::shared_ptr<neb::core::core::actor::base>, double);
					virtual void		doSomething();
			};
		}
	}
}

#endif



