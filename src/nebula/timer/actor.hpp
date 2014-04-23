#ifndef __NEBULA_TIMER_ACTOR__
#define __NEBULA_TIMER_ACTOR__

#include <galaxy/timer/timer.hpp>

#include <nebula/config.hpp>

/** @todo replace types with inheritance and possibly shared library support */

namespace neb {
	namespace Timer {
		class Actor: public gal::timer::timer {
			public:
				enum Type {
					NONE = 0,
					RELEASE,
				};

				Actor(neb::Actor::Base_s, neb::Timer::Actor::Type, double);

				void  activate();

				neb::Timer::Actor::Type         type_;
				neb::Actor::Base_w              actor_;
		};
	}
}

#endif
