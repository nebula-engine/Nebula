#include <utilities/Types/Utilities.h>
#include <core/Core.h>

#include <content/Physics/PhysX/CO_PH_PX_Physics.h>

#include <content/Actor/Admin/CO_AC_AD_Actor.h>
#include <content/Actor/Physics/PhysX/CO_AC_PH_PX_Actor.h>



#include <content/Scene/Physics/PhysX/CO_SC_PH_PX_Scene.h>

void	CO_SC_PH_PX_Scene::VStep( Void* data )
{
	physx::PxU32 nbPxActor = m_scene->getNbActors(physx::PxActorTypeSelectionFlag::eRIGID_DYNAMIC);
	printf("there are %i PxRigidActor objects in the scene\n",nbPxActor);

	float dt = DynCast<Void,AR_Step>( data )->dt;

	// PxScene
	m_scene->simulate( dt );
	m_scene->fetchResults(true);

	// retrieve array of actors that moved
	physx::PxU32 nbActiveTransforms;
	physx::PxActiveTransform* activeTransforms = m_scene->getActiveTransforms(nbActiveTransforms);

	// update each render object with the new transform
	for ( physx::PxU32 i = 0; i < nbActiveTransforms; ++i )
	{
		CO_AC_AD_ActorBase* actorBase = static_cast<CO_AC_AD_ActorBase*>(activeTransforms[i].userData);
		
		Math::Transformf trans = CO_PH_PX_Physics::PxTransformToTransform( activeTransforms[i].actor2World );

		actorBase->SetTransform( trans );

		printf("transform.p.y=%16f\n",activeTransforms[i].actor2World.p.y);
	}
}
void	CO_SC_PH_PX_Scene::AddActor( CO_AC_AD_Actor* actor )
{
	
	CO_AC_PH_PX_Actor* acPhPxActor = dynamic_cast<CO_AC_PH_PX_Actor*>(actor->Ptr<CO_AC_PH_Actor>::Get_Or_Error());
	
	physx::PxActor* pxActor = acPhPxActor->GetPxActor();
	
	m_scene->addActor(*pxActor);
	
}
void	CO_SC_PH_PX_Scene::CustomizeSceneDesc( physx::PxSceneDesc& sceneDesc )
{
	sceneDesc.flags |= physx::PxSceneFlag::eENABLE_ACTIVETRANSFORMS;

}






