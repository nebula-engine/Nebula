#ifndef __NEBULA_VEHICLE_MANAGER__
#define __NEBULA_VEHICLE_MANAGER__

#include <vector>

#include <PxPhysicsAPI.h>

//Tire model friction for each combination of drivable surface type and tire type.

static const physx::PxU32 MAX_NUM_SURFACE_TYPES = 4;
static const physx::PxU32 MAX_NUM_TIRE_TYPES = 4;

static const physx::PxU32 UNDRIVABLE_SURFACE = 32;
static const physx::PxU32 DRIVABLE_SURFACE = 64;

static const physx::PxU32 COLLISION_FLAG_WHEEL = 32;
static const physx::PxU32 COLLISION_FLAG_WHEEL_AGAINST = 32;
static const physx::PxU32 COLLISION_FLAG_CHASSIS = 32;
static const physx::PxU32 COLLISION_FLAG_CHASSIS_AGAINST = 32;

static const physx::PxVec3 chassis_verts[] = {
	physx::PxVec3( 1.5, 0.5, 3),
	physx::PxVec3( 1.5, 0.5,-3),
	physx::PxVec3(-1.5, 0.5,-3),
	physx::PxVec3(-1.5, 0.5, 3),
	physx::PxVec3( 1.5,-0.5, 3),
	physx::PxVec3( 1.5,-0.5,-3),
	physx::PxVec3(-1.5,-0.5,-3),
	physx::PxVec3(-1.5,-0.5, 3)
};
static const physx::PxVec3 wheel_verts[] = {
	physx::PxVec3( 0.25, 0.500, 0.000),
	physx::PxVec3( 0.25, 0.354, 0.354),
	physx::PxVec3( 0.25, 0.000, 0.500),
	physx::PxVec3( 0.25,-0.354, 0.354),
	physx::PxVec3( 0.25,-0.500, 0.000),
	physx::PxVec3( 0.25,-0.354,-0.354),
	physx::PxVec3( 0.25, 0.000,-0.500),
	physx::PxVec3( 0.25, 0.354,-0.354),
	physx::PxVec3(-0.25, 0.500, 0.000),
	physx::PxVec3(-0.25, 0.354, 0.354),
	physx::PxVec3(-0.25, 0.000, 0.500),
	physx::PxVec3(-0.25,-0.354, 0.354),
	physx::PxVec3(-0.25,-0.500, 0.000),
	physx::PxVec3(-0.25,-0.354,-0.354),
	physx::PxVec3(-0.25, 0.000,-0.500),
	physx::PxVec3(-0.25, 0.354,-0.354)
};

/*
static physx::PxF32 gTireFrictionMultipliers[MAX_NUM_SURFACE_TYPES][MAX_NUM_TIRE_TYPES] =
{
	//WETS  SLICKS  ICE             MUD
	{0.95f, 0.95f,  0.95f,  0.95f},         //MUD
	{1.10f, 1.15f,  1.10f,  1.10f},         //TARMAC
	{0.70f, 0.70f,  0.70f,  0.70f},         //ICE
	{0.80f, 0.80f,  0.80f,  0.80f}          //GRASS
};
*/
/*
static physx::PxSceneQueryHitType::Enum VehicleWheelRaycastPreFilter(
		physx::PxFilterData filterData0,
		physx::PxFilterData filterData1,
		const void* constantBlock,
		physx::PxU32 constantBlockSize,
		physx::PxSceneQueryFilterFlags& filterFlags)
{
	//filterData0 is the vehicle suspension raycast.
	//filterData1 is the shape potentially hit by the raycast.
	PX_UNUSED(filterFlags);
	PX_UNUSED(constantBlockSize);
	PX_UNUSED(constantBlock);
	PX_ASSERT(filterData0.word3 & UNDRIVABLE_SURFACE);

	return ((0 == (filterData1.word3 & DRIVABLE_SURFACE)) ? physx::PxSceneQueryHitType::eNONE : physx::PxSceneQueryHitType::eBLOCK);
}
*/


namespace neb
{
	namespace actor
	{
		class vehicle;
	}
	class vehicle_manager
	{
		public:
			vehicle_manager();
			void					setup_surface_tire_pairs();
			void					vehicle_suspension_raycasts(physx::PxScene* scene);
			void					update(const physx::PxF32, const physx::PxVec3&);
			std::shared_ptr<neb::actor::vehicle>	create_vehicle(physx::PxPhysics*, physx::PxScene*);

			physx::PxVehicleDrivableSurfaceToTireFrictionPairs*	surface_tire_pairs_;


			physx::PxBatchQuery*					sq_wheel_raycast_batch_query_;
			std::vector<physx::PxVehicleWheels*>			vehicle_wheels_;
			//sq_data_;
	};
}

#endif
