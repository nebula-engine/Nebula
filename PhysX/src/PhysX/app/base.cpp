#include <assert.h>

//#include <math/free.hpp>

#include <PxPhysicsAPI.h>


//#include <Nebula/Physics.hh>
#include <Nebula/Scene/Base.hh>


#include <PhysX/simulation_callback.hh>

#include <PhysX/app/base.hpp>

sp::shared_ptr<phx::app::base> phx::app::base::g_app_;

physx::PxFilterFlags	DefaultFilterShader(
		physx::PxFilterObjectAttributes attributes0,
		physx::PxFilterData filterData0,
		physx::PxFilterObjectAttributes attributes1,
		physx::PxFilterData filterData1,
		physx::PxPairFlags& pairFlags,
		const void* constantBlock,
		physx::PxU32 constantBlockSize )
{	
	//printf("%s\n",__PRETTY_FUNCTION__);
	
	//printf("%i %i %i %i\n", filterData0.word0, filterData1.word1, filterData1.word0, filterData0.word1);
	
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

	if(w0 && w1) {
		pairFlags |= physx::PxPairFlag::eCONTACT_DEFAULT;
		
		filter_flags = physx::PxFilterFlag::eDEFAULT;	
	} else {
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
/*phx::app::base::Physics()
  {
//	jess::clog << neb_FUNCSIG << std::endl;
}
phx::app::base::~base()
{
//	jess::clog << neb_FUNCSIG << std::endl;
}*/
phx::app::base::base(): px_physics_(NULL) {
}
void	phx::app::base::init() {
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
	/** @todo fix cooking signature */
	//px_cooking_ = PxCreateCooking( PX_PHYSICS_VERSION, *px_foundation_, ::physx::PxCookingParams() );
	assert( px_cooking_ );

	// Extensions
	assert( PxInitExtensions( *px_physics_ ) );

	// character controller manager
	/** @todo fix cooking signature */
	//px_character_controller_manager_ = ::PxCreateControllerManager( *px_foundation_ );
	assert( px_character_controller_manager_ );

	// vehicle
	assert( PxInitVehicleSDK(*px_physics_) );
	PxVehicleSetBasisVectors(physx::PxVec3(0,1,0), physx::PxVec3(0,0,-1));
	PxVehicleSetUpdateMode(physx::PxVehicleUpdateMode::Enum::eACCELERATION);
}
void				phx::app::base::release() {
	//jess::clog << neb_FUNCSIG << std::endl;
	printf("%s\n",__PRETTY_FUNCTION__);

	physx::PxCloseVehicleSDK();

	px_physics_->release();
	px_foundation_->release();
}
sp::shared_ptr<phx::app::base>			phx::app::base::global() {
	return g_app_;
}







