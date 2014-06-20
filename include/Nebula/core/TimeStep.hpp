#ifndef NEBULA_CORE_TIME_STEP_HPP
#define NEBULA_CORE_TIME_STEP_HPP

#include <Nebula/util/typedef.hpp>

namespace neb {
	namespace core {
		struct TimeStep {
			real			time;
			real			last;
			real			dt;
			unsigned int		frame;
		};
	}
}

#endif


