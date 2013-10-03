#include <jess/free.hpp>

#include <nebula/content/physics/physx/base.hpp>
#include <nebula/content/physics/physx/free.hpp>

#include <nebula/content/scene/physics/physx/base.hpp>

#include <nebula/content/actor/admin/rigid_dynamic.hpp>
#include <nebula/content/actor/physics/physx/rigid_dynamic.hpp>

#include <nebula/content/actor/admin/controller.hpp>
#include <nebula/content/actor/physics/physx/controller.hpp>

#include <nebula/content/scene/admin/base.hpp>

::physx::PxFilterFlags DefaultFilterShader
(
	::physx::PxFilterObjectAttributes attributes0,
	::physx::PxFilterData filterData0,
	::physx::PxFilterObjectAttributes attributes1,
	::physx::PxFilterData filterData1,
	::physx::PxPairFlags& pairFlags,
	const void* constantBlock,
	::physx::PxU32 constantBlockSize
)
{
	return ::physx::PxFilterFlag::eDEFAULT;
}

void	ncpp::base::init( const boost::shared_ptr<nebula::content::base>& parent )
{
	//PRINTSIG;
	ncp::base::init( parent );

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
void	ncpp::base::shutdown()
{
	px_physics_->release();
	px_foundation_->release();
}
void	ncpp::base::register_scene( const boost::shared_ptr<nc_sc_a::base>& scn )
{
	//PRINTSIG;
	//CO_SC_PH_PX_Scene* physicsScenePhysX = (CO_SC_PH_PX_Scene*)scene->GetPhysicsScene();
	boost::shared_ptr<nc_sc_pp::base> scene_physics = boost::dynamic_pointer_cast<nc_sc_pp::base>( scn->physics_.get() );
	//if ( !physicsScenePhysX ) throw Except("dynamic_cast returned null");
	
	::physx::PxSceneDesc scene_desc( px_physics_->getTolerancesScale() );
	
	scene_desc.gravity = ::physx::PxVec3(0.0f, -9.81f, 0.0f);
	
	scene_physics->customize_scene_desc( scene_desc );
	
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
		if ( scene_physics->px_default_filter_shader_ )
		{
			scene_desc.filterShader = scene_physics->px_default_filter_shader_;
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

	scene_physics->px_scene_ = px_physics_->createScene( scene_desc );
	jess::assertion( scene_physics->px_scene_ );
	
}
void	ncpp::base::register_rigid_dynamic( const boost::shared_ptr<ncaa::rigid_dynamic>& act )
{
	boost::shared_ptr<ncapp::rigid_dynamic> act_physics = boost::dynamic_pointer_cast<ncapp::rigid_dynamic>( act->physics_.get() );
	
	// get transform
	::physx::PxTransform px_trans = ncpp::boost_to_physx( act->get_pose() );
	
	// create PxRigidDynamic
	::physx::PxRigidDynamic* px_act = px_physics_->createRigidDynamic( px_trans );
	
	// pass PxRigidDynamic to rigid_dynamic
	act_physics->set_px_actor( px_act );
}
void	ncpp::base::register_controller( const boost::shared_ptr<ncaa::controller>& act )
{
	// Get actor's physics object
	boost::shared_ptr<ncapp::controller> act_phy = boost::dynamic_pointer_cast<ncapp::controller>( act->physics_.get() );
	
	//CO_SC_PH_PX_Scene* physicsScenePhysX = (CO_SC_PH_PX_Scene*)scene->GetPhysicsScene();
	boost::shared_ptr<nc_sc_pp::base> scn_phy = boost::dynamic_pointer_cast<nc_sc_pp::base>( act->parent_.lock()->physics_.get() );
	//if ( !physicsScenePhysX ) throw Except("dynamic_cast returned null");
	
	
	::physx::PxCapsuleControllerDesc desc;
	
	// Create PxController
	::physx::PxController* px_cont = px_character_controller_manager_->createController( *px_physics_, scn_phy->get_px_scene(), desc );
	
	
	act_phy->set_px_controller( px_cont );


}
void 	DefaultErrorCallback::reportError( ::physx::PxErrorCode::Enum code, const char *message, const char *file, int line)
{
	printf("%s:%i: %s\n",file,line,message);
}




