#include <neb/physics.h>
#include <neb/vehicle_manager.h>

neb::vehicle_manager::vehicle_manager():
	sq_wheel_raycast_batch_query_(NULL)
{}
void neb::vehicle_manager::setup_surface_tire_pairs() {

	physx::PxMaterial* drivableSurfaceMaterials[16];
	physx::PxVehicleDrivableSurfaceType drivableSurfaceTypes[4];

	
	surface_tire_pairs_ = physx::PxVehicleDrivableSurfaceToTireFrictionPairs::allocate(MAX_NUM_TIRE_TYPES,MAX_NUM_SURFACE_TYPES);
	
	surface_tire_pairs_->setup(
			MAX_NUM_TIRE_TYPES,
			MAX_NUM_SURFACE_TYPES,
			(const physx::PxMaterial**)drivableSurfaceMaterials,
			drivableSurfaceTypes);

	for(physx::PxU32 i=0;i<MAX_NUM_SURFACE_TYPES;i++)
	{
		for(physx::PxU32 j=0;j<MAX_NUM_TIRE_TYPES;j++)
		{
			surface_tire_pairs_->setTypePairFriction(i,j,gTireFrictionMultipliers[i][j]);
		}
	}
}



physx::PxVec3 computeChassisAABBDimensions(physx::PxConvexMesh* chassisConvexMesh)
{
	return physx::PxVec3(3,1,6);
}
void computeWheelWidthsAndRadii(
		physx::PxConvexMesh** wheelConvexMeshes,
		physx::PxF32 * const wheelWidths,
		physx::PxF32 * const wheelRadii)
{

	for(int i = 0; i < 4; ++i)
	{
		wheelWidths[i] = 0.5;
		wheelRadii[i] = 1.0;
	}
}
void createVehicle4WSimulationData(
		const physx::PxF32 chassisMass,
		physx::PxConvexMesh* chassisConvexMesh,
		const physx::PxF32 wheelMass,
		physx::PxConvexMesh** wheelConvexMeshes,
		const physx::PxVec3* wheelCentreOffsets,
		physx::PxVehicleWheelsSimData& wheelsData,
		physx::PxVehicleDriveSimData4W& driveData, 
		physx::PxVehicleChassisData& chassisData)
{
	//Extract the chassis AABB dimensions from the chassis convex mesh.
	const physx::PxVec3 chassisDims = computeChassisAABBDimensions(chassisConvexMesh);

	//The origin is at the center of the chassis mesh.
	//Set the center of mass to be below this point and a little towards the front.
	const physx::PxVec3 chassisCMOffset = physx::PxVec3(0.0f,-chassisDims.y*0.5f+0.65f,0.25f);

	//Now compute the chassis mass and moment of inertia.
	//Use the moment of inertia of a cuboid as an approximate value for the chassis moi.
	physx::PxVec3 chassisMOI
		((chassisDims.y*chassisDims.y + chassisDims.z*chassisDims.z)*chassisMass/12.0f,
		 (chassisDims.x*chassisDims.x + chassisDims.z*chassisDims.z)*chassisMass/12.0f,
		 (chassisDims.x*chassisDims.x + chassisDims.y*chassisDims.y)*chassisMass/12.0f);
	//A bit of tweaking here.  The car will have more responsive turning if we reduce the
	//y-component of the chassis moment of inertia.
	chassisMOI.y*=0.8f;

	//Let's set up the chassis data structure now.
	chassisData.mMass=chassisMass;
	chassisData.mMOI=chassisMOI;
	chassisData.mCMOffset=chassisCMOffset;

	//Work out the front/rear mass split from the cm offset.
	//This is a very approximate calculation with lots of assumptions.
	//massRear*zRear + massFront*zFront = mass*cm           (1)
	//massRear       + massFront        = mass                      (2)
	//Rearrange (2)
	//massFront = mass - massRear                                           (3)
	//Substitute (3) into (1)
	//massRear(zRear - zFront) + mass*zFront = mass*cm      (4)
	//Solve (4) for massRear
	//massRear = mass(cm - zFront)/(zRear-zFront)           (5)
	//Now we also have
	//zFront = (z-cm)/2                                                                     (6a)
	//zRear = (-z-cm)/2                                                                     (6b)
	//Substituting (6a-b) into (5) gives
	//massRear = 0.5*mass*(z-3cm)/z                                         (7)
	const physx::PxF32 massRear=0.5f*chassisMass*(chassisDims.z-3*chassisCMOffset.z)/chassisDims.z;
	const physx::PxF32 massFront=chassisMass-massRear;

	//Extract the wheel radius and width from the wheel convex meshes.
	physx::PxF32 wheelWidths[4];
	physx::PxF32 wheelRadii[4];
	computeWheelWidthsAndRadii(wheelConvexMeshes,wheelWidths,wheelRadii);

	//Now compute the wheel masses and inertias components around the axle's axis.
	//http://en.wikipedia.org/wiki/List_of_moments_of_inertia
	physx::PxF32 wheelMOIs[4];
	for(physx::PxU32 i=0;i<4;i++)
	{
		wheelMOIs[i]=0.5f*wheelMass*wheelRadii[i]*wheelRadii[i];
	}
	//Let's set up the wheel data structures now with radius, mass, and moi.
	physx::PxVehicleWheelData wheels[4];
	for(physx::PxU32 i=0;i<4;i++)
	{
		wheels[i].mRadius=wheelRadii[i];
		wheels[i].mMass=wheelMass;
		wheels[i].mMOI=wheelMOIs[i];
		wheels[i].mWidth=wheelWidths[i];
	}
	//Disable the handbrake from the front wheels and enable for the rear wheels
	wheels[physx::PxVehicleDrive4W::eFRONT_LEFT_WHEEL].mMaxHandBrakeTorque=0.0f;
	wheels[physx::PxVehicleDrive4W::eFRONT_RIGHT_WHEEL].mMaxHandBrakeTorque=0.0f;
	wheels[physx::PxVehicleDrive4W::eREAR_LEFT_WHEEL].mMaxHandBrakeTorque=4000.0f;
	wheels[physx::PxVehicleDrive4W::eREAR_RIGHT_WHEEL].mMaxHandBrakeTorque=4000.0f;
	//Enable steering for the front wheels and disable for the front wheels.
	wheels[physx::PxVehicleDrive4W::eFRONT_LEFT_WHEEL].mMaxSteer=physx::PxPi*0.3333f;
	wheels[physx::PxVehicleDrive4W::eFRONT_RIGHT_WHEEL].mMaxSteer=physx::PxPi*0.3333f;
	wheels[physx::PxVehicleDrive4W::eREAR_LEFT_WHEEL].mMaxSteer=0.0f;
	wheels[physx::PxVehicleDrive4W::eREAR_RIGHT_WHEEL].mMaxSteer=0.0f;

	enum
	{
		TIRE_TYPE_SLICKS,
		TIRE_TYPE_WETS
	};

	//Let's set up the tire data structures now.
	//Put slicks on the front tires and wets on the rear tires.
	physx::PxVehicleTireData tires[4];
	tires[physx::PxVehicleDrive4W::eFRONT_LEFT_WHEEL].mType=TIRE_TYPE_SLICKS;
	tires[physx::PxVehicleDrive4W::eFRONT_RIGHT_WHEEL].mType=TIRE_TYPE_SLICKS;
	tires[physx::PxVehicleDrive4W::eREAR_LEFT_WHEEL].mType=TIRE_TYPE_WETS;
	tires[physx::PxVehicleDrive4W::eREAR_RIGHT_WHEEL].mType=TIRE_TYPE_WETS;

	//Let's set up the suspension data structures now.
	physx::PxVehicleSuspensionData susps[4];
	for(physx::PxU32 i=0;i<4;i++)
	{
		susps[i].mMaxCompression=0.3f;
		susps[i].mMaxDroop=0.1f;
		susps[i].mSpringStrength=35000.0f;
		susps[i].mSpringDamperRate=4500.0f;
	}
	susps[physx::PxVehicleDrive4W::eFRONT_LEFT_WHEEL].mSprungMass=massFront*0.5f;
	susps[physx::PxVehicleDrive4W::eFRONT_RIGHT_WHEEL].mSprungMass=massFront*0.5f;
	susps[physx::PxVehicleDrive4W::eREAR_LEFT_WHEEL].mSprungMass=massRear*0.5f;
	susps[physx::PxVehicleDrive4W::eREAR_RIGHT_WHEEL].mSprungMass=massRear*0.5f;

	//We need to set up geometry data for the suspension, wheels, and tires.
	//We already know the wheel centers described as offsets from the rigid body centre of mass.
	//From here we can approximate application points for the tire and suspension forces.
	//Lets assume that the suspension travel directions are absolutely vertical.
	//Also assume that we apply the tire and suspension forces 30cm below the centre of mass.
	physx::PxVec3 suspTravelDirections[4] = {
		physx::PxVec3(0,-1,0),
		physx::PxVec3(0,-1,0),
		physx::PxVec3(0,-1,0),
		physx::PxVec3(0,-1,0)};

	physx::PxVec3 wheelCentreCMOffsets[4];
	physx::PxVec3 suspForceAppCMOffsets[4];
	physx::PxVec3 tireForceAppCMOffsets[4];
	for(physx::PxU32 i=0;i<4;i++)
	{
		wheelCentreCMOffsets[i]=wheelCentreOffsets[i]-chassisCMOffset;
		suspForceAppCMOffsets[i]=physx::PxVec3(wheelCentreCMOffsets[i].x,-0.3f,wheelCentreCMOffsets[i].z);
		tireForceAppCMOffsets[i]=physx::PxVec3(wheelCentreCMOffsets[i].x,-0.3f,wheelCentreCMOffsets[i].z);
	}

	//Now add the wheel, tire and suspension data.
	for(physx::PxU32 i=0;i<4;i++)
	{
		wheelsData.setWheelData(i,wheels[i]);
		wheelsData.setTireData(i,tires[i]);
		wheelsData.setSuspensionData(i,susps[i]);
		wheelsData.setSuspTravelDirection(i,suspTravelDirections[i]);
		wheelsData.setWheelCentreOffset(i,wheelCentreCMOffsets[i]);
		wheelsData.setSuspForceAppPointOffset(i,suspForceAppCMOffsets[i]);
		wheelsData.setTireForceAppPointOffset(i,tireForceAppCMOffsets[i]);
	}

	//Now set up the differential, engine, gears, clutch, and ackermann steering.

	//Diff
	physx::PxVehicleDifferential4WData diff;
	diff.mType=physx::PxVehicleDifferential4WData::eDIFF_TYPE_LS_4WD;
	driveData.setDiffData(diff);

	//Engine
	physx::PxVehicleEngineData engine;
	engine.mPeakTorque=500.0f;
	engine.mMaxOmega=600.0f;//approx 6000 rpm
	driveData.setEngineData(engine);

	//Gears
	physx::PxVehicleGearsData gears;
	gears.mSwitchTime=0.5f;
	driveData.setGearsData(gears);

	//Clutch
	physx::PxVehicleClutchData clutch;
	clutch.mStrength=10.0f;
	driveData.setClutchData(clutch);

	//Ackermann steer accuracy
	physx::PxVehicleAckermannGeometryData ackermann;
	ackermann.mAccuracy=1.0f;
	ackermann.mAxleSeparation =
		wheelCentreOffsets[physx::PxVehicleDrive4W::eFRONT_LEFT_WHEEL].z -
		wheelCentreOffsets[physx::PxVehicleDrive4W::eREAR_LEFT_WHEEL].z;

	ackermann.mFrontWidth =
		wheelCentreOffsets[physx::PxVehicleDrive4W::eFRONT_RIGHT_WHEEL].x -
		wheelCentreOffsets[physx::PxVehicleDrive4W::eFRONT_LEFT_WHEEL].x;

	ackermann.mRearWidth =
		wheelCentreOffsets[physx::PxVehicleDrive4W::eREAR_RIGHT_WHEEL].x -
		wheelCentreOffsets[physx::PxVehicleDrive4W::eREAR_LEFT_WHEEL].x;

	driveData.setAckermannGeometryData(ackermann);
}
void setupActor(
		physx::PxRigidDynamic* vehActor,
		const physx::PxFilterData& vehQryFilterData,
		const physx::PxGeometry** wheelGeometries,
		const physx::PxTransform* wheelLocalPoses,
		const physx::PxU32 numWheelGeometries,
		const physx::PxMaterial* wheelMaterial,
		const physx::PxFilterData& wheelCollFilterData,
		const physx::PxGeometry** chassisGeometries,
		const physx::PxTransform* chassisLocalPoses,
		const physx::PxU32 numChassisGeometries,
		const physx::PxMaterial* chassisMaterial,
		const physx::PxFilterData& chassisCollFilterData,
		const physx::PxVehicleChassisData& chassisData,
		physx::PxPhysics* physics)
{
	//Add all the wheel shapes to the actor.
	for(physx::PxU32 i=0;i<numWheelGeometries;i++)
	{
		physx::PxShape* wheelShape=vehActor->createShape(*wheelGeometries[i],*wheelMaterial);
		wheelShape->setQueryFilterData(vehQryFilterData);
		wheelShape->setSimulationFilterData(wheelCollFilterData);
		wheelShape->setLocalPose(wheelLocalPoses[i]);
	}

	//Add the chassis shapes to the actor.
	for(physx::PxU32 i=0;i<numChassisGeometries;i++)
	{
		physx::PxShape* chassisShape=vehActor->createShape(*chassisGeometries[i],*chassisMaterial);
		chassisShape->setQueryFilterData(vehQryFilterData);
		chassisShape->setSimulationFilterData(chassisCollFilterData);
		chassisShape->setLocalPose(chassisLocalPoses[i]);
	}

	vehActor->setMass(chassisData.mMass);
	vehActor->setMassSpaceInertiaTensor(chassisData.mMOI);
	vehActor->setCMassLocalPose(physx::PxTransform(chassisData.mCMOffset, physx::PxQuat::createIdentity()));
}
physx::PxConvexMesh* create_mesh(physx::PxVec3 const * verts, int num_verts)
{
	physx::PxConvexMeshDesc convexDesc;
	convexDesc.points.count     = num_verts;
	convexDesc.points.stride    = sizeof(physx::PxVec3);
	convexDesc.points.data      = verts;
	convexDesc.flags            = physx::PxConvexFlag::eCOMPUTE_CONVEX;
	
	//PxToolkit::MemoryOutputStream buf;
	physx::PxDefaultMemoryOutputStream buf;
	
	if(!neb::__physics.px_cooking_->cookConvexMesh(convexDesc, buf)) exit(0);

	//PxToolkit::MemoryInputData input(buf.getData(), buf.getSize());
	physx::PxDefaultMemoryInputData input(buf.getData(), buf.getSize());

	physx::PxConvexMesh* convexMesh = neb::__physics.px_physics_->createConvexMesh(input);

	return convexMesh;
}
physx::PxRigidDynamic* createVehicleActor4W(
		physx::PxVehicleChassisData chassisData,
		physx::PxConvexMesh** wheelConvexMeshes4,
		physx::PxConvexMesh* chassisConvexMesh,
		physx::PxScene* scene,
		physx::PxPhysics* physics,
		physx::PxMaterial* material)
{
	// This function creates a PhysX rigid body actor, sets up all the shapes for the wheels and chassis,
	// configures the rigid body mass and inertia, and sets collision and scene query filters for wheel and chassis shapes.

	math::vec3 p(0,0,0);
	math::quat q(0, math::vec3(1,0,0));
	math::transform pose(p,q);

	physx::PxRigidDynamic* actor = physics->createRigidDynamic(pose);

	//physx::PxShape* wheel_shape[4];
	for(int i = 0; i < 4; ++i)
	{
		/*wheel_shape[i] =*/ actor->createShape(physx::PxConvexMeshGeometry(wheelConvexMeshes4[i]), *material);
	}

	actor->createShape(physx::PxConvexMeshGeometry(chassisConvexMesh), *material);

	// mass and inertia
	physx::PxRigidBodyExt::updateMassAndInertia(*actor, 100.0);

	// collision filters


	// scene query filters



	return actor;
}
void SampleVehicleSetupVehicleShapeQueryFilterData(physx::PxFilterData* data) {
	data->word3 = DRIVABLE_SURFACE;
}
std::shared_ptr<neb::actor::vehicle>	neb::vehicle_manager::create_vehicle(
		physx::PxPhysics* physics,
		physx::PxScene* scene) {

	physx::PxF32 chassisMass = 1000.0;

	auto chassisConvexMesh = create_mesh(chassis_verts, 8);

	physx::PxConvexMesh* wheelConvexMeshes4[4];
	for(int i = 0; i < 4; ++i)
	{
		wheelConvexMeshes4[i] = create_mesh(wheel_verts, 16);
	}

	physx::PxVec3 wheelCentreOffsets4[4];
	wheelCentreOffsets4[physx::PxVehicleDrive4W::eFRONT_LEFT_WHEEL]  = physx::PxVec3(-1.5, -1, -3);
	wheelCentreOffsets4[physx::PxVehicleDrive4W::eFRONT_RIGHT_WHEEL] = physx::PxVec3( 1.5, -1, -3);
	wheelCentreOffsets4[physx::PxVehicleDrive4W::eREAR_LEFT_WHEEL]   = physx::PxVec3(-1.5, -1,  3);
	wheelCentreOffsets4[physx::PxVehicleDrive4W::eREAR_RIGHT_WHEEL]  = physx::PxVec3( 1.5, -1,  3);

	physx::PxMaterial* material = neb::__physics.px_physics_->createMaterial(0.5f, 0.5f, 0.1f);




	// from guide
	physx::PxVehicleWheelsSimData* wheelsSimData = physx::PxVehicleWheelsSimData::allocate(4);
	physx::PxVehicleDriveSimData4W driveSimData;

	physx::PxVehicleChassisData chassisData;
	createVehicle4WSimulationData(
			chassisMass,
			chassisConvexMesh,
			20.0f,
			wheelConvexMeshes4,
			wheelCentreOffsets4,
			*wheelsSimData,
			driveSimData,
			chassisData);

	physx::PxRigidDynamic* vehActor = createVehicleActor4W(
			chassisData,
			wheelConvexMeshes4,
			chassisConvexMesh,
			scene,
			physics,
			material);

	physx::PxVehicleDrive4W* car = physx::PxVehicleDrive4W::allocate(4);

	car->setup(
			neb::__physics.px_physics_,
			vehActor,
			*wheelsSimData,
			driveSimData,
			0);

	//Set up the mapping between wheel and actor shape.
	car->setWheelShapeMapping(0,0);
	car->setWheelShapeMapping(1,1);
	car->setWheelShapeMapping(2,2);
	car->setWheelShapeMapping(3,3);

	//Set up the scene query filter data for each suspension line.
	physx::PxFilterData vehQryFilterData;
	SampleVehicleSetupVehicleShapeQueryFilterData(&vehQryFilterData);
	car->setSceneQueryFilterData(0, vehQryFilterData);
	car->setSceneQueryFilterData(1, vehQryFilterData);
	car->setSceneQueryFilterData(2, vehQryFilterData);
	car->setSceneQueryFilterData(3, vehQryFilterData);






	physx::PxFilterData wheelCollFilterData;
	wheelCollFilterData.word0 = COLLISION_FLAG_WHEEL;
	wheelCollFilterData.word1 = COLLISION_FLAG_WHEEL_AGAINST;

	physx::PxFilterData chassisCollFilterData;
	chassisCollFilterData.word0 = COLLISION_FLAG_CHASSIS;
	chassisCollFilterData.word1 = COLLISION_FLAG_CHASSIS_AGAINST;


	/*
	   physx::PxFilterData qryFilterData;
	   SampleVehicleSetupDrivableShapeQueryFilterData(&qryFilterData);

	   physx::PxFilterData qryFilterData;
	   SampleVehicleSetupNonDrivableShapeQueryFilterData(&qryFilterData);

	   physx::PxFilterData vehQryFilterData;
	   SampleVehicleSetupVehicleShapeQueryFilterData(&vehQryFilterData);
	 */



	return std::shared_ptr<neb::actor::vehicle>();
}



void neb::vehicle_manager::vehicle_suspension_raycasts(physx::PxScene* scene)
{
	// Create a scene query if we haven't already done so
	if(sq_wheel_raycast_batch_query_ == NULL)
	{
		//sq_wheel_raycast_batch_query_ = sq_data_->setUpBatchedSceneQuery(scene);

		physx::PxBatchQueryDesc query_desc;
		query_desc.preFilterShader = VehicleWheelRaycastPreFilter;

		sq_wheel_raycast_batch_query_ = scene->createBatchQuery(query_desc);
	}

	physx::PxRaycastQueryResult result[4];

	// raycasts
	physx::PxVehicleSuspensionRaycasts(
			sq_wheel_raycast_batch_query_,
			vehicle_wheels_.size(),
			vehicle_wheels_.data(),
			4,
			result);
}
void neb::vehicle_manager::update(const physx::PxF32 timestep, const physx::PxVec3& gravity)
{
	//Update
	physx::PxVehicleUpdates(
			timestep,
			gravity,
			*surface_tire_pairs_,
			vehicle_wheels_.size(),
			vehicle_wheels_.data());
}




