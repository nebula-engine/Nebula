#include <neb/physics.h>
#include <neb/simulation_callback.h>

void 	neb::simulation_callback::onConstraintBreak(
		physx::PxConstraintInfo *constraints, physx::PxU32 count) {
	printf("%s\n", __PRETTY_FUNCTION__);
}
void	neb::simulation_callback::onContact(
		const physx::PxContactPairHeader & pairHeader,
		const physx::PxContactPair *pairs,
		physx::PxU32 nbPairs) {
	
	printf("%s\n", __PRETTY_FUNCTION__);
	
	physx::PxActor* pxactor0 = pairHeader.actors[0];
	physx::PxActor* pxactor1 = pairHeader.actors[1];
	neb::actor::Actor* actor0 = reinterpret_cast<neb::actor::Actor*>(pxactor0->userData);
	neb::actor::Actor* actor1 = reinterpret_cast<neb::actor::Actor*>(pxactor1->userData);
	
	for(physx::PxU32 i=0; i < nbPairs; i++)
	{
		const physx::PxContactPair& cp = pairs[i];
		
		if(cp.events & physx::PxPairFlag::eNOTIFY_TOUCH_FOUND)
		{
			physx::PxU32 w02 = actor0->get_raw()->filter_data_.simulation_.word2;
			physx::PxU32 w12 = actor1->get_raw()->filter_data_.simulation_.word2;
			
			if(w02 & glutpp::filter::type::PROJECTILE)
			{
				//printf("delete actor\n");
				actor0->set(glutpp::actor::flag::SHOULD_RELEASE);
			}
			
			if(w12 & glutpp::filter::type::PROJECTILE)
			{
				//printf("delete actor\n");
				actor1->set(glutpp::actor::flag::SHOULD_RELEASE);
			}
		}
	}
}
void 	neb::simulation_callback::onWake(physx::PxActor **actors, physx::PxU32 count) {
	printf("%s\n", __PRETTY_FUNCTION__);
}
void 	neb::simulation_callback::onSleep(physx::PxActor **actors, physx::PxU32 count) {
	printf("%s\n", __PRETTY_FUNCTION__);
}
void 	neb::simulation_callback::onTrigger(physx::PxTriggerPair *pairs, physx::PxU32 count)
{
	printf("%s\n", __PRETTY_FUNCTION__);
}


