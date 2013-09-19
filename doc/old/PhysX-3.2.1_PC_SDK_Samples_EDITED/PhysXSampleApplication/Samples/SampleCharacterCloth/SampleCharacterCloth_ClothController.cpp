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

#include "SampleCharacterCloth.h"

#include "SampleCharacterClothCameraController.h"
#include "SampleCharacterClothFlag.h"

#include "TestClothHelpers.h"
#include "SampleCharacterHelpers.h"
#include "characterkinematic/PxCapsuleController.h"
#include "cloth/PxClothReadData.h"

using namespace PxToolkit;

// size of spheres for stickman (total 30 bones + 1 root)
static const PxReal gSphereRadius[] = { 
	2.0f,  // root

	// left lower limb
	1.5f,  // lhipjoint
	1.5f,  // lfemur (upper leg)
	1.0f,  // ltibia (lower leg)
	1.0f,  // lfoot
	1.0f,  // ltoes

	// right lower limb
	1.5f,  // rhipjoint
	1.5f,  // rfemur
	1.0f,  // rtibia
	1.0f,  // rfoot
	1.0f,  // rtoes

	// spine
	2.5f,  // lowerback
	2.5f,  // upperback
	2.0f,  // thorax
	1.0f,  // lowerneck
	1.0f,  // upperneck

	2.0f,  // head

	// left arm/hand
	1.5f,  // lclavicle (shoulder)
	1.5f,  // lhumerus (upper arm)
	1.3f,  // lradius (lower arm)
	1.5f,  // lwrist
	1.8f,  // lhand
	0.5f,  // lfingers
	0.5f,  // lthumb

	// right arm/hand
	1.5f,  // rclavicle
	1.5f,  // rhumerus
	1.3f,  // rradius
	1.5f,  // rwrist
	1.8f,  // rhand
	0.5f,  // rfingers
	0.5f,  // rthumb
};

static const PxReal gCharacterScale = 0.1;

///////////////////////////////////////////////////////////////////////////////
void
SampleCharacterCloth::createCharacter()
{
	const char* asfpath = getSampleMediaFilename("motion/stickman.asf");
	if (!mCharacter.create(asfpath, gCharacterScale))
	{
		fatalError("ERROR - Cannot load motion/stickman.asf\n");
	}

	// add motion clips to the character
	const char* amcpath = 0;

	amcpath = getSampleMediaFilename("motion/stickman_walking_01.amc");
	mMotionHandleWalk = mCharacter.addMotion(amcpath);
	if (mMotionHandleWalk < 0)
		fatalError("ERROR - Cannot load motion/stickman_walking_01.amc\n");

	amcpath = getSampleMediaFilename("motion/stickman_jump_01.amc");
	mMotionHandleJump = mCharacter.addMotion(amcpath, 100,200);
	if (mMotionHandleJump < 0)
		fatalError("ERROR - Cannot load motion/stickman_jump_01.amc\n");

	// initialize character position, scale, and orientation
	resetCharacter();
}

///////////////////////////////////////////////////////////////////////////////
void
SampleCharacterCloth::createCape()
{
	// compute root transform and positions of all the bones
	PxTransform rootPose;
	SampleArray<PxVec3> positions;	
	SampleArray<PxU32> indexPairs;
	mCharacter.getFramePose(rootPose, positions, indexPairs);

	// convert bones to collision capsules
	SampleArray<PxClothCollisionSphere> spheres;	
	spheres.resize(positions.size());
	for (PxU32 i = 0; i < positions.size(); i++)
	{
		spheres[i].pos = positions[i];
		spheres[i].radius = gCharacterScale * gSphereRadius[i];
	}

	PxClothCollisionData collisionData;
	collisionData.numSpheres = static_cast<PxU32>(positions.size());
	collisionData.spheres = spheres.begin();
	collisionData.numPairs = static_cast<PxU32>(indexPairs.size()) / 2; // number of capsules
	collisionData.pairIndexBuffer = indexPairs.begin();

	// create the cloth cape mesh from file
	PxClothMeshDesc meshDesc;
	SampleArray<PxVec3> vertices;
	SampleArray<PxU32> primitives;
	SampleArray<PxReal> uvs;
	const char* capeFileName = getSampleMediaFilename("ctdm_cape_m.obj");
	PxReal clothScale = gCharacterScale * 0.3f;
	PxVec3 offset = PxVec3(0,-1.5,0); 
	PxQuat rot = PxQuat(0, PxVec3(0,1,0));
	Test::ClothHelpers::createMeshFromObj(capeFileName, clothScale, &rot, &offset, 
		vertices, primitives, &uvs, meshDesc);

	if (!meshDesc.isValid()) fatalError("Could not load ctdm_cape_m.obj\n");
	// create the cloth
	PxCloth& cloth = *createClothFromMeshDesc(
		meshDesc, rootPose, &collisionData, PxVec3(0,-1,0),
		uvs.begin(), "dummy_cape_d.bmp", PxVec3(0.5f, 0.5f, 0.5f), 0.8f);

	mCape = &cloth;

	// attach top verts
	PxClothReadData* readData = cloth.lockClothReadData();
	PX_ASSERT(readData);
	PxU32 numParticles = cloth.getNbParticles();
	SampleArray<PxClothParticle> particles(numParticles);
	SampleArray<PxVec3> particlePositions(numParticles);
    for(PxU32 i = 0; i < numParticles; i++)
	{
		particles[i].pos = readData->particles[i].pos;
		particles[i].invWeight = (uvs[i*2+1] > 0.85f) ? 0.0f : readData->particles[i].invWeight;
		particlePositions[i] = readData->particles[i].pos;
	}
	readData->unlock();
	cloth.setParticles(particles.begin(), particles.begin());

	// compute initial skin binding to the character
	mSkin.bindToCharacter(mCharacter, particlePositions);

	// set solver settings
	cloth.setSolverFrequency(240);

	// damp global particle velocity to 90% every 0.1 seconds
	cloth.setDampingCoefficient(0.1f); // damp local particle velocity
	cloth.setDragCoefficient(0.1f); // transfer frame velocity

	// reduce effect of local frame acceleration
	cloth.setInertiaScale(0.3f);
	
	const bool useVirtualParticles = true;
	const bool useSweptContact = true;
	const bool useCustomConfig = true;

	// virtual particles
	if (useVirtualParticles)
		Test::ClothHelpers::createVirtualParticles(cloth, meshDesc, 4);

	// ccd
	cloth.setClothFlag(PxClothFlag::eSWEPT_CONTACT, useSweptContact);

	// use GPU or not
#if PX_SUPPORT_GPU_PHYSX
	cloth.setClothFlag(PxClothFlag::eGPU, mUseGPU);
#endif

	// custom fiber configuration
	if (useCustomConfig)
	{
		PxClothPhaseSolverConfig config;

		config = cloth.getPhaseSolverConfig(PxClothFabricPhaseType::eSTRETCHING);
		config.solverType = PxClothPhaseSolverConfig::eSTIFF;
		config.stiffness = 1.0f;
		cloth.setPhaseSolverConfig(PxClothFabricPhaseType::eSTRETCHING, config);

		config = cloth.getPhaseSolverConfig(PxClothFabricPhaseType::eSTRETCHING_HORIZONTAL);
		config.solverType = PxClothPhaseSolverConfig::eFAST;
		config.stiffness = 1.0f;
		cloth.setPhaseSolverConfig(PxClothFabricPhaseType::eSTRETCHING_HORIZONTAL, config);

		config = cloth.getPhaseSolverConfig(PxClothFabricPhaseType::eSHEARING);
		config.solverType = PxClothPhaseSolverConfig::eFAST;
		config.stiffness = 0.75f;
		cloth.setPhaseSolverConfig(PxClothFabricPhaseType::eSHEARING, config);

		config = cloth.getPhaseSolverConfig(PxClothFabricPhaseType::eBENDING_ANGLE);
		config.solverType = PxClothPhaseSolverConfig::eBENDING;
		config.stiffness = 0.5f;
		cloth.setPhaseSolverConfig(PxClothFabricPhaseType::eBENDING_ANGLE, config);
	}
}

///////////////////////////////////////////////////////////////////////////////
void
SampleCharacterCloth::createFlags()
{
	PxQuat q = PxQuat::createIdentity();

    mFlags.pushBack(new SampleCharacterClothFlag(*this, PxTransform(PxVec3(-3,0,-10), q), 2.0f, 1.0f, 5.0f));
	mFlags.pushBack(new SampleCharacterClothFlag(*this, PxTransform(PxVec3(-3,0,-20), q), 2.0f, 1.0f, 5.0f));
	mFlags.pushBack(new SampleCharacterClothFlag(*this, PxTransform(PxVec3(-3,0,-30), q), 2.0f, 1.0f, 5.0f));
}

///////////////////////////////////////////////////////////////////////////////
void
SampleCharacterCloth::resetCape()
{
	PxCloth& cloth = *mCape;

	// compute cloth pose and collider positions
	PxTransform rootPose;
	SampleArray<PxVec3> positions;
	SampleArray<PxU32> indexPairs;
	mCharacter.getFramePose(rootPose, positions, indexPairs);

	// set cloth pose
	cloth.setGlobalPose(rootPose);

	// set collision sphere positions
	SampleArray<PxClothCollisionSphere> spheres(positions.size());
	SampleArray<PxClothCollisionPlane> planes(cloth.getNbCollisionPlanes());
	SampleArray<PxU32> convexMasks(cloth.getNbCollisionConvexes());
	cloth.getCollisionData(spheres.begin(), indexPairs.begin(), planes.begin(), convexMasks.begin());
	for (PxU32 i = 0; i < positions.size(); i++)
		spheres[i].pos = positions[i];
	cloth.setCollisionSpheres(spheres.begin());

	// set positions for constrained particles
	SampleArray<PxVec3> particlePositions;
	mSkin.computeNewPositions(mCharacter, particlePositions);
	Test::ClothHelpers::setParticlePositions(cloth, particlePositions, false, false);

	cloth.setExternalAcceleration(PxVec3(0.0f));

	// clear previous state of collision shapes etc.
	cloth.clearInterpolation();
}

///////////////////////////////////////////////////////////////////////////////
void
SampleCharacterCloth::resetCharacter()
{
	// compute global pose and local positions
	PxExtendedVec3 posExt = mController->getPosition();
	PxVec3 pos = PxVec3(PxReal(posExt.x), PxReal(posExt.y), PxReal(posExt.z)) - PxVec3(0.0f, 1.5, 0.0f);

	PxTransform pose;
	pose.p = pos;
	pose.q = PxQuat::createIdentity();

	mCharacter.resetMotion(37.0f);
	mCharacter.setGlobalPose(pose);
	mCharacter.setTargetPosition(PxVec3(pos.x, pos.y, pos.z));
	mCharacter.setMotion(mMotionHandleWalk, true);
	mCharacter.move(1.0f, false, mCCTActive);
	mCharacter.faceToward(PxVec3(0,0,-1));

	mJump.reset();

	mCCTDisplacementPrevStep = PxVec3(0.0f);
}


///////////////////////////////////////////////////////////////////////////////
void
SampleCharacterCloth::updateCape(float dtime)
{
	PxCloth& cloth = *mCape;

	// compute cloth pose and collider positions
	PxTransform rootPose;
	SampleArray<PxVec3> positions;
	SampleArray<PxU32> indexPairs;
	mCharacter.getFramePose(rootPose, positions, indexPairs);

	// set cloth pose
	cloth.setTargetPose(rootPose);

	// set collision sphere positions
	SampleArray<PxClothCollisionSphere> spheres(positions.size());
	SampleArray<PxClothCollisionPlane> planes(cloth.getNbCollisionPlanes());
	SampleArray<PxU32> convexMasks(cloth.getNbCollisionConvexes());

	cloth.getCollisionData(spheres.begin(), indexPairs.begin(), planes.begin(), convexMasks.begin());
	for (PxU32 i = 0; i < positions.size(); i++)
		spheres[i].pos = positions[i];
	cloth.setCollisionSpheres(spheres.begin());

	// set positions for constrained particles
	SampleArray<PxVec3> particlePositions;
	mSkin.computeNewPositions(mCharacter, particlePositions);

	Test::ClothHelpers::setParticlePositions(cloth, particlePositions, true, true);

	// add wind while in freefall
	if (mJump.isInFreefall())
	{
		PxReal strength = 20.0f;
		PxVec3 offset( PxReal(PxToolkit::Rand(-1,1)), 1.0f + PxReal(PxToolkit::Rand(-1,1)), PxReal(PxToolkit::Rand(-1,1)));
		PxVec3 windAcceleration = strength * offset;
		cloth.setExternalAcceleration(windAcceleration);
	}
}

///////////////////////////////////////////////////////////////////////////////
void
SampleCharacterCloth::updateCharacter(float dtime)
{
	// compute global pose of the character from CCT
	PxExtendedVec3 posExt = mController->getPosition();
	PxVec3 offset(0.0f, gCharacterScale * 15.0f, 0.0f); // offset from controller center to the foot
	PxVec3 pos = PxVec3(PxReal(posExt.x), PxReal(posExt.y), PxReal(posExt.z)) - offset;
	
	// update character pose and motion 
	if (mJump.isJumping() == true)
	{	
		mCharacter.setTargetPosition(pos);
		mCharacter.setMotion(mMotionHandleJump);
		mCharacter.move(0.25f, true);
	}
	else 
	{
		bool cctActive = mCCTActive && (mJump.isInFreefall() == false);

		mCharacter.setTargetPosition(pos);
		mCharacter.setMotion(mMotionHandleWalk);
		mCharacter.move(1.0f, false, cctActive);
	}
}

///////////////////////////////////////////////////////////////////////////////
void
SampleCharacterCloth::updateFlags(float dtime)
{
	// apply wind force to flags
	for (PxU32 i = 0 ; i < mFlags.size(); i++)
	{
		mFlags[i]->setWind(PxVec3(1,0.1,0), 40.0f, PxVec3(0.0f, 5.0f, 15.0f));
		mFlags[i]->update(dtime);
	}
}

#if PX_SUPPORT_GPU_PHYSX
///////////////////////////////////////////////////////////////////////////////
void
SampleCharacterCloth::toggleGPU()
{
	mUseGPU = !mUseGPU;

	if (mCape)
		mCape->setClothFlag(PxClothFlag::eGPU, mUseGPU);

	for (PxU32 i = 0 ; i < mFlags.size(); i++)
	{
		mFlags[i]->getCloth()->setClothFlag(PxClothFlag::eGPU, mUseGPU);
	}
}
#endif

#endif // PX_USE_CLOTH_API
