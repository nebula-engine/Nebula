#include <utilities/Types/Utilities.h>

#include <content/Physics/PhysX/CO_PH_PX_Physics.h>

#include <content/Scene/Physics/PhysX/CO_SC_PH_PX_Scene.h>

#include <nebula/content/actor/admin/ncaa::rigid_dynamic.h>
#include <content/actor/Physics/PhysX/CO_AC_PH_PX_rigid_dynamic.h>

#include <nebula/content/actor/admin/ncaa::Controller.h>
#include <content/actor/Physics/PhysX/CO_AC_PH_PX_Controller.h>

#include <content/Scene/Admin/CO_SC_AD_Scene.h>

physx::PxFilterFlags DefaultFilterShader( physx::PxFilterObjectAttributes attributes0, physx::PxFilterData filterData0, physx::PxFilterObjectAttributes attributes1, physx::PxFilterData filterData1, physx::PxPairFlags& pairFlags, const void* constantBlock, physx::PxU32 constantBlockSize) {
	return physx::PxFilterFlag::eDEFAULT;
}

void	CO_PH_PX_Physics::init( const boost::shared_ptr<>&  ) {
	PRINTSIG;
	

	// Foundation
	m_foundation = PxCreateFoundation(PX_PHYSICS_VERSION, m_defaultAllocatorCallback, m_defaultErrorCallback);
	if ( !m_foundation ) {
		throw Except("PxCreateFoundation failed!");
	}
	
	bool recordMemoryAllocations = true;
	
	// Profile Zone Manager
	m_profileZoneManager = &physx::PxProfileZoneManager::createProfileZoneManager( m_foundation );
	if(!m_profileZoneManager) {
		throw Except("PxProfileZoneManager::createProfileZoneManager failed!");
	}
	
	// Physics
	m_physics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_foundation, physx::PxTolerancesScale(), recordMemoryAllocations, m_profileZoneManager );
	
	if ( !m_physics ) {
		throw Except("PxCreatePhysics failed!");
	}
	
	// Cooking
	m_cooking = PxCreateCooking(PX_PHYSICS_VERSION, *m_foundation, physx::PxCookingParams());
	if (!m_cooking) {
		throw Except("PxCreateCooking failed!");
	}
	
	// Extensions
	if ( !PxInitExtensions(*m_physics) ) {
		throw Except("PxInitExtensions failed!");
	}
	
	// Character controller manager
	m_characterControllerManager = PxCreateControllerManager(*m_foundation);

}
void	CO_PH_PX_Physics::VShutDown() {
	m_physics->release();
	m_foundation->release();
}
void	CO_PH_PX_Physics::RegisterScene( CO_SC_AD_Scene* scene ) {
	PRINTSIG;
	//CO_SC_PH_PX_Scene* physicsScenePhysX = (CO_SC_PH_PX_Scene*)scene->GetPhysicsScene();
	CO_SC_PH_PX_Scene* physicsScenePhysX = dynamic_cast<CO_SC_PH_PX_Scene*>( scene->GetPhysicsScene() );
	if ( !physicsScenePhysX ) throw Except("dynamic_cast returned null");

	physx::PxSceneDesc sceneDesc( m_physics->getTolerancesScale() );
	
	sceneDesc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);
	
	physicsScenePhysX->CustomizeSceneDesc( sceneDesc );
	
	int m_nbThreads = 1;
	
	// cpu dispatcher
	if( !sceneDesc.cpuDispatcher ) {
		physx::PxDefaultCpuDispatcher* cpuDispatcher = physx::PxDefaultCpuDispatcherCreate( m_nbThreads );
		if( !cpuDispatcher ) throw Except("PxDefaultCpuDispatcherCreate failed!\n");
		sceneDesc.cpuDispatcher = cpuDispatcher;
	}
	
	// filter shader
	if( !sceneDesc.filterShader ) {
		if (physicsScenePhysX->m_defaultFilterShader) {
			sceneDesc.filterShader = physicsScenePhysX->m_defaultFilterShader;
		}
		else {
			sceneDesc.filterShader = DefaultFilterShader;
		}
	}
	
	// gpu dispatcher
	#ifdef PX_WINDOWS
		if( !sceneDesc.gpuDispatcher && m_cudaContextManager ) {
			sceneDesc.gpuDispatcher = m_cudaContextManager->getGpuDispatcher();
		}
	#endif
	
	if (!sceneDesc.isValid()) throw Except("PxSceneDesc invalid");

	physicsScenePhysX->m_scene = m_physics->createScene( sceneDesc );
	if ( !physicsScenePhysX->m_scene ) {
		throw Except("createScene failed!\n");
	}
	
}
void	CO_PH_PX_Physics::Registerrigid_dynamic( ncaa::rigid_dynamic* rigidDynamic )
{
	
	CO_AC_PH_PX_rigid_dynamic* acPhPxrigid_dynamic = dynamic_cast<CO_AC_PH_PX_rigid_dynamic*>(rigidDynamic->Ptr<CO_AC_PH_rigid_dynamic>::Get_Or_Error());

	// Get transform
	Math::Transformf transform; //physx::PxTransform transform;
	rigidDynamic->GetTransform( transform ); //acPhPxrigid_dynamic->GetTransform( transform );
	
	physx::PxTransform pxtransform;

	pxtransform = TransformToPxTransform( transform );

	// Create Pxrigid_dynamic
	physx::Pxrigid_dynamic* actor = m_physics->createrigid_dynamic( pxtransform );
	
	// Pass Pxrigid_dynamic to rigid_dynamic
	acPhPxrigid_dynamic->Setactor( actor );
};
void	CO_PH_PX_Physics::RegisterController( ncaa::Controller*& controller, CO_SC_AD_Scene* scene ) {
	// Get actor's physics object
	CO_AC_PH_PX_Controller* acPhPxController = dynamic_cast<CO_AC_PH_PX_Controller*>( controller->Ptr<CO_AC_PH_Controller>::Get_Or_Error() );
	
	//CO_SC_PH_PX_Scene* physicsScenePhysX = (CO_SC_PH_PX_Scene*)scene->GetPhysicsScene();
	CO_SC_PH_PX_Scene* physicsScenePhysX = dynamic_cast<CO_SC_PH_PX_Scene*>( scene->GetPhysicsScene() );
	if ( !physicsScenePhysX ) throw Except("dynamic_cast returned null");
	

	physx::PxCapsuleControllerDesc desc;

	// Create PxController
	physx::PxController* pxController = m_characterControllerManager->createController( *m_physics, physicsScenePhysX->GetPxScene(), desc );
	
	
	acPhPxController->SetPxController( pxController );


}


void 	DefaultErrorCallback::reportError( physx::PxErrorCode::Enum code, const char *message, const char *file, int line) {
	printf("%s:%i: %s\n",file,line,message);
}




