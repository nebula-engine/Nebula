#include <cassert>

#include <neb/phx/simulation_callback.hh>

#include <neb/fnd/core/actor/actor/Base.hpp>
//#include <neb/phx/core/actor/actor/base.hpp>

void 	neb::phx::simulation_callback::onConstraintBreak(
		physx::PxConstraintInfo *constraints, physx::PxU32 count)
{
	printf("%s\n", __PRETTY_FUNCTION__);
}
void	neb::phx::simulation_callback::onContact(
		const physx::PxContactPairHeader & pairHeader,
		const physx::PxContactPair *pairs,
		physx::PxU32 nbPairs)
{	
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
	auto nactor0 = static_cast<neb::fnd::core::actor::base*>(pxactor0->userData)->is_fnd_actor_base();
	auto nactor1 = static_cast<neb::fnd::core::actor::base*>(pxactor1->userData)->is_fnd_actor_base();

	assert(nactor0);
	assert(nactor1);
	
	//auto actor0 = static_cast<phx::core::actor::actor::base*>(pxactor0->userData)->isPxActorActorBase();
	//auto actor1 = static_cast<phx::core::actor::actor::base*>(pxactor1->userData)->isPxActorActorBase();

	/*
	auto actor0 = std::dynamic_pointer_cast<neb::phx::core::actor::actor::base>(nactor0);
	auto actor1 = std::dynamic_pointer_cast<neb::phx::core::actor::actor::base>(nactor1);
	
	printf("actor0 %p\n", actor0.get());
	printf("actor1 %p\n", actor1.get());

	assert(actor0);
	assert(actor1);
	*/

	for(physx::PxU32 i=0; i < nbPairs; i++) {
		const physx::PxContactPair& cp = pairs[i];
		
		if(cp.events & physx::PxPairFlag::eNOTIFY_TOUCH_FOUND) {
	
			printf("hit\n");
		
			//actor0->hit();
			//actor1->hit();
			nactor0->hit();
			nactor1->hit();
		}
	}
}
void 	neb::phx::simulation_callback::onWake(physx::PxActor **actors, physx::PxU32 count)
{
	printf("%s\n", __PRETTY_FUNCTION__);
}
void 	neb::phx::simulation_callback::onSleep(physx::PxActor **actors, physx::PxU32 count)
{
	printf("%s\n", __PRETTY_FUNCTION__);
}
void 	neb::phx::simulation_callback::onTrigger(physx::PxTriggerPair *pairs, physx::PxU32 count)
{
	printf("%s\n", __PRETTY_FUNCTION__);
}


