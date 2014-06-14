
#include <PhysX/simulation_callback.hh>
#include <PhysX/core/actor/actor/base.hpp>

void 	px::simulation_callback::onConstraintBreak(
		physx::PxConstraintInfo *constraints, physx::PxU32 count) {
	printf("%s\n", __PRETTY_FUNCTION__);
}
void	px::simulation_callback::onContact(
		const physx::PxContactPairHeader & pairHeader,
		const physx::PxContactPair *pairs,
		physx::PxU32 nbPairs) {
	
	printf("%s\n", __PRETTY_FUNCTION__);
	
	physx::PxActor* pxactor0 = pairHeader.actors[0];
	physx::PxActor* pxactor1 = pairHeader.actors[1];
	
	/* cast the userdata to a plain old pointer
	 * then call @c isActor to get the shared opinter
	 * doing so keeps the actors alive long enough to return from the call to @c hit
	 * allows the scene to release the actors safely during the call to @c hit
	 */
	auto actor0 = reinterpret_cast<px::core::actor::actor::base*>(pxactor0->userData);//->isPxActorBase();
	auto actor1 = reinterpret_cast<px::core::actor::actor::base*>(pxactor1->userData);//->isPxActorBase();
	
	for(physx::PxU32 i=0; i < nbPairs; i++) {
		const physx::PxContactPair& cp = pairs[i];
		
		if(cp.events & physx::PxPairFlag::eNOTIFY_TOUCH_FOUND) {
			actor0->hit();
			actor1->hit();
		}
	}
}
void 	px::simulation_callback::onWake(physx::PxActor **actors, physx::PxU32 count) {
	printf("%s\n", __PRETTY_FUNCTION__);
}
void 	px::simulation_callback::onSleep(physx::PxActor **actors, physx::PxU32 count) {
	printf("%s\n", __PRETTY_FUNCTION__);
}
void 	px::simulation_callback::onTrigger(physx::PxTriggerPair *pairs, physx::PxU32 count)
{
	printf("%s\n", __PRETTY_FUNCTION__);
}


