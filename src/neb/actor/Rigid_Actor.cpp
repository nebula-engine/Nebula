#include <neb/actor/Rigid_Actor.h>

void	neb::actor::Rigid_Actor::step_remote(double)
{}
void	neb::actor::Rigid_Actor::setupFiltering(physx::PxU32 filterGroup, physx::PxU32 filterMask)
{
	assert(px_actor_);
	
	physx::PxRigidActor* actor = (physx::PxRigidActor*)px_actor_;
	
	physx::PxFilterData filterData;
	filterData.word0 = filterGroup; // word0 = own ID
	filterData.word1 = filterMask;  // word1 = ID mask to filter pairs that trigger a contact callback;
	const physx::PxU32 numShapes = actor->getNbShapes();
	
	physx::PxShape** shapes = new physx::PxShape*[numShapes];
	
	actor->getShapes(shapes, numShapes);

	for(physx::PxU32 i = 0; i < numShapes; i++)
	{
		physx::PxShape* shape = shapes[i];
		shape->setSimulationFilterData(filterData);
	}
	
	delete[] shapes;
}


