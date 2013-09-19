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

#include "SampleBridges.h"
#include "SampleUtils.h"
#include "PxPhysicsAPI.h"
#include "SampleAllocatorSDKClasses.h"
#include "SampleBridgesInputEventIds.h"
#ifdef CCT_ON_BRIDGES
	#include "KinematicPlatform.h"
	#include "SampleCCTActor.h"
	#include "SampleCCTCameraController.h"
	extern const char* gPlankName;
	extern const char* gPlatformName;
#endif
#include <SamplePlatform.h>
#include <SampleUserInput.h>
#include <SampleUserInputIds.h>
#include <SampleUserInputDefines.h>

using namespace SampleRenderer;
using namespace SampleFramework;

///////////////////////////////////////////////////////////////////////////////

void SampleBridges::collectInputEvents(std::vector<const InputEvent*>& inputEvents)
{
	PhysXSample::collectInputEvents(inputEvents);
	getApplication().getPlatform()->getSampleUserInput()->unregisterInputEvent(VARIABLE_TIMESTEP);

	//digital keyboard events
	DIGITAL_INPUT_EVENT_DEF(RETRY,			WKEY_R,	XKEY_R,	PS3KEY_R,	AKEY_UNKNOWN,	OSXKEY_R,	PSP2KEY_UNKNOWN,    IKEY_UNKNOWN,	LINUXKEY_R);
	DIGITAL_INPUT_EVENT_DEF(TELEPORT,		WKEY_T,	XKEY_T,	PS3KEY_T,	AKEY_UNKNOWN,	OSXKEY_T,	PSP2KEY_UNKNOWN,	IKEY_UNKNOWN,	LINUXKEY_T);
	DIGITAL_INPUT_EVENT_DEF(CAMERA_LINK,	WKEY_X,	XKEY_X,	PS3KEY_X,	AKEY_UNKNOWN,	OSXKEY_X,	PSP2KEY_UNKNOWN,	IKEY_UNKNOWN,	LINUXKEY_X);
	DIGITAL_INPUT_EVENT_DEF(DEBUG_RENDER,	WKEY_J,	XKEY_J,	PS3KEY_J,	AKEY_UNKNOWN,	OSXKEY_J,	PSP2KEY_UNKNOWN,	IKEY_UNKNOWN,	LINUXKEY_J);

	// gamepad events
	DIGITAL_INPUT_EVENT_DEF(RETRY,			GAMEPAD_DIGI_LEFT,  GAMEPAD_DIGI_LEFT,  GAMEPAD_DIGI_LEFT,  AKEY_UNKNOWN, OSXKEY_UNKNOWN, GAMEPAD_DIGI_LEFT,    IKEY_UNKNOWN, LINUXKEY_UNKNOWN);
	DIGITAL_INPUT_EVENT_DEF(TELEPORT,		GAMEPAD_DIGI_RIGHT, GAMEPAD_DIGI_RIGHT, GAMEPAD_DIGI_RIGHT, AKEY_UNKNOWN, OSXKEY_UNKNOWN, GAMEPAD_DIGI_RIGHT,   IKEY_UNKNOWN, LINUXKEY_UNKNOWN);
	DIGITAL_INPUT_EVENT_DEF(CAMERA_LINK,	GAMEPAD_DIGI_DOWN,  GAMEPAD_DIGI_DOWN,  GAMEPAD_DIGI_DOWN,  AKEY_UNKNOWN, OSXKEY_UNKNOWN, PSP2KEY_UNKNOWN,      IKEY_UNKNOWN, LINUXKEY_UNKNOWN);
    
    //touch events
    TOUCH_INPUT_EVENT_DEF(RETRY,			"Retry",		ABUTTON_5,			IBUTTON_5);
	TOUCH_INPUT_EVENT_DEF(TELEPORT,         "Teleport",		ABUTTON_6,          IBUTTON_6);
	TOUCH_INPUT_EVENT_DEF(CAMERA_CROUCH,    "Crouch",		ABUTTON_7,          IBUTTON_7);
    TOUCH_INPUT_EVENT_DEF(CAMERA_JUMP,      "Jump",			AQUICK_BUTTON_1,    IQUICK_BUTTON_1);
}

PxU32 SampleBridges::getDebugObjectTypes() const
{
	return DEBUG_OBJECT_BOX | DEBUG_OBJECT_SPHERE | DEBUG_OBJECT_CAPSULE | DEBUG_OBJECT_CONVEX;
}

bool SampleBridges::onDigitalInputEvent(const InputEvent& ie, bool val)
{
	switch (ie.m_Id)
	{
	case RETRY:
		{
			if(val)
			{
#ifdef CCT_ON_BRIDGES
				mActor->reset();
				mCCTCamera->setView(0,0);
#endif
			}
		}
		break;
	case TELEPORT:
		{
			if(val)
			{
#ifdef CCT_ON_BRIDGES
		if(mCurrentPlatform==0xffffffff)
			mCurrentPlatform = 0;
		else
		{
			mCurrentPlatform++;
			if(mCurrentPlatform==mPlatformManager.getNbPlatforms())
				mCurrentPlatform = 0;
		}
		const KinematicPlatform* platform = mPlatformManager.getPlatforms()[mCurrentPlatform];
	#ifdef PLATFORMS_AS_OBSTACLES
		mActor->teleport(platform->getRenderPose().p+PxVec3(0.0f, 6.0f, 0.0f));
	#else
		mActor->teleport(platform->getPhysicsPose().p+PxVec3(0.0f, 3.0f, 0.0f));
	#endif
#endif
			}
		}
		break;
	case CAMERA_LINK:
		{
			if(val)
			{
#ifdef CCT_ON_BRIDGES
				mCCTCamera->setCameraLinkToPhysics(!mCCTCamera->getCameraLinkToPhysics());
#endif
			}
		}
		break;
	case DEBUG_RENDER:
		{
			if(val)
				mEnableCCTDebugRender = !mEnableCCTDebugRender;
		}
	}

	PhysXSample::onDigitalInputEvent(ie,val);

	return true;
}

///////////////////////////////////////////////////////////////////////////////

static PxFilterFlags SampleBridgesFilterShader(	PxFilterObjectAttributes attributes0, PxFilterData filterData0, 
												PxFilterObjectAttributes attributes1, PxFilterData filterData1,
												PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize)
{
	pairFlags = PxPairFlag::eCONTACT_DEFAULT;

	return PxFilterFlags();
}

///////////////////////////////////////////////////////////////////////////////

void SampleBridges::customizeSceneDesc(PxSceneDesc& sceneDesc)
{
	sceneDesc.filterShader				= SampleBridgesFilterShader;
}

///////////////////////////////////////////////////////////////////////////////

#ifdef CCT_ON_BRIDGES
void SampleBridges::onShapeHit(const PxControllerShapeHit& hit)
{
	defaultCCTInteraction(hit);
}

PxU32 SampleBridges::getBehaviorFlags(const PxShape& shape)
{
	const char* actorName = shape.getActor().getName();
#ifdef PLATFORMS_AS_OBSTACLES
	PX_ASSERT(actorName!=gPlatformName);	// PT: in this mode we should have filtered out those guys already
#endif

	// PT: ride on planks
	if(actorName==gPlankName)
		return PxControllerBehaviorFlag::eCCT_CAN_RIDE_ON_OBJECT;

	// PT: ride & slide on platforms
	if(actorName==gPlatformName)
		return PxControllerBehaviorFlag::eCCT_CAN_RIDE_ON_OBJECT|PxControllerBehaviorFlag::eCCT_SLIDE;

	return 0;
}

PxU32 SampleBridges::getBehaviorFlags(const PxController&)
{
	return 0;
}

PxU32 SampleBridges::getBehaviorFlags(const PxObstacle&)
{
	return PxControllerBehaviorFlag::eCCT_CAN_RIDE_ON_OBJECT|PxControllerBehaviorFlag::eCCT_SLIDE;
}

PxSceneQueryHitType::Enum SampleBridges::preFilter(const PxFilterData& filterData, PxShape* shape, PxSceneQueryFilterFlags& filterFlags)
{
#ifdef PLATFORMS_AS_OBSTACLES
	const char* actorName = shape->getActor().getName();
	if(actorName==gPlatformName)
		return PxSceneQueryHitType::eNONE;
#endif

	return PxSceneQueryHitType::eBLOCK;
}

PxSceneQueryHitType::Enum SampleBridges::postFilter(const PxFilterData& filterData, const PxSceneQueryHit& hit)
{
	return PxSceneQueryHitType::eBLOCK;
}

#endif
