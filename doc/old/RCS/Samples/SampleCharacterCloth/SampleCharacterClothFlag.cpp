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

#include "PxPhysX.h"

#if PX_USE_CLOTH_API

#include "SampleCharacterClothFlag.h"
#include "SampleCharacterCloth.h"

#include "TestClothHelpers.h"
#include "cloth/PxClothReadData.h"

using namespace PxToolkit;


////////////////////////////////////////////////////////////////////////////////
SampleCharacterClothFlag::SampleCharacterClothFlag(SampleCharacterCloth& sample, const PxTransform &pose, PxReal sizeX, PxReal sizeY, PxReal height)
    :
    mWindDir(1.0f, 0.0f, 0.0f),
    mWindRange(1.0f),
	mWindStrength(1.0f),
	mTime(0.0f)
{
	PxScene& scene = sample.getActiveScene();

	// adjust placement position for the flag with ray casting so that we can put each flag properly on the terrain
	PxVec3 pos = pose.p;
	PxRaycastHit hit;
	scene.raycastSingle(PxVec3(pos.x,100,pos.z), PxVec3(0,-1,0), 500.0f, PxSceneQueryFlags(0xffffffff), hit);
	pos = hit.impact + PxVec3(0,0.2f,0.0);

    PxTransform clothPose(pos, pose.q);

	PxReal halfSizeX = sizeX * 0.5f;
    PxReal halfSizeY = sizeY * 0.5f;
    PxReal offset = sizeX * 0.1f;
	PxReal halfHeight = height * 0.5f;

    PxReal clothHeight = height - halfSizeY;
    clothPose.p.y += clothHeight;

	// create collision capsule for the pole
	SampleArray<PxClothCollisionSphere> spheres(2);
	spheres[0].pos = PxVec3(-halfSizeX - offset, -clothHeight, 0);
	spheres[1].pos = PxVec3(-halfSizeX - offset, halfSizeY, 0);
	spheres[0].radius = 0.1f;
	spheres[1].radius = 0.1f;

	SampleArray<PxU32> indexPairs;
	indexPairs.pushBack(0);
	indexPairs.pushBack(1);

	PxClothCollisionData collisionData;
	collisionData.numSpheres = 2;
	collisionData.spheres = spheres.begin();
	collisionData.numPairs = 1;
	collisionData.pairIndexBuffer = indexPairs.begin();

	// create the cloth flag mesh
	PxClothMeshDesc meshDesc;
	SampleArray<PxVec3> vertices;
	SampleArray<PxU32> primitives;

	mUVs.clear();

	Test::ClothHelpers::createMeshGrid(sizeX, sizeY, 15, 10, PxVec3(1,0,0), PxVec3(0,-1,0), vertices, primitives, mUVs, meshDesc);

	// create the cloth
	PxCloth& cloth = *sample.createClothFromMeshDesc(
		meshDesc, clothPose, &collisionData, PxVec3(0,-1,0),
		mUVs.begin(), "nvidia_flag_d.bmp"
		, PxVec3(0.5f, 0.5f, 0.5f), 0.5f);

	// attach two corners on the left
	PxClothReadData* readData = cloth.lockClothReadData();
	PX_ASSERT(readData);
	PxU32 numParticles = cloth.getNbParticles();
	SampleArray<PxClothParticle> particles(numParticles);
    for(PxU32 i = 0; i < numParticles; i++)
	{
		particles[i].pos = readData->particles[i].pos;
		PxReal u = mUVs[i*2], v = mUVs[i*2+1];
		bool constrain = ( (u < 0.01) && (v < 1.01) ) || (( u < 0.01) && (v > 0.99));
		particles[i].invWeight = constrain ? 0.0f : readData->particles[i].invWeight;
	}
	readData->unlock();

	// set solver settings
	cloth.setParticles(particles.begin(), particles.begin());
	cloth.setSolverFrequency(120);
	cloth.setDampingCoefficient(0.0f);

	PxClothPhaseSolverConfig config;

	config = cloth.getPhaseSolverConfig(PxClothFabricPhaseType::eBENDING_ANGLE);
	config.solverType = PxClothPhaseSolverConfig::eBENDING;
	config.stiffness = 0.1f;
	cloth.setPhaseSolverConfig(PxClothFabricPhaseType::eBENDING_ANGLE, config);

    mCloth = &cloth;

	// we create an invisible kinematic capsule so that the CCT avoids colliding character against the pole of this flag
	PxTransform capsulePose(pos, PxQuat(PxHalfPi, PxVec3(0,0,1)));
	capsulePose.p.x -= halfSizeX + offset;
	capsulePose.p.y += halfHeight;
	PxCapsuleGeometry geom(0.2f,halfHeight);
	PxRigidDynamic* actor = sample.getPhysics().createRigidDynamic(capsulePose);
	actor->setRigidDynamicFlag(PxRigidDynamicFlag::eKINEMATIC, true);
	actor->createShape( geom, sample.getDefaultMaterial());
	scene.addActor(*actor);
}

////////////////////////////////////////////////////////////////////////////////
void
SampleCharacterClothFlag::release()
{
	delete this;
}

////////////////////////////////////////////////////////////////////////////////
void     
SampleCharacterClothFlag::setWind(const PxVec3 &dir, PxReal strength, const PxVec3& range)
{
    mWindStrength = strength;
    mWindDir = dir;
    mWindRange = range;
}

////////////////////////////////////////////////////////////////////////////////
void     
SampleCharacterClothFlag::update(PxReal dtime)
{
    PX_ASSERT(mCloth);
    
    mTime += dtime;

	// global wind 
	PxVec3 offset( PxReal(PxToolkit::Rand(-1,1)), PxReal(PxToolkit::Rand(-1,1)), PxReal(PxToolkit::Rand(-1,1)));
	PxVec3 windAcceleration = mWindStrength * mWindDir + mWindRange.multiply(offset);
	mCloth->setExternalAcceleration(windAcceleration);

	// per particle wind 
	PxU32 nbParticles = mCloth->getNbParticles();
	SampleArray<PxVec4> accel(nbParticles);

	for (PxU32 i = 0; i < nbParticles; i++)
	{
		accel[i].x = PxToolkit::Rand(-1,1) * mWindRange.x;
		accel[i].y = PxToolkit::Rand(-1,1) * mWindRange.y;
		accel[i].z = PxToolkit::Rand(-1,1) * mWindRange.z;
	}
	mCloth->setParticleAccelerations(accel.begin());
}

#endif // PX_USE_CLOTH_API

 