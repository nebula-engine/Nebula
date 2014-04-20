#ifndef __NEBULA_VEHICLE_MANAGER__
#define __NEBULA_VEHICLE_MANAGER__

#include <vector>

#include <PxPhysicsAPI.h>

#include <gru/actor/desc.hpp>

//Tire model friction for each combination of drivable surface type and tire type.
static const physx::PxU32 MAX_NUM_SURFACE_TYPES = 4;
static const physx::PxU32 MAX_NUM_TIRE_TYPES = 4;


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

static const physx::PxF32 gTireFrictionMultipliers[MAX_NUM_SURFACE_TYPES][MAX_NUM_TIRE_TYPES] =
{
	//WETS  SLICKS  ICE     MUD
	{0.95f, 0.95f,  0.95f,  0.95f},         //MUD
	{1.10f, 1.15f,  1.10f,  1.10f},         //TARMAC
	{0.70f, 0.70f,  0.70f,  0.70f},         //ICE
	{0.80f, 0.80f,  0.80f,  0.80f}          //GRASS
};
physx::PxSceneQueryHitType::Enum VehicleWheelRaycastPreFilter(
		physx::PxFilterData filterData0,
		physx::PxFilterData filterData1,
		const void* constantBlock,
		physx::PxU32 constantBlockSize,
		physx::PxSceneQueryFilterFlags& filterFlags);


class SampleVehicleSceneQueryData
{
	public:
		//Allocate scene query data for up to maxNumWheels suspension raycasts.
		static SampleVehicleSceneQueryData* allocate(const physx::PxU32 maxNumWheels);

		//Free allocated buffer for scene queries of suspension raycasts.
		void free();

		//Create a PxBatchQuery instance that will be used as a single batched raycast of multiple suspension lines of multiple vehicles
		physx::PxBatchQuery* setUpBatchedSceneQuery(physx::PxScene* scene);

		//Get the buffer of scene query results that will be used by PxVehicleNWSuspensionRaycasts
		physx::PxRaycastQueryResult* getRaycastQueryResultBuffer() {return mSqResults;}

		//Get the number of scene query results that have been allocated for use by PxVehicleNWSuspensionRaycasts
		physx::PxU32 getRaycastQueryResultBufferSize() const {return mNumQueries;}

		//Set the pre-filter shader 
		void setPreFilterShader(physx::PxBatchQueryPreFilterShader preFilterShader) {mPreFilterShader=preFilterShader;}

		//Set the spu pre-filter shader (essential to run filtering on spu)
		void setSpuPreFilterShader(void* spuPreFilterShader, const physx::PxU32 spuPreFilterShaderSize) {mSpuPreFilterShader=spuPreFilterShader; mSpuPreFilterShaderSize=spuPreFilterShaderSize;}

	private:

		//One result for each wheel.
		physx::PxRaycastQueryResult* mSqResults;

		//One hit for each wheel.
		physx::PxRaycastHit* mSqHitBuffer;

		//Filter shader used to filter drivable and non-drivable surfaces
		physx::PxBatchQueryPreFilterShader mPreFilterShader;

		//Ptr to compiled spu filter shader 
		//Set this on ps3 for spu raycasts
		void* mSpuPreFilterShader;

		//Size of compiled spu filter shader 
		//Set this on ps3 for spu raycasts.
		physx::PxU32 mSpuPreFilterShaderSize;

		//Maximum number of suspension raycasts that can be supported by the allocated buffers 
		//assuming a single query and hit per suspension line.
		physx::PxU32 mNumQueries;

		physx::PxU32 mPad[2];

		void init()
		{
			mPreFilterShader = VehicleWheelRaycastPreFilter;
			mSpuPreFilterShader=NULL;
			mSpuPreFilterShaderSize=0;
		}

		SampleVehicleSceneQueryData()
		{
			init();
		}

		~SampleVehicleSceneQueryData()
		{
		}
};

namespace neb
{
	namespace actor
	{
		class vehicle;
	}
	class vehicle_manager
	{
		public:
			typedef std::shared_ptr<neb::actor::vehicle> vehicle_t;

			enum surface_type
			{
				MUD = 0, TARMAC = 1, ICE = 2, GRASS = 3
			};

			vehicle_manager();

			void			setup_surface_tire_pairs();
			void			setup_sq_data();

			void			vehicle_suspension_raycasts(physx::PxScene* scene);
			void			update(const physx::PxF32, const physx::PxVec3&);
			vehicle_t		create_vehicle(
					physx::PxPhysics*,
					physx::PxScene*,
					glutpp::actor::desc_s);

			physx::PxVehicleDrivableSurfaceToTireFrictionPairs*	surface_tire_pairs_;


			physx::PxBatchQuery*				sq_wheel_raycast_batch_query_;
			std::vector<physx::PxVehicleWheels*>		vehicle_wheels_;
			SampleVehicleSceneQueryData*			sq_data_;
	};
}

#endif
