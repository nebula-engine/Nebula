#ifndef NEBULA_CORE_POSE
#define NEBULA_CORE_POSE

#include <neb/core/pose.hpp>

namespace neb {
	namespace core {
		class Pose {
			public:
				virtual neb::core::pose				getPoseGlobal() const = 0;
				virtual neb::core::pose				getPose() const = 0;
		};
	}
}

#endif
