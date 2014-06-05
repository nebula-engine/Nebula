#ifndef NEBULA_CORE_POSE
#define NEBULA_CORE_POSE

#include <glm/mat4x4.hpp>

namespace Neb {
	namespace Core {
		class Pose {
			public:
				virtual glm::mat4			getPoseGlobal() = 0;
				virtual glm::mat4			getPose() = 0;

		};
	}
}

#endif
