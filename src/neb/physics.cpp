#include <assert.h>

#include <math/free.h>

#include <PxPhysicsAPI.h>

#include <neb/physics.h>
#include <neb/scene/scene.h>
#include <neb/simulation_callback.h>

namespace neb
{
	physics __physics;
}

physx::PxFilterFlags	DefaultFilterShader(
		physx::PxFilterObjectAttributes attributes0,
		physx::PxFilterData filterData0,
		physx::PxFilterObjectAttributes attributes1,
		physx::PxFilterData filterData1,
		physx::PxPairFlags& pairFlags,
		const void* constantBlock,
		physx::PxU32 constantBlockSize )
{	
	printf("%s\n",__PRETTY_FUNCTION__);
	
	printf("%i %i %i %i\n", filterData0.word0, filterData1.word1, filterData1.word0, filterData0.word1);
	
	physx::PxFilterFlags filter_flags = physx::PxFilterFlag::eDEFAULT;
	
	// let triggers through
	if(physx::PxFilterObjectIsTrigger(attributes0) || physx::PxFilterObjectIsTrigger(attributes1))
	{
		pairFlags = physx::PxPairFlag::eTRIGGER_DEFAULT;
		return physx::PxFilterFlag::eDEFAULT;
	}
	
	// collision
	physx::PxU32 w0 = filterData0.word0 & filterData1.word1;
	physx::PxU32 w1 = filterData1.word0 & filterData0.word1;
	if(w0 && w1)
	{
		pairFlags |= physx::PxPairFlag::eCONTACT_DEFAULT;
		
		filter_flags = physx::PxFilterFlag::eDEFAULT;	
	}
	else
	{
		filter_flags = physx::PxFilterFlag::eSUPPRESS;
	}
	
	// notification
	physx::PxU32 w2 = filterData0.word2 & filterData1.word3;
	physx::PxU32 w3 = filterData1.word2 & filterData0.word3;
	if(w2 && w3)
	{
		pairFlags |= physx::PxPairFlag::eNOTIFY_TOUCH_FOUND;
	}
	
	return filter_flags;
}

void DefaultErrorCallback::reportError(
		physx::PxErrorCode::Enum code,
		char const * message,
		char const * file,
		int line)
{
	printf("%s:%i: %s\n",file,line,message);
}
/*neb::Physics::Physics()
  {
//	jess::clog << neb_FUNCSIG << std::endl;
}
neb::Physics::~base()
{
//	jess::clog << neb_FUNCSIG << std::endl;
}*/
neb::physics::physics(): px_physics_(NULL) {
}
void	neb::physics::Init() {
	
	printf("%s\n",__PRETTY_FUNCTION__);
	
	// Physx
	// Foundation
	px_foundation_ = PxCreateFoundation(
			PX_PHYSICS_VERSION,
			px_default_allocator_callback_,
			px_default_error_callback_);
	assert(px_foundation_);
	
	bool recordMemoryAllocations = true;

	// Profile Zone Manager
	px_profile_zone_manager_ = &::physx::PxProfileZoneManager::createProfileZoneManager( px_foundation_ );
	assert( px_profile_zone_manager_ );

	// Physics
	px_physics_ = PxCreatePhysics(
			PX_PHYSICS_VERSION,
			*px_foundation_,
			physx::PxTolerancesScale(),
			recordMemoryAllocations, px_profile_zone_manager_ );
	assert( px_physics_ );

	// cooking
	px_cooking_ = PxCreateCooking( PX_PHYSICS_VERSION, *px_foundation_, ::physx::PxCookingParams() );
	assert( px_cooking_ );

	// Extensions
	assert( PxInitExtensions( *px_physics_ ) );

	// character controller manager
	px_character_controller_manager_ = ::PxCreateControllerManager( *px_foundation_ );
	assert( px_character_controller_manager_ );

	// vehicle
	assert( PxInitVehicleSDK(*px_physics_) );
	PxVehicleSetBasisVectors(physx::PxVec3(0,1,0), physx::PxVec3(0,0,-1));
	PxVehicleSetUpdateMode(physx::PxVehicleUpdateMode::Enum::eACCELERATION);
	
	
}
void				neb::physics::Shutdown() {
	//jess::clog << neb_FUNCSIG << std::endl;
	printf("%s\n",__PRETTY_FUNCTION__);

	physx::PxCloseVehicleSDK();

	px_physics_->release();
	px_foundation_->release();
}
std::shared_ptr<neb::scene::scene> neb::physics::create_scene(scene::desc* sd) {
	
	printf("%s\n",__PRETTY_FUNCTION__);
	
	assert(px_physics_ != NULL);
	
	std::shared_ptr<neb::scene::scene> scene(new neb::scene::scene);
	
	physx::PxSceneDesc scene_desc( px_physics_->getTolerancesScale() );
	
	scene_desc.gravity = sd->raw_.gravity_.to_math();
	
	scene_desc.flags |= physx::PxSceneFlag::eENABLE_ACTIVETRANSFORMS;
	
	int m_nbThreads = 1;
	
	// cpu dispatcher
	printf("cpu dispatcher\n");
	if( !scene_desc.cpuDispatcher )
	{
		physx::PxDefaultCpuDispatcher* cpuDispatcher = ::physx::PxDefaultCpuDispatcherCreate( m_nbThreads );
		assert( cpuDispatcher );

		scene_desc.cpuDispatcher = cpuDispatcher;
	}

	// filter shader
	printf("filter shader\n");
	if(!scene_desc.filterShader)
	{
		if(scene->px_filter_shader_)
		{
			scene_desc.filterShader = scene->px_filter_shader_;
		}
		else
		{
			scene_desc.filterShader = DefaultFilterShader;
		}
	}

	// gpu dispatcher
	printf("gpu dispatcher\n");
#ifdef PX_WINDOWS
	if( !scene_desc.gpuDispatcher && m_cudaContextManager )
	{
		sceneDesc.gpuDispatcher = m_cudaContextManager->getGpuDispatcher();
	}
#endif
	assert( scene_desc.isValid() );



	scene->px_scene_ = px_physics_->createScene(scene_desc);
	assert(scene->px_scene_);

	// simulation callback
	neb::simulation_callback* sec = new neb::simulation_callback;
	scene->simulation_callback_ = sec;
	scene->px_scene_->setSimulationEventCallback(sec);

	// actors
	//scene->Create_Lights(sd);

	
	return scene;
}


