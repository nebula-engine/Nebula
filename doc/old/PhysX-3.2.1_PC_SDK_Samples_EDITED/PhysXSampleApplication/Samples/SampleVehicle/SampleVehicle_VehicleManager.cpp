// This code contains NVIDIA Confidential Information and is disclosed to you 
// under a form of NVIDIA software license agreement provided separately to you.
//
// Notice
// NVIDIA Corporation and its licensors retain all intellectual property and
// proprietary rights in and to this software and related documentation and 
// any modifications thereto. Any use, reproduction, disclosure, or 
// distribution of this software and related documentation without an express 
// license agreement from NVIDIA Corporation is strictly prohibited.
// 
// ALL NVIDIA DESIGN SPECIFICATIONS, CODE ARE PROVIDED "AS IS.". NVIDIA MAKES
// NO WARRANTIES, EXPRESSED, IMPLIED, STATUTORY, OR OTHERWISE WITH RESPECT TO
// THE MATERIALS, AND EXPRESSLY DISCLAIMS ALL IMPLIED WARRANTIES OF NONINFRINGEMENT,
// MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE.
//
// Information and code furnished is believed to be accurate and reliable.
// However, NVIDIA Corporation assumes no responsibility for the consequences of use of such
// information or for any infringement of patents or other rights of third parties that may
// result from its use. No license is granted by implication or otherwise under any patent
// or patent rights of NVIDIA Corporation. Details are subject to change without notice.
// This code supersedes and replaces all information previously supplied.
// NVIDIA Corporation products are not authorized for use as critical
// components in life support devices or systems without express written approval of
// NVIDIA Corporation.
//
// Copyright (c) 2008-2012 NVIDIA Corporation. All rights reserved.
// Copyright (c) 2004-2008 AGEIA Technologies, Inc. All rights reserved.
// Copyright (c) 2001-2004 NovodeX AG. All rights reserved.  

#include "SampleVehicle_VehicleManager.h"
#include "SampleVehicle_VehicleCooking.h"
#include "SampleVehicle_SceneQuery.h"
#include "RendererMemoryMacros.h"
#include "vehicle/PxVehicleSDK.h"
#include "vehicle/PxVehicleDrive4W.h"
#include "vehicle/PxVehicleUpdate.h"
#include "vehicle/PxVehicleTireFriction.h"
#include "vehicle/PxVehicleUtilSetup.h"
#include "PxRigidDynamic.h"
#include "PxScene.h"
#include "geometry/PxConvexMesh.h"
#include "geometry/PxConvexMeshGeometry.h"
#include "SampleAllocatorSDKClasses.h"
#ifdef PX_PS3
#include "ps3/SampleVehicle_RaycastShader.h"
#endif


#ifdef PX_PS3
PX_FORCE_INLINE void setSpuRaycastShader(SampleVehicleSceneQueryData* sqDesc)
{
	sqDesc->setSpuPreFilterShader(sampleVehicle_RaycastShader,SAMPLEVEHICLE_RAYCASTSHADER_SIZE);
}
#endif
///////////////////////////////////

SampleVehicle_VehicleManager::SampleVehicle_VehicleManager() 
:	mNumVehicles(0),
	mSqWheelRaycastBatchQuery(NULL)
{
}

SampleVehicle_VehicleManager::~SampleVehicle_VehicleManager()
{
}

void SampleVehicle_VehicleManager::init(PxPhysics& physics, const PxMaterial** drivableSurfaceMaterials, const PxVehicleDrivableSurfaceType* drivableSurfaceTypes)
{
	//Initialise the sdk.
	PxInitVehicleSDK(physics);

	//Initialise all vehicle ptrs to null.
	for(PxU32 i=0;i<MAX_NUM_4W_VEHICLES;i++)
	{
		mVehicles[i]=NULL;
	}

	//Scene query data for to allow raycasts for all suspensions of all vehicles.
	mSqData = SampleVehicleSceneQueryData::allocate(MAX_NUM_4W_VEHICLES*4);

	//Set up the friction values arising from combinations of tire type and surface type.
	mSurfaceTirePairs=PxVehicleDrivableSurfaceToTireFrictionPairs::create(MAX_NUM_TIRE_TYPES,MAX_NUM_SURFACE_TYPES,drivableSurfaceMaterials,drivableSurfaceTypes);
	for(PxU32 i=0;i<MAX_NUM_SURFACE_TYPES;i++)
	{
		for(PxU32 j=0;j<MAX_NUM_TIRE_TYPES;j++)
		{
			mSurfaceTirePairs->setTypePairFriction(i,j,gTireFrictionMultipliers[i][j]);
		}
	}

#ifdef PX_PS3 
	setSpuRaycastShader(mSqData);
#endif
}

void SampleVehicle_VehicleManager::shutdown()
{
	//Remove the N-wheeled vehicles.
	for(PxU32 i=0;i<mNumVehicles;i++)
	{
		PX_ASSERT(eVEHICLE_TYPE_DRIVE4W==mVehicles[i]->getVehicleType());
		PxVehicleDrive4W* veh=(PxVehicleDrive4W*)mVehicles[i];
		veh->free();
	}

	//Deallocate scene query data that was used for suspension raycasts.
	mSqData->free();

	//Release the  friction values used for combinations of tire type and surface type.
	mSurfaceTirePairs->release();

	//Scene query.
	if(mSqWheelRaycastBatchQuery)
	{
		mSqWheelRaycastBatchQuery=NULL;
	}

	PxCloseVehicleSDK();
}

void SampleVehicle_VehicleManager::resetNWCar(const PxTransform& transform, const PxU32 vehicleId)
{
	PX_ASSERT(vehicleId<mNumVehicles);
	resetNWCar(transform,mVehicles[vehicleId]);
}

void SampleVehicle_VehicleManager::suspensionRaycasts(PxScene* scene)
{
	//Create a scene query if we haven't already done so.
	if(NULL==mSqWheelRaycastBatchQuery)
	{
		mSqWheelRaycastBatchQuery=mSqData->setUpBatchedSceneQuery(scene);
	}
	//Raycasts.
	PxVehicleSuspensionRaycasts(mSqWheelRaycastBatchQuery,mNumVehicles,mVehicles,mSqData->getRaycastQueryResultBufferSize(),mSqData->getRaycastQueryResultBuffer());
}


#if PX_DEBUG_VEHICLE_ON

void SampleVehicle_VehicleManager::updateAndRecordTelemetryData
(const PxF32 timestep, const PxVec3& gravity, PxVehicleWheels* focusVehicle, PxVehicleTelemetryData* telemetryData)
{
	PX_ASSERT(focusVehicle && telemetryData);

	//Update the vehicle for which we want to record debug data.
	PxVehicleUpdateSingleVehicleAndStoreTelemetryData(timestep,gravity,*mSurfaceTirePairs,focusVehicle,*telemetryData);

	//Update the remaining vehicles.
	PxVehicleWheels* vehicles[MAX_NUM_4W_VEHICLES];
	PxU32 numVehicles=0;
	for(PxU32 i=0;i<mNumVehicles;i++)
	{
		if(focusVehicle!=mVehicles[i])
		{
			vehicles[numVehicles]=mVehicles[i];
			numVehicles++;
		}
	}
	PxVehicleUpdates(timestep,gravity,*mSurfaceTirePairs,numVehicles,vehicles);
}

#else

void SampleVehicle_VehicleManager::update(const PxF32 timestep, const PxVec3& gravity)
{
	//Update.
	PxVehicleUpdates(timestep,gravity,*mSurfaceTirePairs,mNumVehicles,mVehicles);
}

#endif //PX_DEBUG_VEHICLE_ON

void SampleVehicle_VehicleManager::resetNWCar(const PxTransform& startTransform, PxVehicleWheels* vehWheels)
{
	PX_ASSERT(eVEHICLE_TYPE_DRIVE4W==vehWheels->getVehicleType());
	PxVehicleDrive4W* vehDrive4W=(PxVehicleDrive4W*)vehWheels;
	//Set the car back to its rest state.
	vehDrive4W->setToRestState();
	//Set the car to first gear.
	vehDrive4W->mDriveDynData.forceGearChange(PxVehicleGearsData::eFIRST);

	//Set the car's transform to be the start transform.
	PxRigidDynamic* actor=vehWheels->getRigidDynamicActor();
	actor->setGlobalPose(startTransform);
}

void setupActor
(PxRigidDynamic* vehActor, 
 const PxFilterData& vehQryFilterData,
 const PxGeometry** wheelGeometries, const PxTransform* wheelLocalPoses, const PxU32 numWheelGeometries, const PxMaterial* wheelMaterial, const PxFilterData& wheelCollFilterData,
 const PxGeometry** chassisGeometries, const PxTransform* chassisLocalPoses, const PxU32 numChassisGeometries, const PxMaterial* chassisMaterial, const PxFilterData& chassisCollFilterData,
 const PxVehicleChassisData& chassisData,
 PxPhysics* physics)
{
	//Add all the wheel shapes to the actor.
	for(PxU32 i=0;i<numWheelGeometries;i++)
	{
		PxShape* wheelShape=vehActor->createShape(*wheelGeometries[i],*wheelMaterial);
		wheelShape->setQueryFilterData(vehQryFilterData);
		wheelShape->setSimulationFilterData(wheelCollFilterData);
		wheelShape->setLocalPose(wheelLocalPoses[i]);
	}

	//Add the chassis shapes to the actor.
	for(PxU32 i=0;i<numChassisGeometries;i++)
	{
		PxShape* chassisShape=vehActor->createShape(*chassisGeometries[i],*chassisMaterial);
		chassisShape->setQueryFilterData(vehQryFilterData);
		chassisShape->setSimulationFilterData(chassisCollFilterData);
		chassisShape->setLocalPose(chassisLocalPoses[i]);
	}

	vehActor->setMass(chassisData.mMass);
	vehActor->setMassSpaceInertiaTensor(chassisData.mMOI);
	vehActor->setCMassLocalPose(PxTransform(chassisData.mCMOffset,PxQuat::createIdentity()));
}

PxRigidDynamic* createVehicleActor4W
(const PxVehicleChassisData& chassisData,
 PxConvexMesh** wheelConvexMeshes, PxConvexMesh* chassisConvexMesh, 
 PxScene& scene, PxPhysics& physics, const PxMaterial& material)
{
	//We need a rigid body actor for the vehicle.
	//Don't forget to add the actor the scene after setting up the associated vehicle.
	PxRigidDynamic* vehActor=physics.createRigidDynamic(PxTransform::createIdentity());

	//We need to add wheel collision shapes, their local poses, a material for the wheels, and a simulation filter for the wheels.
	PxConvexMeshGeometry frontLeftWheelGeom(wheelConvexMeshes[0]);
	PxConvexMeshGeometry frontRightWheelGeom(wheelConvexMeshes[1]);
	PxConvexMeshGeometry rearLeftWheelGeom(wheelConvexMeshes[2]);
	PxConvexMeshGeometry rearRightWheelGeom(wheelConvexMeshes[3]);
	const PxGeometry* wheelGeometries[4]={&frontLeftWheelGeom,&frontRightWheelGeom,&rearLeftWheelGeom,&rearRightWheelGeom};
	const PxTransform wheelLocalPoses[4]={PxTransform::createIdentity(),PxTransform::createIdentity(),PxTransform::createIdentity(),PxTransform::createIdentity()};
	const PxMaterial& wheelMaterial=material;
	PxFilterData wheelCollFilterData;
	wheelCollFilterData.word0=COLLISION_FLAG_WHEEL;
	wheelCollFilterData.word1=COLLISION_FLAG_WHEEL_AGAINST;

	//We need to add chassis collision shapes, their local poses, a material for the chassis, and a simulation filter for the chassis.
	PxConvexMeshGeometry chassisConvexGeom(chassisConvexMesh);
	const PxGeometry* chassisGeoms[1]={&chassisConvexGeom};
	const PxTransform chassisLocalPoses[1]={PxTransform::createIdentity()};
	const PxMaterial& chassisMaterial=material;
	PxFilterData chassisCollFilterData;
	chassisCollFilterData.word0=COLLISION_FLAG_CHASSIS;
	chassisCollFilterData.word1=COLLISION_FLAG_CHASSIS_AGAINST;

	//Create a query filter data for the car to ensure that cars
	//do not attempt to drive on themselves.
	PxFilterData vehQryFilterData;
	SampleVehicleSetupVehicleShapeQueryFilterData(&vehQryFilterData);

	//Set up the physx rigid body actor with shapes, local poses, and filters.
	setupActor
		(vehActor,
		vehQryFilterData,
		wheelGeometries,wheelLocalPoses,4,&wheelMaterial,wheelCollFilterData,
		chassisGeoms,chassisLocalPoses,1,&chassisMaterial,chassisCollFilterData,
		chassisData,
		&physics);

	return vehActor;
}

void computeWheelWidthsAndRadii(PxConvexMesh** wheelConvexMeshes, PxF32* wheelWidths, PxF32* wheelRadii)
{
	for(PxU32 i=0;i<4;i++)
	{
		const PxU32 numWheelVerts=wheelConvexMeshes[i]->getNbVertices();
		const PxVec3* wheelVerts=wheelConvexMeshes[i]->getVertices();
		PxVec3 wheelMin(PX_MAX_F32,PX_MAX_F32,PX_MAX_F32);
		PxVec3 wheelMax(-PX_MAX_F32,-PX_MAX_F32,-PX_MAX_F32);
		for(PxU32 j=0;j<numWheelVerts;j++)
		{
			wheelMin.x=PxMin(wheelMin.x,wheelVerts[j].x);
			wheelMin.y=PxMin(wheelMin.y,wheelVerts[j].y);
			wheelMin.z=PxMin(wheelMin.z,wheelVerts[j].z);
			wheelMax.x=PxMax(wheelMax.x,wheelVerts[j].x);
			wheelMax.y=PxMax(wheelMax.y,wheelVerts[j].y);
			wheelMax.z=PxMax(wheelMax.z,wheelVerts[j].z);
		}
		wheelWidths[i]=wheelMax.x-wheelMin.x;
		wheelRadii[i]=PxMax(wheelMax.y,wheelMax.z)*0.975f;
	}
}

PxVec3 computeChassisAABBDimensions(const PxConvexMesh* chassisConvexMesh)
{
	const PxU32 numChassisVerts=chassisConvexMesh->getNbVertices();
	const PxVec3* chassisVerts=chassisConvexMesh->getVertices();
	PxVec3 chassisMin(PX_MAX_F32,PX_MAX_F32,PX_MAX_F32);
	PxVec3 chassisMax(-PX_MAX_F32,-PX_MAX_F32,-PX_MAX_F32);
	for(PxU32 i=0;i<numChassisVerts;i++)
	{
		chassisMin.x=PxMin(chassisMin.x,chassisVerts[i].x);
		chassisMin.y=PxMin(chassisMin.y,chassisVerts[i].y);
		chassisMin.z=PxMin(chassisMin.z,chassisVerts[i].z);
		chassisMax.x=PxMax(chassisMax.x,chassisVerts[i].x);
		chassisMax.y=PxMax(chassisMax.y,chassisVerts[i].y);
		chassisMax.z=PxMax(chassisMax.z,chassisVerts[i].z);
	}
	const PxVec3 chassisDims=chassisMax-chassisMin;
	return chassisDims;
}

void createVehicle4WSimulationData
(const PxF32 chassisMass, PxConvexMesh* chassisConvexMesh, 
 const PxF32 wheelMass, PxConvexMesh** wheelConvexMeshes, const PxVec3* wheelCentreOffsets, 
 PxVehicleWheelsSimData& wheelsData, PxVehicleDriveSimData4W& driveData, PxVehicleChassisData& chassisData)
{
	//Extract the chassis AABB dimensions from the chassis convex mesh.
	const PxVec3 chassisDims=computeChassisAABBDimensions(chassisConvexMesh);

	//The origin is at the center of the chassis mesh.
	//Set the center of mass to be below this point and a little towards the front.
	const PxVec3 chassisCMOffset=PxVec3(0.0f,-chassisDims.y*0.5f+0.65f,0.25f);

	//Now compute the chassis mass and moment of inertia.
	//Use the moment of inertia of a cuboid as an approximate value for the chassis moi.
	PxVec3 chassisMOI
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
	//massRear*zRear + massFront*zFront = mass*cm		(1)
	//massRear       + massFront        = mass			(2)
	//Rearrange (2)
	//massFront = mass - massRear						(3)
	//Substitute (3) into (1)
	//massRear(zRear - zFront) + mass*zFront = mass*cm	(4)
	//Solve (4) for massRear
	//massRear = mass(cm - zFront)/(zRear-zFront)		(5)
	//Now we also have
	//zFront = (z-cm)/2									(6a)
	//zRear = (-z-cm)/2									(6b)
	//Substituting (6a-b) into (5) gives
	//massRear = 0.5*mass*(z-3cm)/z						(7)
	const PxF32 massRear=0.5f*chassisMass*(chassisDims.z-3*chassisCMOffset.z)/chassisDims.z;
	const PxF32 massFront=chassisMass-massRear;

	//Extract the wheel radius and width from the wheel convex meshes.
	PxF32 wheelWidths[4];
	PxF32 wheelRadii[4];
	computeWheelWidthsAndRadii(wheelConvexMeshes,wheelWidths,wheelRadii);

	//Now compute the wheel masses and inertias components around the axle's axis.
	//http://en.wikipedia.org/wiki/List_of_moments_of_inertia
	PxF32 wheelMOIs[4];
	for(PxU32 i=0;i<4;i++)
	{
		wheelMOIs[i]=0.5f*wheelMass*wheelRadii[i]*wheelRadii[i];
	}
	//Let's set up the wheel data structures now with radius, mass, and moi.
	PxVehicleWheelData wheels[4];
	for(PxU32 i=0;i<4;i++)
	{
		wheels[i].mRadius=wheelRadii[i];
		wheels[i].mMass=wheelMass;
		wheels[i].mMOI=wheelMOIs[i];
		wheels[i].mWidth=wheelWidths[i];
	}
	//Disable the handbrake from the front wheels and enable for the rear wheels
	wheels[PxVehicleDrive4W::eFRONT_LEFT_WHEEL].mMaxHandBrakeTorque=0.0f;
	wheels[PxVehicleDrive4W::eFRONT_RIGHT_WHEEL].mMaxHandBrakeTorque=0.0f;
	wheels[PxVehicleDrive4W::eREAR_LEFT_WHEEL].mMaxHandBrakeTorque=4000.0f;
	wheels[PxVehicleDrive4W::eREAR_RIGHT_WHEEL].mMaxHandBrakeTorque=4000.0f;
	//Enable steering for the front wheels and disable for the front wheels.
	wheels[PxVehicleDrive4W::eFRONT_LEFT_WHEEL].mMaxSteer=PxPi*0.3333f;
	wheels[PxVehicleDrive4W::eFRONT_RIGHT_WHEEL].mMaxSteer=PxPi*0.3333f;
	wheels[PxVehicleDrive4W::eREAR_LEFT_WHEEL].mMaxSteer=0.0f;
	wheels[PxVehicleDrive4W::eREAR_RIGHT_WHEEL].mMaxSteer=0.0f;

	//Let's set up the tire data structures now.
	//Put slicks on the front tires and wets on the rear tires.
	PxVehicleTireData tires[4];
	tires[PxVehicleDrive4W::eFRONT_LEFT_WHEEL].mType=TIRE_TYPE_SLICKS;
	tires[PxVehicleDrive4W::eFRONT_RIGHT_WHEEL].mType=TIRE_TYPE_SLICKS;
	tires[PxVehicleDrive4W::eREAR_LEFT_WHEEL].mType=TIRE_TYPE_WETS;
	tires[PxVehicleDrive4W::eREAR_RIGHT_WHEEL].mType=TIRE_TYPE_WETS;

	//Let's set up the suspension data structures now.
	PxVehicleSuspensionData susps[4];
	for(PxU32 i=0;i<4;i++)
	{
		susps[i].mMaxCompression=0.3f;
		susps[i].mMaxDroop=0.1f;
		susps[i].mSpringStrength=35000.0f;	
		susps[i].mSpringDamperRate=4500.0f;
	}
	susps[PxVehicleDrive4W::eFRONT_LEFT_WHEEL].mSprungMass=massFront*0.5f;
	susps[PxVehicleDrive4W::eFRONT_RIGHT_WHEEL].mSprungMass=massFront*0.5f;
	susps[PxVehicleDrive4W::eREAR_LEFT_WHEEL].mSprungMass=massRear*0.5f;
	susps[PxVehicleDrive4W::eREAR_RIGHT_WHEEL].mSprungMass=massRear*0.5f;

	//We need to set up geometry data for the suspension, wheels, and tires.
	//We already know the wheel centers described as offsets from the rigid body centre of mass.
	//From here we can approximate application points for the tire and suspension forces.
	//Lets assume that the suspension travel directions are absolutely vertical.
	//Also assume that we apply the tire and suspension forces 30cm below the centre of mass.
	PxVec3 suspTravelDirections[4]={PxVec3(0,-1,0),PxVec3(0,-1,0),PxVec3(0,-1,0),PxVec3(0,-1,0)};
	PxVec3 wheelCentreCMOffsets[4];
	PxVec3 suspForceAppCMOffsets[4];
	PxVec3 tireForceAppCMOffsets[4];
	for(PxU32 i=0;i<4;i++)
	{
		wheelCentreCMOffsets[i]=wheelCentreOffsets[i]-chassisCMOffset;
		suspForceAppCMOffsets[i]=PxVec3(wheelCentreCMOffsets[i].x,-0.3f,wheelCentreCMOffsets[i].z);
		tireForceAppCMOffsets[i]=PxVec3(wheelCentreCMOffsets[i].x,-0.3f,wheelCentreCMOffsets[i].z);
	}

	//Now add the wheel, tire and suspension data.
	for(PxU32 i=0;i<4;i++)
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
	PxVehicleDifferential4WData diff;
	diff.mType=PxVehicleDifferential4WData::eDIFF_TYPE_LS_4WD;
	driveData.setDiffData(diff);
	
	//Engine
	PxVehicleEngineData engine;
	engine.mPeakTorque=500.0f;
	engine.mMaxOmega=600.0f;//approx 6000 rpm
	driveData.setEngineData(engine);

	//Gears
	PxVehicleGearsData gears;
	gears.mSwitchTime=0.5f;
	driveData.setGearsData(gears);

	//Clutch
	PxVehicleClutchData clutch;
	clutch.mStrength=10.0f;
	driveData.setClutchData(clutch);

	//Ackermann steer accuracy
	PxVehicleAckermannGeometryData ackermann;
	ackermann.mAccuracy=1.0f;
	ackermann.mAxleSeparation=wheelCentreOffsets[PxVehicleDrive4W::eFRONT_LEFT_WHEEL].z-wheelCentreOffsets[PxVehicleDrive4W::eREAR_LEFT_WHEEL].z;
	ackermann.mFrontWidth=wheelCentreOffsets[PxVehicleDrive4W::eFRONT_RIGHT_WHEEL].x-wheelCentreOffsets[PxVehicleDrive4W::eFRONT_LEFT_WHEEL].x;
	ackermann.mRearWidth=wheelCentreOffsets[PxVehicleDrive4W::eREAR_RIGHT_WHEEL].x-wheelCentreOffsets[PxVehicleDrive4W::eREAR_LEFT_WHEEL].x;
	driveData.setAckermannGeometryData(ackermann);
}

void SampleVehicle_VehicleManager::create4WVehicle
(PxScene& scene, PxPhysics& physics, PxCooking& cooking, const PxMaterial& material,
 const PxF32 chassisMass, const PxVec3* wheelCentreOffsets4, PxConvexMesh* chassisConvexMesh, PxConvexMesh** wheelConvexMeshes4,
 const PxTransform& startTransform, const bool useAutoGearFlag)
{
	PX_ASSERT(mNumVehicles<MAX_NUM_4W_VEHICLES);

	PxVehicleWheelsSimData* wheelsSimData=PxVehicleWheelsSimData::allocate(4);
	PxVehicleDriveSimData4W driveSimData;
	PxVehicleChassisData chassisData;
	createVehicle4WSimulationData
		(chassisMass,chassisConvexMesh,
		 20.0f,wheelConvexMeshes4,wheelCentreOffsets4,
		 *wheelsSimData,driveSimData,chassisData);
		
	//Instantiate and finalize the vehicle using physx.
	PxRigidDynamic* vehActor=createVehicleActor4W(chassisData,wheelConvexMeshes4,chassisConvexMesh,scene,physics,material);

	//Create a car.
	PxVehicleDrive4W* car = PxVehicleDrive4W::allocate(4);
	car->setup(&physics,vehActor,*wheelsSimData,driveSimData,0);

	//Free the sim data because we don't need that any more.
	wheelsSimData->free();

	//Don't forget to add the actor to the scene.
	scene.addActor(*vehActor);

	//Set the transform and the instantiated car and set it be to be at rest.
	resetNWCar(startTransform,car);
	//Set the autogear mode of the instantiate car.
	car->mDriveDynData.setUseAutoGears(useAutoGearFlag);

	//Increment the number of vehicles
	mVehicles[mNumVehicles]=car;
	mNumVehicles++;
}

