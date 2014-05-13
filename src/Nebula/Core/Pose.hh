#ifndef NEBULA_CORE_POSE
#define NEBULA_CORE_POSE

#include <PxPhysicsAPI.h>

namespace Neb {
	namespace Core {
		class Pose {
			public:
				virtual physx::PxTransform			getPoseGlobal() = 0;
				virtual physx::PxTransform			getPose() = 0;

		};
	}
}

#endif
