#ifndef NEBULA_CORE_POSE
#define NEBULA_CORE_POSE

#include <Nebula/Util/typedef.hpp>
#include <Nebula/Core/pose.hpp>

namespace neb {
	namespace core {
		class Pose {
			public:
				virtual neb::core::pose				getPoseGlobal() = 0;
				virtual neb::core::pose				getPose() = 0;

		};
	}
}

#endif
