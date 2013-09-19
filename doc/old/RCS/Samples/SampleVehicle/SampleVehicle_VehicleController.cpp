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

#include "SampleVehicle_VehicleController.h"
#include "PhysXSample.h"
#include "vehicle/PxVehicleDrive4W.h"
#include "vehicle/PxVehicleUtilControl.h"

using namespace SampleRenderer;
using namespace SampleFramework;

PxVehicleKeySmoothingData gKeySmoothingData=
{
	{
		3.0f,	//rise rate eANALOG_INPUT_ACCEL		
		3.0f,	//rise rate eANALOG_INPUT_BRAKE		
		10.0f,	//rise rate eANALOG_INPUT_HANDBRAKE	
		2.5f,	//rise rate eANALOG_INPUT_STEER_LEFT	
		2.5f,	//rise rate eANALOG_INPUT_STEER_RIGHT	
	},
	{
		5.0f,	//fall rate eANALOG_INPUT__ACCEL		
		5.0f,	//fall rate eANALOG_INPUT__BRAKE		
		10.0f,	//fall rate eANALOG_INPUT__HANDBRAKE	
		5.0f,	//fall rate eANALOG_INPUT_STEER_LEFT	
		5.0f	//fall rate eANALOG_INPUT_STEER_RIGHT	
	}
};

PxVehiclePadSmoothingData gCarPadSmoothingData=
{
	{
		6.0f,	//rise rate eANALOG_INPUT_ACCEL		
		6.0f,	//rise rate eANALOG_INPUT_BRAKE		
		12.0f,	//rise rate eANALOG_INPUT_HANDBRAKE	
		2.5f,	//rise rate eANALOG_INPUT_STEER_LEFT	
		2.5f,	//rise rate eANALOG_INPUT_STEER_RIGHT	
	},
	{
		10.0f,	//fall rate eANALOG_INPUT_ACCEL		
		10.0f,	//fall rate eANALOG_INPUT_BRAKE		
		12.0f,	//fall rate eANALOG_INPUT_HANDBRAKE	
		5.0f,	//fall rate eANALOG_INPUT_STEER_LEFT	
		5.0f	//fall rate eANALOG_INPUT_STEER_RIGHT	
	}
};

PxF32 gSteerVsForwardSpeedData[2*8]=
{
	0.0f,		0.75f,
	5.0f,		0.75f,
	30.0f,		0.125f,
	120.0f,		0.1f,
	PX_MAX_F32, PX_MAX_F32,
	PX_MAX_F32, PX_MAX_F32,
	PX_MAX_F32, PX_MAX_F32,
	PX_MAX_F32, PX_MAX_F32
};
PxFixedSizeLookupTable<8> gSteerVsForwardSpeedTable(gSteerVsForwardSpeedData,4);
			
///////////////////////////////////////////////////////////////////////////////

SampleVehicle_VehicleController::SampleVehicle_VehicleController()
{
	clear();
}

SampleVehicle_VehicleController::~SampleVehicle_VehicleController()
{
}

void SampleVehicle_VehicleController::clear()
{
	mKeyPressedAccel					 = false;
	mKeyPressedBrake					 = false;
	mKeyPressedHandbrake				 = false;
	mKeyPressedSteerLeft				 = false;
	mKeyPressedSteerRight				 = false;
	mKeyPressedGearUp					 = false;
	mKeyPressedGearDown					 = false;
	mGamepadAccel						 = 0.0f;
	mGamepadGearup						 = false;			
	mGamepadGeardown					 = false;
	mGamepadCarBrake					 = 0.0f;
	mGamepadCarSteer					 = 0.0f;
	mGamepadCarHandbrake				 = false;
	mRecord								 = false;
	mReplay								 = false;
	mNumSamples							 = 0;
	mNumRecordedSamples					 = 0;
	mUseKeyInputs						 = true;
	mToggleAutoGears					 = false;
	mIsMovingForwardSlowly				 = true;
	mInReverseMode						 = false;
}


void SampleVehicle_VehicleController::processRawInputs
(const PxF32 dtime, const bool useAutoGears, PxVehicleDrive4WRawInputData& rawInputData)
{
	// Keyboard
	{
		if(mRecord)
		{
			if(mNumSamples<MAX_NUM_RECORD_REPLAY_SAMPLES)
			{
				mKeyboardAccelValues[mNumSamples]		= mKeyPressedAccel;
				mKeyboardBrakeValues[mNumSamples]		= mKeyPressedBrake;
				mKeyboardHandbrakeValues[mNumSamples]	= mKeyPressedHandbrake;
				mKeyboardSteerLeftValues[mNumSamples]	= mKeyPressedSteerLeft;
				mKeyboardSteerRightValues[mNumSamples]	= mKeyPressedSteerRight;
				mKeyboardGearupValues[mNumSamples]		= mKeyPressedGearUp;
				mKeyboardGeardownValues[mNumSamples]	= mKeyPressedGearDown;
			}
		}
		else if(mReplay)
		{
			if(mNumSamples<mNumRecordedSamples)
			{
				mKeyPressedAccel		= mKeyboardAccelValues[mNumSamples];		
				mKeyPressedBrake		= mKeyboardBrakeValues[mNumSamples];		
				mKeyPressedHandbrake	= mKeyboardHandbrakeValues[mNumSamples];	
				mKeyPressedSteerLeft	= mKeyboardSteerLeftValues[mNumSamples];
				mKeyPressedSteerRight	= mKeyboardSteerRightValues[mNumSamples];	
				mKeyPressedGearUp		= mKeyboardGearupValues[mNumSamples];	
				mKeyPressedGearDown		= mKeyboardGeardownValues[mNumSamples];
			}
		}

		rawInputData.setDigitalAccel(mKeyPressedAccel);
		rawInputData.setDigitalBrake(mKeyPressedBrake);
		rawInputData.setDigitalHandbrake(mKeyPressedHandbrake);
		rawInputData.setDigitalSteerLeft(mKeyPressedSteerLeft);
		rawInputData.setDigitalSteerRight(mKeyPressedSteerRight);
		rawInputData.setGearUp(mKeyPressedGearUp);
		rawInputData.setGearDown(mKeyPressedGearDown);

		mUseKeyInputs=
			(mKeyPressedAccel || mKeyPressedBrake  || mKeyPressedHandbrake || 
			 mKeyPressedSteerLeft || mKeyPressedSteerRight || 
			 mKeyPressedGearUp || mKeyPressedGearDown);
	}

	// Gamepad
	{
		if(mRecord)
		{
			if(mNumSamples<MAX_NUM_RECORD_REPLAY_SAMPLES)
			{
				mGamepadAccelValues[mNumSamples]		= mGamepadAccel;
				mGamepadCarBrakeValues[mNumSamples]		= mGamepadCarBrake;
				mGamepadCarSteerValues[mNumSamples]		= mGamepadCarSteer;
				mGamepadGearupValues[mNumSamples]		= mGamepadGearup;
				mGamepadGeardownValues[mNumSamples]		= mGamepadGeardown;
				mGamepadCarHandbrakeValues[mNumSamples]	= mGamepadCarHandbrake;
			}
		}
		else if(mReplay)
		{
			if(mNumSamples<mNumRecordedSamples)
			{
				mGamepadAccel		= mGamepadAccelValues[mNumSamples];		
				mGamepadCarBrake		= mGamepadCarBrakeValues[mNumSamples];		
				mGamepadCarSteer		= mGamepadCarSteerValues[mNumSamples];		
				mGamepadGearup		= mGamepadGearupValues[mNumSamples];	
				mGamepadGeardown	= mGamepadGeardownValues[mNumSamples];	
				mGamepadCarHandbrake	= mGamepadCarHandbrakeValues[mNumSamples];	
			}
		}

		if(mGamepadAccel<0.0f || mGamepadAccel>1.01f)
			getSampleErrorCallback().reportError(PxErrorCode::eINTERNAL_ERROR, "Illegal accel value from gamepad", __FILE__, __LINE__);

		if(mGamepadCarBrake<0.0f || mGamepadCarBrake>1.01f)
			getSampleErrorCallback().reportError(PxErrorCode::eINTERNAL_ERROR, "Illegal brake value from gamepad", __FILE__, __LINE__);

		if(PxAbs(mGamepadCarSteer)>1.01f)
			getSampleErrorCallback().reportError(PxErrorCode::eINTERNAL_ERROR, "Illegal steer value from gamepad", __FILE__, __LINE__);

		if(mUseKeyInputs && ((mGamepadAccel+mGamepadCarBrake+mGamepadCarSteer)!=0.0f ||  mGamepadGearup || mGamepadGeardown || mGamepadCarHandbrake))
		{
			mUseKeyInputs=false;
		}

		if(!mUseKeyInputs)
		{
			rawInputData.setAnalogAccel(mGamepadAccel);
			rawInputData.setAnalogBrake(mGamepadCarBrake);
			rawInputData.setAnalogHandbrake(mGamepadCarHandbrake ? 1.0f : 0.0f);
			rawInputData.setAnalogSteer(mGamepadCarSteer);
			rawInputData.setGearUp(mGamepadGearup);
			rawInputData.setGearDown(mGamepadGeardown);
		}
	}

	if(useAutoGears && (rawInputData.getGearDown() || rawInputData.getGearUp()))
	{
		rawInputData.setGearDown(false);
		rawInputData.setGearUp(false);
	}

	mNumSamples++;
}


#define THRESHOLD_FORWARD_SPEED (0.1f) 
#define THRESHOLD_SIDEWAYS_SPEED (0.2f)
#define THRESHOLD_ROLLING_BACKWARDS_SPEED (0.1f)

void SampleVehicle_VehicleController::processAutoReverse
(const PxVehicleWheels& focusVehicle, const PxVehicleDriveDynData& driveDynData, const PxVehicleDrive4WRawInputData& carRawInputs,
 bool& toggleAutoReverse, bool& newIsMovingForwardSlowly) const
{
	newIsMovingForwardSlowly = false;
	toggleAutoReverse = false;

	if(driveDynData.getUseAutoGears())
	{
		//If the car is travelling very slowly in forward gear without player input and the player subsequently presses the brake then we want the car to go into reverse gear
		//If the car is travelling very slowly in reverse gear without player input and the player subsequently presses the accel then we want the car to go into forward gear
		//If the car is in forward gear and is travelling backwards then we want to automatically put the car into reverse gear.
		//If the car is in reverse gear and is travelling forwards then we want to automatically put the car into forward gear.
		//(If the player brings the car to rest with the brake the player needs to release the brake then reapply it 
		//to indicate they want to toggle between forward and reverse.)

		const bool prevIsMovingForwardSlowly=mIsMovingForwardSlowly;
		bool isMovingForwardSlowly=false;
		bool isMovingBackwards=false;
		const bool isInAir = focusVehicle.isInAir();
		if(!isInAir)
		{
			bool accelRaw,brakeRaw,handbrakeRaw;
			if(mUseKeyInputs)
			{
				accelRaw=carRawInputs.getDigitalAccel();
				brakeRaw=carRawInputs.getDigitalBrake();
				handbrakeRaw=carRawInputs.getDigitalHandbrake();
			}
			else
			{
				accelRaw=carRawInputs.getAnalogAccel() > 0 ? true : false;
				brakeRaw=carRawInputs.getAnalogBrake() > 0 ? true : false;
				handbrakeRaw=carRawInputs.getAnalogHandbrake() > 0 ? true : false;
			}

			const PxF32 forwardSpeed = focusVehicle.computeForwardSpeed();
			const PxF32 forwardSpeedAbs = PxAbs(forwardSpeed);
			const PxF32 sidewaysSpeedAbs = PxAbs(focusVehicle.computeSidewaysSpeed());
			const PxU32 currentGear = driveDynData.getCurrentGear();
			const PxU32 targetGear = driveDynData.getTargetGear();

			//Check if the car is rolling against the gear (backwards in forward gear or forwards in reverse gear).
			if(PxVehicleGearsData::eFIRST == currentGear  && forwardSpeed < -THRESHOLD_ROLLING_BACKWARDS_SPEED)
			{
				isMovingBackwards = true;
			}
			else if(PxVehicleGearsData::eREVERSE == currentGear && forwardSpeed > THRESHOLD_ROLLING_BACKWARDS_SPEED)
			{
				isMovingBackwards = true;
			}

			//Check if the car is moving slowly.
			if(forwardSpeedAbs < THRESHOLD_FORWARD_SPEED && sidewaysSpeedAbs < THRESHOLD_SIDEWAYS_SPEED)
			{
				isMovingForwardSlowly=true;
			}

			//Now work if we need to toggle from forwards gear to reverse gear or vice versa.
			if(isMovingBackwards)
			{
				if(!accelRaw && !brakeRaw && !handbrakeRaw && (currentGear == targetGear))			
				{
					//The car is rolling against the gear and the player is doing nothing to stop this.
					toggleAutoReverse = true;
				}
			}
			else if(prevIsMovingForwardSlowly && isMovingForwardSlowly)
			{
				if((currentGear > PxVehicleGearsData::eNEUTRAL) && brakeRaw && !accelRaw && (currentGear == targetGear))
				{
					//The car was moving slowly in forward gear without player input and is now moving slowly with player input that indicates the 
					//player wants to switch to reverse gear.
					toggleAutoReverse = true;
				}
				else if(currentGear == PxVehicleGearsData::eREVERSE && accelRaw && !brakeRaw && (currentGear == targetGear))
				{
					//The car was moving slowly in reverse gear without player input and is now moving slowly with player input that indicates the 
					//player wants to switch to forward gear.
					toggleAutoReverse = true;
				}
			}

			//If the car was brought to rest through braking then the player needs to release the brake then reapply
			//to indicate that the gears should toggle between reverse and forward.
			if(isMovingForwardSlowly && !brakeRaw && !accelRaw && !handbrakeRaw)
			{
				newIsMovingForwardSlowly = true;
			}
		}
	}
}

void SampleVehicle_VehicleController::update(const PxF32 timestep, PxVehicleWheels& focusVehicle)
{
	PX_ASSERT(eVEHICLE_TYPE_DRIVE4W==focusVehicle.getVehicleType());
	PxVehicleDrive4W& vehDrive4W=(PxVehicleDrive4W&)focusVehicle;
	PxVehicleDriveDynData& driveDynData=vehDrive4W.mDriveDynData;

	//Toggle autogear flag
	if(mToggleAutoGears)
	{
		driveDynData.toggleAutoGears();
		mToggleAutoGears = false;
	}

	//Store raw inputs in replay stream if in recording mode.
	//Set raw inputs from replay stream if in replay mode.
	//Store raw inputs from active stream in handy arrays so we don't need to worry
	//about which stream (live input or replay) is active.
	//Work out if we are using keys or gamepad controls depending on which is being used
	//(gamepad selected if both are being used).
	PxVehicleDrive4WRawInputData carRawInputs;
	processRawInputs(timestep,driveDynData.getUseAutoGears(),carRawInputs);

	//Work out if the car is to flip from reverse to forward gear or from forward gear to reverse.
	//Store if the car is moving slowly to help decide if the car is to toggle from reverse to forward in the next update.
	bool toggleAutoReverse = false;
	bool newIsMovingForwardSlowly = false;
	processAutoReverse(focusVehicle, driveDynData, carRawInputs, toggleAutoReverse, newIsMovingForwardSlowly);
	mIsMovingForwardSlowly = newIsMovingForwardSlowly;

	//If the car is to flip gear direction then switch gear as appropriate.
	if(toggleAutoReverse)
	{
		mInReverseMode = !mInReverseMode;
		
		if(mInReverseMode)
		{
			driveDynData.forceGearChange(PxVehicleGearsData::eREVERSE);
		}
		else
		{
			driveDynData.forceGearChange(PxVehicleGearsData::eFIRST);
		}
	}

	//If in reverse mode then swap the accel and brake.
	if(mInReverseMode)
	{
		if(mUseKeyInputs)
		{
			const bool accel=carRawInputs.getDigitalAccel();
			const bool brake=carRawInputs.getDigitalBrake();
			carRawInputs.setDigitalAccel(brake);
			carRawInputs.setDigitalBrake(accel);
		}
		else
		{
			const PxF32 accel=carRawInputs.getAnalogAccel();
			const PxF32 brake=carRawInputs.getAnalogBrake();
			carRawInputs.setAnalogAccel(brake);
			carRawInputs.setAnalogBrake(accel);
		}
	}

	// Now filter the raw input values and apply them to focus vehicle
	// as floats for brake,accel,handbrake,steer and bools for gearup,geardown.
	if(mUseKeyInputs)
	{
		PxVehicleDrive4WSmoothDigitalRawInputsAndSetAnalogInputs(gKeySmoothingData,gSteerVsForwardSpeedTable,carRawInputs,timestep,(PxVehicleDrive4W&)focusVehicle);
	}
	else
	{
		PxVehicleDrive4WSmoothAnalogRawInputsAndSetAnalogInputs(gCarPadSmoothingData,gSteerVsForwardSpeedTable,carRawInputs,timestep,(PxVehicleDrive4W&)focusVehicle);
	}
}

void SampleVehicle_VehicleController::restart()
{
	const bool record=mRecord;
	const bool replay=mReplay;
	const PxU32 numSamples=mNumSamples;
	const PxU32 numRecordedSamples=mNumRecordedSamples;
	clear();
	mRecord=record;
	mReplay=replay;
	mNumRecordedSamples=numRecordedSamples;

	if(record)
	{
		PX_ASSERT(!replay);
		mNumRecordedSamples	= numSamples;
		mRecord				= false;
		mReplay				= true;
	}
}
