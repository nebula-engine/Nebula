#ifndef NEBULA_CORE_POSE
#define NEBULA_CORE_POSE

#include <neb/core/pose.hpp>

namespace neb {
	namespace core {
		class Pose {
			public:
<<<<<<< HEAD
				virtual neb::core::pose				getPoseGlobal() = 0;
				virtual neb::core::pose				getPose() = 0;
=======
				virtual neb::core::pose				getPoseGlobal() const = 0;
				virtual neb::core::pose				getPose() const = 0;
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
		};
	}
}

#endif
