#ifndef NEBULA_TIMER_ACTOR_RELEASE_HPP
#define NEBULA_TIMER_ACTOR_RELEASE_HPP

#include <Nebula/timer/Actor/Base.hpp>

namespace neb {
	namespace Timer {
		namespace Actor {
			class Release: public Neb::Timer::Actor::Base {
				public:
					Release(Neb::Actor::Base_s, double);
					virtual void		doSomething();
			};
		}
	}
}

#endif



