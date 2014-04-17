#ifndef _NEBULA_SIMULATION_CALLBACK__
#define _NEBULA_SIMULATION_CALLBACK__

#include <memory>
#include <vector>

#include <PxPhysicsAPI.h>

#include <gal/map.h>

#include <glutpp/scene/scene.h>

#include <neb/actor/Rigid_Dynamic.h>
#include <neb/actor/Rigid_Static.h>
#include <neb/actor/Controller.h>

#include <tinyxml2.h>


namespace neb
{
	class simulation_callback: public physx::PxSimulationEventCallback
	{
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

#endif



