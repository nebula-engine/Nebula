#include <assert.h>
#include <memory>

#include <PxPhysicsAPI.h>

#include <neb/actor/Rigid_Dynamic_Box.h>
#include <neb/physics.h>
#include <neb/scene.h>


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
	// let triggers through
        if(physx::PxFilterObjectIsTrigger(attributes0) || physx::PxFilterObjectIsTrigger(attributes1))
        {
                pairFlags = physx::PxPairFlag::eTRIGGER_DEFAULT;
                return physx::PxFilterFlag::eDEFAULT;
        }
	
        // generate contacts for all that were not filtered above
        pairFlags = physx::PxPairFlag::eCONTACT_DEFAULT;

        // trigger the contact callback for pairs (A,B) where
        // the filtermask of A contains the ID of B and vice versa.
        if((filterData0.word0 & filterData1.word1) && (filterData1.word0 & filterData0.word1))
                pairFlags |= physx::PxPairFlag::eNOTIFY_TOUCH_FOUND;
	
	return physx::PxFilterFlag::eDEFAULT;
}

void 	DefaultErrorCallback::reportError( physx::PxErrorCode::Enum code, char const * message, char const * file, int line)
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
void	neb::physics::Init()
{
	// Physx
	// Foundation
	px_foundation_ = PxCreateFoundation( PX_PHYSICS_VERSION, px_default_allocator_callback_, px_default_error_callback_ );
	assert( px_foundation_ );

	bool recordMemoryAllocations = true;

	// Profile Zone Manager
	px_profile_zone_manager_ = &::physx::PxProfileZoneManager::createProfileZoneManager( px_foundation_ );
	assert( px_profile_zone_manager_ );

	// Physics
	px_physics_ = PxCreatePhysics( PX_PHYSICS_VERSION, *px_foundation_, ::physx::PxTolerancesScale(), recordMemoryAllocations, px_profile_zone_manager_ );
	assert( px_physics_ );

	// cooking
	px_cooking_ = PxCreateCooking( PX_PHYSICS_VERSION, *px_foundation_, ::physx::PxCookingParams() );
	assert( px_cooking_ );

	// Extensions
	assert( PxInitExtensions( *px_physics_ ) );

	// character controller manager
	px_character_controller_manager_ = ::PxCreateControllerManager( *px_foundation_ );
	assert( px_character_controller_manager_ );


}
void				neb::physics::Shutdown()
{
	//jess::clog << neb_FUNCSIG << std::endl;

	px_physics_->release();
	px_foundation_->release();
}
std::shared_ptr<neb::scene>	neb::physics::Create_Scene(TiXmlElement* el_scene)
{
	//jess::clog << neb_FUNCSIG << std::endl;
	
	std::shared_ptr<neb::scene> scene(new neb::scene);
	
	physx::PxSceneDesc scene_desc( px_physics_->getTolerancesScale() );
	
	scene_desc.gravity = physx::PxVec3(0.0f, -1.0f, 0.0f);
	scene_desc.flags |= physx::PxSceneFlag::eENABLE_ACTIVETRANSFORMS;

	int m_nbThreads = 1;

	// cpu dispatcher
	if( !scene_desc.cpuDispatcher )
	{
		physx::PxDefaultCpuDispatcher* cpuDispatcher = ::physx::PxDefaultCpuDispatcherCreate( m_nbThreads );
		assert( cpuDispatcher );

		scene_desc.cpuDispatcher = cpuDispatcher;
	}

	// filter shader
	if( !scene_desc.filterShader )
	{
		if ( scene->px_filter_shader_ )
		{
			scene_desc.filterShader = scene->px_filter_shader_;
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
	assert( scene_desc.isValid() );

	scene->px_scene_ = px_physics_->createScene(scene_desc);
	assert(scene->px_scene_);
	
	// actors
	scene->Create_Actors(el_scene);
	
	return scene;
}
/*std::shared_ptr<n34200::rigid_dynamic>		neb::physics::create_rigid_dynamic(
  std::shared_ptr<n32100::base> scene,
  std::shared_ptr<n34100::base> actor
  )
  {
//jess::clog << neb_FUNCSIG << std::endl;

// create
std::shared_ptr<n34200::rigid_dynamic> act( new n34200::rigid_dynamic( actor ) );

// create
physx::PxRigidDynamic* px_actor = px_physics_->createRigidDynamic( physx::PxTransform() );

px_actor->userData = actor.get();

act->px_actor_ = px_actor;

return act;
}*/
/*std::shared_ptr<n34200::rigid_static_plane>	neb::physics::create_rigid_static_plane(
  std::shared_ptr<n32100::base> scene,
  std::shared_ptr<n34100::base> actor
  )
  {
  jess::scoped_ostream sos( &jess::cout, neb_FUNCSIG );

// create
std::shared_ptr<n34200::rigid_static_plane> physics( new n34200::rigid_static_plane( actor ) );

physx::PxTransform pose( physx::PxVec3(0,-2,0), physx::PxQuat( 0, physx::PxVec3(1,0,0) ) );

// create
physx::PxRigidStatic* px_actor = px_physics_->createRigidStatic( pose );

px_actor->userData = actor.get();

physics->px_actor_ = px_actor;

// init
init_rigid_actor( physics );

return physics;
}
void						neb::Physics::init_rigid_actor( std::shared_ptr<n34200::rigid_actor> actor )
{
actor->material_ = default_material_;
}*/
/*std::shared_ptr<n34200::controller>		neb::Physics::create_controller(
  std::shared_ptr<n32100::base> scene,
  std::shared_ptr<n34100::base> actor
  )
  {
  jess::scoped_ostream( &jess::clog, neb_FUNCSIG );

// create
std::shared_ptr<n34200::controller> physics ( new n34200::controller( actor ) );

physics->material_ = request_physics_material();
neb_ASSERT( physics->material_->px_material_ );

// description 
physx::PxExtendedVec3 position( 0, 0, -5.0 );

physx::PxCapsuleControllerDesc desc;
desc.position = position;
desc.height = 1.0;
desc.radius = 0.5;
desc.scaleCoeff = 1.0;
desc.volumeGrowth = 2.0;
desc.density = 1000.0;
desc.slopeLimit = 0.707;
desc.stepOffset = 1.0;
desc.contactOffset = 1.0;
desc.material = physics->material_->px_material_;
desc.climbingMode = physx::PxCapsuleClimbingMode::eEASY;
desc.userData = actor.get();


// assert
neb_ASSERT( px_character_controller_manager_ );
neb_ASSERT( px_physics_ );
neb_ASSERT( scene->physics_->px_scene_ );
neb_ASSERT( desc.isValid() );

physx::PxController* px_cont = px_character_controller_manager_->createController( *px_physics_, scene->physics_->px_scene_, desc );

physics->px_controller_ = px_cont;


neb_ASSERT( px_cont );

return physics;
}
std::shared_ptr<n35200::box>			neb::Physics::create_box(
std::shared_ptr<n35100::box> box
)
{
jess::scoped_ostream sos( &jess::cout, neb_FUNCSIG );

std::shared_ptr<n35100::base> base = std::static_pointer_cast<n35100::base>( box );

// create
std::shared_ptr<n35200::box> box_physics( new n35200::box( base ) );



// admin rigid_actor
//std::shared_ptr<n34100::rigid_actor> ad_act = parent_.lock()->parent_.lock();

// physics rigid_actor
//std::shared_ptr<n34200::rigid_actor> ph_act = std::dynamic_pointer_cast<n34200::rigid_actor>( ad_act->physics_ );

// physx rigid_actor
//std::shared_ptr<n34200p::rigid_actor> ph_px_act = std::dynamic_pointer_cast<n34200::physx::rigid_actor>( ph_act );

// Pxrigid_actor


// physx material
//std::shared_ptr<n34200p::material> mat = std::dynamic_pointer_cast<n34200p::material>( ad_act->materials_.at(0)->physics_ );
//jess::assertion( bool(mat) ); //throw jess::except("no material");

neb_ASSERT( bool( box ) );
neb_ASSERT( !box->parent_.expired() );

std::shared_ptr<n34200::rigid_actor> actor_physics = std::dynamic_pointer_cast<n34200::rigid_actor>( box->parent_.lock()->physics_ );
neb_ASSERT( bool( actor_physics ) );
neb_ASSERT( bool( actor_physics->material_ ) );


physx::PxRigidActor* px_rigid_actor = (::physx::PxRigidActor*)( actor_physics->px_actor_ );

// PxMaterial
physx::PxMaterial* px_mat = actor_physics->material_->px_material_;
neb_ASSERT( bool( px_mat ) );

// geometry
physx::PxBoxGeometry px_geometry( 1, 1, 1 );

// PxShape
box_physics->px_shape_ = px_rigid_actor->createShape( px_geometry, *px_mat );



return box_physics;
}
std::shared_ptr<n35200::plane>			neb::Physics::create_plane(
		std::shared_ptr<n35100::plane> plane
		)
{
	jess::scoped_ostream sos( &jess::cout, neb_FUNCSIG );

	std::shared_ptr<n35100::base> base = std::static_pointer_cast<n35100::base>( plane );

	// create
	std::shared_ptr<n35200::plane> plane_physics( new n35200::plane( base ) );



	// admin rigid_actor
	std::shared_ptr<n34100::rigid_actor> actor = plane->parent_.lock();

	// physics rigid_actor
	std::shared_ptr<n34200::rigid_actor> ph_act = std::dynamic_pointer_cast<n34200::rigid_actor>( ad_act->physics_ );

	// physx rigid_actor
	std::shared_ptr<n34200p::rigid_actor> ph_px_act = std::dynamic_pointer_cast<n34200::physx::rigid_actor>( ph_act );

	// Pxrigid_actor
	/		

		// physx material
		std::shared_ptr<n34200::material> mat = default_material_;
	//jess::assertion( bool(mat) ); //throw jess::except("no material");


	std::shared_ptr<n34200::rigid_actor> actor_physics= std::dynamic_pointer_cast<n34200::rigid_actor>( actor->physics_ );

	physx::PxRigidActor* px_rigid_actor = (::physx::PxRigidActor*)( actor_physics->px_actor_ );

	// PxMaterial
	physx::PxMaterial* px_mat = actor_physics->material_->px_material_;
	neb_ASSERT( bool( px_mat ) );

	// geometry
	physx::PxPlaneGeometry px_geometry;

	physx::PxTransform pose( physx::PxVec3(0,0,0), physx::PxQuat( -1.0f * physx::PxPi / 2.0f, physx::PxVec3(0,0,1) ) );

	// PxShape
	plane_physics->px_shape_ = px_rigid_actor->createShape( px_geometry, *px_mat, pose );


	return plane_physics;
}
std::shared_ptr<n34200::material>		neb::Physics::request_physics_material()
{
	neb_ASSERT( bool( default_material_ ) );
	return default_material_;
}
std::shared_ptr<n34200::material>		neb::Physics::create_physics_material()
{
	std::shared_ptr<n34200::material> material( new n34200::material );

	material->px_material_ = px_physics_->createMaterial(1,1,1);

	return material;
}


void 	DefaultErrorCallback::reportError( physx::PxErrorCode::Enum code, char const * message, char const * file, int line)
{
	printf("%s:%i: %s\n",file,line,message);
}
*/
