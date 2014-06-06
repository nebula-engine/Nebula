#ifndef NEBULA_CORE_TIME_STEP_HPP
#define NEBULA_CORE_TIME_STEP_HPP

#include <Nebula/Util/typedef.hpp>

namespace Neb {
	namespace Core {
		struct TimeStep {
			real			time;
			real			last;
			real			dt;
			unsigned int		frame;
		};
	}
}

#endif


