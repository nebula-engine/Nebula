#ifndef _NEBULA_SIMULATION_CALLBACK__
#define _NEBULA_SIMULATION_CALLBACK__

#include <memory>
#include <vector>

#include <PxPhysicsAPI.h>

namespace Neb {
	namespace Physics {
		namespace PhysX {
			class simulation_callback: public physx::PxSimulationEventCallback {
				public:

					virtual void 	onConstraintBreak(
							physx::PxConstraintInfo *constraints,
							physx::PxU32 count);

					virtual void 	onWake (physx::PxActor **actors, physx::PxU32 count);

					virtual void 	onSleep (physx::PxActor **actors, physx::PxU32 count);

					virtual void 	onContact (
							const physx::PxContactPairHeader &pairHeader,
							const physx::PxContactPair *pairs,
							physx::PxU32 nbPairs);

					virtual void 	onTrigger (physx::PxTriggerPair *pairs, physx::PxU32 count);

			};
		}
	}
}

#endif



