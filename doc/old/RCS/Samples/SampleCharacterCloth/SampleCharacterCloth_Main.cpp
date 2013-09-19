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

#include "SampleAllocatorSDKClasses.h"
#include "SampleCharacterClothCameraController.h"
#include "SampleCharacterClothInputEventIds.h"
#include "SampleCharacterClothFlag.h"
#include "SamplePlatform.h"

#include "RenderMaterial.h"
#include "RenderBaseActor.h"

#include "characterkinematic/PxCapsuleController.h"
#include "characterkinematic/PxControllerManager.h"
#include "PxPhysicsAPI.h"


REGISTER_SAMPLE(SampleCharacterCloth, "SampleCharacterCloth")

using namespace SampleFramework;
using namespace SampleRenderer;
using namespace PxToolkit;

///////////////////////////////////////////////////////////////////////////////

SampleCharacterCloth::SampleCharacterCloth(PhysXSampleApplication& app) :
	PhysXSample				(app, 2),
#if PX_SUPPORT_GPU_PHYSX
	mUseGPU                 (true),
#endif
	mCCTCamera				(NULL),
	mController             (NULL),
	mControllerManager		(NULL),
	mCCTDisplacement		(0.0f),
	mCCTDisplacementPrevStep(0.0f),
	mCCTTimeStep			(0.0f),
	mCape                   (NULL)
{
	mCreateGroundPlane  = false;
	mUseFixedStepper	= true;
	mControllerInitialPosition = PxVec3(0.0, 3.0f, 0.0);

	mCCTActive = false;

	mNbVerts	= 0;
	mNbTris		= 0;
	mVerts		= NULL;
	mTris		= NULL;
}

///////////////////////////////////////////////////////////////////////////////
SampleCharacterCloth::~SampleCharacterCloth()
{
	DELETESINGLE(mCCTCamera);

	SAMPLE_FREE(mTris);
	SAMPLE_FREE(mVerts);

	const size_t nbFlags = mFlags.size();
	for(PxU32 i = 0;i < nbFlags;i++)
		mFlags[i]->release();
}

///////////////////////////////////////////////////////////////////////////////
// create render materials used for render objects.
// The newly created materials are appended to PhysXSample::mRenderMaterials array
void SampleCharacterCloth::createRenderMaterials()
{
	getRenderer()->setAmbientColor(RendererColor(100, 100, 100));

	// create render materials used in this sample
	mSnowMaterial = SAMPLE_NEW(RenderMaterial)(*getRenderer(), PxVec3(0.70f, 0.70f, 0.8f), 1.0f, false, 0, NULL);
	mRenderMaterials.push_back(mSnowMaterial);

}

///////////////////////////////////////////////////////////////////////////////

void SampleCharacterCloth::customizeSample(SampleSetup& setup)
{
	setup.mName	= "SampleCharacterCloth";
}

///////////////////////////////////////////////////////////////////////////////

void SampleCharacterCloth::helpRender(PxU32 x, PxU32 y, PxU8 textAlpha)
{
	Renderer* renderer = getRenderer();
	const PxU32 yInc = 18;
	const PxReal scale = 0.5f;
	const PxReal shadowOffset = 6.0f;
	const RendererColor textColor(255, 255, 255, textAlpha);
	const bool isMouseSupported = getApplication().getPlatform()->getSampleUserInput()->mouseSupported();
	const bool isPadSupported = getApplication().getPlatform()->getSampleUserInput()->gamepadSupported();
	const char* msg;

	if (isMouseSupported && isPadSupported)
		renderer->print(x, y += yInc, "Use mouse or right stick to rotate the camera", scale, shadowOffset, textColor);
	else if (isMouseSupported)
		renderer->print(x, y += yInc, "Use mouse to rotate the camera", scale, shadowOffset, textColor);
	else if (isPadSupported)
		renderer->print(x, y += yInc, "Use right stick to rotate the camera", scale, shadowOffset, textColor);
	if (isPadSupported)
		renderer->print(x, y += yInc, "Use left stick to move",scale, shadowOffset, textColor);
	msg = mApplication.inputMoveInfoMsg("Press "," to move", CAMERA_MOVE_FORWARD,CAMERA_MOVE_BACKWARD, CAMERA_MOVE_LEFT, CAMERA_MOVE_RIGHT);
	if(msg)
		renderer->print(x, y += yInc, msg,scale, shadowOffset, textColor);
	msg = mApplication.inputInfoMsg("Press "," to move fast", CAMERA_SHIFT_SPEED, -1);
	if(msg)
		renderer->print(x, y += yInc, msg, scale, shadowOffset, textColor);
	msg = mApplication.inputInfoMsg("Press "," to jump", CAMERA_JUMP, -1);
	if(msg)
		renderer->print(x, y += yInc, msg,scale, shadowOffset, textColor);

	msg = mApplication.inputInfoMsg("Press "," to toggle visualization", TOGGLE_VISUALIZATION, -1);
	if(msg)
		renderer->print(x, y += yInc, msg,scale, shadowOffset, textColor);

	msg = mApplication.inputInfoMsg("Press "," to reset scene", RESET_SCENE, -1);
	if(msg)
		renderer->print(x, y += yInc, msg,scale, shadowOffset, textColor);

#if defined(PX_WINDOWS)
	msg = mApplication.inputInfoMsg("Press "," to toggle CPU/GPU", TOGGLE_CPU_GPU, -1);
	if(msg)
		renderer->print(x, y += yInc, msg,scale, shadowOffset, textColor);
#endif
}

void SampleCharacterCloth::descriptionRender(PxU32 x, PxU32 y, PxU8 textAlpha)
{
	bool print=(textAlpha!=0.0f);

	if(print)
	{
		Renderer* renderer = getRenderer();
		const PxU32 yInc = 24;
		const PxReal scale = 0.5f;
		const PxReal shadowOffset = 6.0f;
		const RendererColor textColor(255, 255, 255, textAlpha);

		char line0[256]="This sample demonstrates the PhysX cloth feature.  In particular, the ";
		char line1[256]="setup and simulation of a cape attached to an animated character is";
		char line2[256]="presented. This involves generating an approximate description of the";  
		char line3[256]="character's geometry, cloth instantiation, the binding of the cloth to a";
		char line4[256]="skinned character, and the setup of simulation parameters and values";
		char line5[256]="controlling the different phases of the cloth solver.  To clarify the";
		char line6[256]="process, and to offer some variety, a flag is also created and simulated.";
#ifdef PX_WINDOWS
		char line7[256]="Finally, the sample illustrates the steps required to enable GPU";
		char line8[256]="acceleration of PhysX cloth.";
#endif

		renderer->print(x, y+=yInc, line0, scale, shadowOffset, textColor);
		renderer->print(x, y+=yInc, line1, scale, shadowOffset, textColor);
		renderer->print(x, y+=yInc, line2, scale, shadowOffset, textColor);
		renderer->print(x, y+=yInc, line3, scale, shadowOffset, textColor);
		renderer->print(x, y+=yInc, line4, scale, shadowOffset, textColor);
		renderer->print(x, y+=yInc, line5, scale, shadowOffset, textColor);
		renderer->print(x, y+=yInc, line6, scale, shadowOffset, textColor);
#ifdef PX_WINDOWS
		renderer->print(x, y+=yInc, line7, scale, shadowOffset, textColor);
		renderer->print(x, y+=yInc, line8, scale, shadowOffset, textColor);
#endif
	}
}

///////////////////////////////////////////////////////////////////////////////
void SampleCharacterCloth::customizeRender()
{
#if PX_SUPPORT_GPU_PHYSX
	SampleRenderer::Renderer* renderer = getRenderer();

	const PxU32 yInc = 18;
	const PxReal scale = 0.5f;
	const PxReal shadowOffset = 6.0f;
	PxU32 width, height;
	renderer->getWindowSize(width, height);

	PxU32 y = height-2*yInc;
	PxU32 x = width - 240;

	{
		const RendererColor textColor(255, 0, 0, 255);
		renderer->print(x, y, mUseGPU ? "Running on GPU" : "Running on CPU", scale, shadowOffset, textColor);
	}
#endif

}

///////////////////////////////////////////////////////////////////////////////
void SampleCharacterCloth::onInit()
{
#if defined(PX_PS3)
	mNbThreads = 1;
#elif defined(PX_APPLE_IOS)
	mNbThreads = 2;
#else
	mNbThreads = 3;
#endif
	
	// try to get gpu support
	mCreateCudaCtxManager = true;

	PhysXSample::onInit();

	mApplication.setMouseCursorHiding(true);
	mApplication.setMouseCursorRecentering(true);

	// create materials and render setup
	createRenderMaterials();
	
	// build static heightfield landscape
	buildHeightField();

	// create CCT controller 
	createCCTController();

	// create the stickman character
	createCharacter();

	// create a cape for the stickman
	createCape();

	// create flags
	createFlags();
	
	// reset scene
	resetScene();
}

///////////////////////////////////////////////////////////////////////////////
void SampleCharacterCloth::resetScene()
{	
	// reset cct 
	PxVec3 pos = mControllerInitialPosition;
	mController->setPosition(PxExtendedVec3(pos.x, pos.y, pos.z));

	// compute global pose and local positions
	PxExtendedVec3 posExt = mController->getPosition();
	PxTransform pose = mController->getActor()->getGlobalPose();
	pose.p = PxVec3(PxReal(posExt.x), PxReal(posExt.y), PxReal(posExt.z)) - PxVec3(0.0f, 1.5, 0.0f);

	mCharacter.setGlobalPose(pose);

	resetCharacter();
	resetCape();

	// reset camera
	mCCTCamera->setView(0.0f, 0.0f);
}

///////////////////////////////////////////////////////////////////////////////
void SampleCharacterCloth::onShutdown()
{
	DELETESINGLE(mCCTCamera);
	SAFE_RELEASE(mControllerManager);
	PhysXSample::onShutdown();
}

///////////////////////////////////////////////////////////////////////////////
void SampleCharacterCloth::onTickPreRender(float dtime)
{
	PhysXSample::onTickPreRender(dtime);
}

///////////////////////////////////////////////////////////////////////////////
// called after each substep is done (can be called more than once per frame)
void SampleCharacterCloth::onSubstep(float dtime)
{
	updateCCT(dtime);
	updateCharacter(dtime);
	updateCape(dtime);
	updateFlags(dtime);

#if PX_SUPPORT_GPU_PHYSX
	// update the GPU flag (may have been disabled if CUDA error, not enough shared memory, etc)
	mUseGPU = mCape->getClothFlags()&PxClothFlag::eGPU;
#endif
}

///////////////////////////////////////////////////////////////////////////////
void SampleCharacterCloth::onTickPostRender(float dtime)
{
	PhysXSample::onTickPostRender(dtime);
}

///////////////////////////////////////////////////////////////////////////////
void SampleCharacterCloth::onPointerInputEvent(const SampleFramework::InputEvent& ie, physx::PxU32 x, physx::PxU32 y, physx::PxReal dx, physx::PxReal dy, bool val)
{
	PhysXSample::onPointerInputEvent(ie,x,y,dx,dy,val);
}

///////////////////////////////////////////////////////////////////////////////
static PxFilterFlags filter(PxFilterObjectAttributes attributes0,
							PxFilterData filterData0, 
							PxFilterObjectAttributes attributes1,
							PxFilterData filterData1,
							PxPairFlags& pairFlags,
							const void* constantBlock,
							PxU32 constantBlockSize)
{
	pairFlags |= PxPairFlag::eCONTACT_DEFAULT;
	return PxFilterFlags();
}

///////////////////////////////////////////////////////////////////////////////
void SampleCharacterCloth::customizeSceneDesc(PxSceneDesc& sceneDesc)
{
	sceneDesc.gravity		= PxVec3(0,-9.81,0);
	sceneDesc.filterShader	= filter;
}

#endif // PX_USE_CLOTH_API


