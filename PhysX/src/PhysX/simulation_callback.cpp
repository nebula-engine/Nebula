
#include <PhysX/simulation_callback.hh>
#include <PhysX/core/actor/actor/base.hpp>

void 	phx::simulation_callback::onConstraintBreak(
		physx::PxConstraintInfo *constraints, physx::PxU32 count) {
	printf("%s\n", __PRETTY_FUNCTION__);
}
void	phx::simulation_callback::onContact(
		const physx::PxContactPairHeader & pairHeader,
		const physx::PxContactPair *pairs,
		physx::PxU32 nbPairs) {
	
	printf("%s\n", __PRETTY_FUNCTION__);
	
	physx::PxActor* pxactor0 = pairHeader.actors[0];
	physx::PxActor* pxactor1 = pairHeader.actors[1];
	
	assert(pxactor0->userData);
	assert(pxactor1->userData);

	printf("%p\n", pxactor0->userData);
	printf("%p\n", pxactor1->userData);


	/* cast the userdata to a plain old pointer
	 * then call @c isActor to get the shared opinter
	 * doing so keeps the actors alive long enough to return from the call to @c hit
	 * allows the scene to release the actors safely during the call to @c hit
	 */
	auto nactor0 = static_cast<neb::core::actor::base*>(pxactor0->userData)->isActorBase();
	auto nactor1 = static_cast<neb::core::actor::base*>(pxactor1->userData)->isActorBase();

	assert(nactor0);
	assert(nactor1);
	
	auto actor0 = static_cast<phx::core::actor::actor::base*>(pxactor0->userData)->isPxActorActorBase();
	auto actor1 = static_cast<phx::core::actor::actor::base*>(pxactor1->userData)->isPxActorActorBase();

	printf("%p\n", actor0.get());
	printf("%p\n", actor1.get());

	assert(actor0);
	assert(actor1);

	for(physx::PxU32 i=0; i < nbPairs; i++) {
		const physx::PxContactPair& cp = pairs[i];
		
		if(cp.events & physx::PxPairFlag::eNOTIFY_TOUCH_FOUND) {
	
			printf("hit\n");
		
			actor0->hit();
			actor1->hit();
		}
	}
}
void 	phx::simulation_callback::onWake(physx::PxActor **actors, physx::PxU32 count) {
	printf("%s\n", __PRETTY_FUNCTION__);
}
void 	phx::simulation_callback::onSleep(physx::PxActor **actors, physx::PxU32 count) {
	printf("%s\n", __PRETTY_FUNCTION__);
}
void 	phx::simulation_callback::onTrigger(physx::PxTriggerPair *pairs, physx::PxU32 count)
{
	printf("%s\n", __PRETTY_FUNCTION__);
}


