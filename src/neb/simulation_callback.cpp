#include <neb/physics.h>
#include <neb/simulation_callback.h>

void 	neb::simulation_callback::onConstraintBreak(
		physx::PxConstraintInfo *constraints, physx::PxU32 count) {
	printf("%s\n", __PRETTY_FUNCTION__);
}
void	neb::simulation_callback::onContact(
		const physx::PxContactPairHeader & pairHeader, const physx::PxContactPair *pairs, physx::PxU32 nbPairs) {

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
			if(actor0->desc_.filter_data_.simulation_.word3 & neb::filter::type::PROJECTILE)
			{
				actors_to_delete_.push_back(actor0->i_);
			}
			
			if(actor1->desc_.filter_data_.simulation_.word3 & neb::filter::type::PROJECTILE)
			{
				actors_to_delete_.push_back(actor1->i_);
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


