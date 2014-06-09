#ifndef NEBULA_CORE_POSE
#define NEBULA_CORE_POSE

#include <Nebula/Util/typedef.hpp>

namespace Neb {
	namespace Core {
		class Pose {
			public:
				virtual mat4				getPoseGlobal() = 0;
				virtual mat4				getPose() = 0;

		};
	}
}

#endif
