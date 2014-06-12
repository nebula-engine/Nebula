#ifndef NEBULA_TIMER_ACTOR_RELEASE_HPP
#define NEBULA_TIMER_ACTOR_RELEASE_HPP

#include <Nebula/timer/Actor/Base.hpp>

namespace neb {
	namespace Timer {
		namespace Actor {
			class Release: public neb::Timer::Actor::Base {
				public:
					Release(neb::Actor::Base_s, double);
					virtual void		doSomething();
			};
		}
	}
}

#endif



