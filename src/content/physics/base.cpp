#include <nebula/content/scene/admin/base.hpp>
#include <nebula/content/scene/physics/base.hpp>
#include <nebula/content/actor/admin/rigid_dynamic.hpp>
#include <nebula/content/actor/physics/rigid_dynamic_box.hpp>
#include <nebula/content/actor/physics/controller.hpp>

#include <nebula/content/physics/base.hpp>

physx::PxFilterFlags	DefaultFilterShader(
		physx::PxFilterObjectAttributes attributes0,
		physx::PxFilterData filterData0,
		physx::PxFilterObjectAttributes attributes1,
		physx::PxFilterData filterData1,
		physx::PxPairFlags& pairFlags,
		const void* constantBlock,
		physx::PxU32 constantBlockSize )
{
	return physx::PxFilterFlag::eDEFAULT;
}

n36000::base::base( jess::shared_ptr<n30000::base> parent ):
	parent_(parent)
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
n36000::base::~base()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	n36000::base::init()
{
	jess::clog << NEB_FUNCSIG << std::endl;

	// Foundation
	px_foundation_ = PxCreateFoundation( PX_PHYSICS_VERSION, px_default_allocator_callback_, px_default_error_callback_ );
	jess::assertion( px_foundation_ );

	bool recordMemoryAllocations = true;

	// Profile Zone Manager
	px_profile_zone_manager_ = &::physx::PxProfileZoneManager::createProfileZoneManager( px_foundation_ );
	jess::assertion( px_profile_zone_manager_ );

	// Physics
	px_physics_ = PxCreatePhysics( PX_PHYSICS_VERSION, *px_foundation_, ::physx::PxTolerancesScale(), recordMemoryAllocations, px_profile_zone_manager_ );
	jess::assertion( px_physics_ );

	// cooking
	px_cooking_ = PxCreateCooking( PX_PHYSICS_VERSION, *px_foundation_, ::physx::PxCookingParams() );
	jess::assertion( px_cooking_ );

	// Extensions
	jess::assertion( ::PxInitExtensions( *px_physics_ ) );

	// Character controller manager
	px_character_controller_manager_ = ::PxCreateControllerManager( *px_foundation_ );

}
void	n36000::base::shutdown()
{
	jess::clog << NEB_FUNCSIG << std::endl;

	px_physics_->release();
	px_foundation_->release();
}
jess::shared_ptr<n32200::base>		n36000::base::create_scene()
{
	jess::clog << NEB_FUNCSIG << std::endl;

	jess::shared_ptr<n32200::base> scene( new n32200::base() );

	physx::PxSceneDesc scene_desc( px_physics_->getTolerancesScale() );

	scene_desc.gravity = physx::PxVec3(0,-9.81,0);

	scene->customize_scene_desc( scene_desc );

	int m_nbThreads = 1;

	// cpu dispatcher
	if( !scene_desc.cpuDispatcher )
	{
		::physx::PxDefaultCpuDispatcher* cpuDispatcher = ::physx::PxDefaultCpuDispatcherCreate( m_nbThreads );
		jess::assertion( cpuDispatcher );

		scene_desc.cpuDispatcher = cpuDispatcher;
	}

	// filter shader
	if( !scene_desc.filterShader )
	{
		if ( scene->px_default_filter_shader_ )
		{
			scene_desc.filterShader = scene->px_default_filter_shader_;
		}
		else
		{
			scene_desc.filterShader = DefaultFilterShader;
		}
	}

	// gpu dispatcher
#ifdef PX_WINDOWS
	if( !scene_desc.gpuDispatcher && m_cudaContextManager )
	{
		sceneDesc.gpuDispatcher = m_cudaContextManager->getGpuDispatcher();
	}
#endif

	jess::assertion( scene_desc.isValid() );

	scene->px_scene_ = px_physics_->createScene( scene_desc );

	jess::assertion( scene->px_scene_ );

	return scene;
}
jess::shared_ptr<n34200::rigid_dynamic>		n36000::base::create_rigid_dynamic(
		jess::shared_ptr<n32100::base> scene,
		jess::shared_ptr<n34100::base> actor
		)
{
	jess::clog << NEB_FUNCSIG << std::endl;

	// create
	jess::shared_ptr<n34200::rigid_dynamic> act( new n34200::rigid_dynamic( actor ) );

	// create
	physx::PxRigidDynamic* px_actor = px_physics_->createRigidDynamic( physx::PxTransform() );

	act->px_actor_ = px_actor;

	return act;
}
jess::shared_ptr<n34200::rigid_dynamic_box>	n36000::base::create_rigid_dynamic_box(
		jess::shared_ptr<n32100::base> scene,
		jess::shared_ptr<n34100::base> actor
		)
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	// create
	jess::shared_ptr<n34200::rigid_dynamic_box> physics( new n34200::rigid_dynamic_box( actor ) );
	
	// create
	physx::PxRigidDynamic* px_actor = px_physics_->createRigidDynamic( physx::PxTransform() );

	physics->px_actor_ = px_actor;

	return physics;
}
jess::shared_ptr<n34200::controller>		n36000::base::create_controller(
		jess::shared_ptr<n32100::base> scene,
		jess::shared_ptr<n34100::base> actor
		)
{
	jess::clog << NEB_FUNCSIG << std::endl;

	// create
	jess::shared_ptr<n34200::controller> act ( new n34200::controller( actor ) );

	// create
	physx::PxCapsuleControllerDesc desc;

	physx::PxController* px_cont = px_character_controller_manager_->createController( *px_physics_, scene->physics_->px_scene_, desc );

	act->px_controller_ = px_cont;

	return act;
}

void 	DefaultErrorCallback::reportError( ::physx::PxErrorCode::Enum code, const char *message, const char *file, int line)
{
	printf("%s:%i: %s\n",file,line,message);
}

