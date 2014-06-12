#ifndef NEBULA_TIMER_ACTOR_RELEASE_HPP
#define NEBULA_TIMER_ACTOR_RELEASE_HPP

#include <Nebula/timer/Actor/Base.hpp>

namespace neb {
	namespace Timer {
		namespace actor {
			class Release: public neb::Timer::actor::Base {
				public:
					Release(sp::shared_ptr<neb::core::actor::Base>, double);
					virtual void		doSomething();
			};
		}
	}
}

#endif



