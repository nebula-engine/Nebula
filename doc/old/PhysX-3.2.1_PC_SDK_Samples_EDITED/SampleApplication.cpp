/*
 * Copyright 2008-2012 NVIDIA Corporation.  All rights reserved.
 *
 * NOTICE TO USER:
 *
 * This source code is subject to NVIDIA ownership rights under U.S. and
 * international Copyright laws.  Users and possessors of this source code
 * are hereby granted a nonexclusive, royalty-free license to use this code
 * in individual and commercial software.
 *
 * NVIDIA MAKES NO REPRESENTATION ABOUT THE SUITABILITY OF THIS SOURCE
 * CODE FOR ANY PURPOSE.  IT IS PROVIDED "AS IS" WITHOUT EXPRESS OR
 * IMPLIED WARRANTY OF ANY KIND.  NVIDIA DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOURCE CODE, INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE.
 * IN NO EVENT SHALL NVIDIA BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF USE, DATA OR PROFITS,  WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
 * OR OTHER TORTIOUS ACTION,  ARISING OUT OF OR IN CONNECTION WITH THE USE
 * OR PERFORMANCE OF THIS SOURCE CODE.
 *
 * U.S. Government End Users.   This source code is a "commercial item" as
 * that term is defined at  48 C.F.R. 2.101 (OCT 1995), consisting  of
 * "commercial computer  software"  and "commercial computer software
 * documentation" as such terms are  used in 48 C.F.R. 12.212 (SEPT 1995)
 * and is provided to the U.S. Government only as a commercial end item.
 * Consistent with 48 C.F.R.12.212 and 48 C.F.R. 227.7202-1 through
 * 227.7202-4 (JUNE 1995), all U.S. Government End Users acquire the
 * source code with only those rights set forth herein.
 *
 * Any use of this source code in individual and commercial software must
 * include, in the user documentation and internal comments to the code,
 * the above Disclaimer and U.S. Government End Users Notice.
 */
#include "AgPerfMonEventSrcAPI.h"
#include <NxApplication.h>
#include <NxCommandLine.h>
#include <SampleAssetManager.h>
#include <Renderer.h>
#include <RendererDesc.h>
#include <RendererMemoryMacros.h>
#include <SamplePlatform.h>
#include "SampleFrameworkInputEventIds.h"
// for PsString.h
namespace physx
{
	namespace string {}
}
#include <PsString.h>
#include "PsFoundation.h"
#include "PsUtilities.h"

//#define RENDERER_USE_OPENGL_ON_WINDONWS	1

#ifdef AGPERFMON
#define DEFINE_EVENT(name) #name,
const char *AgAppPerfUtils::mEventNames[] = {
#include "AgPerfMonEventDefs.h"
	""
};

AgAppPerfUtils* gAppPerfUtils = NULL;

#undef DEFINE_EVENT
#endif

#ifdef PHYSX_PROFILE_SDK
#include "SamplePxProfileZone.h"
#include "PxProfileZone.h"
#include "PxProfileZoneManager.h"
extern SampleProfileEventNameProvider gProfileNameProvider;
#endif //PHYSX_PROFILE_SDK

#ifdef PX_ANDROID
#define LOGI(...) LOG_INFO("NxApplication", __VA_ARGS__)
#define printf LOGI
#endif
#if defined(SMOOTH_CAM)
const float g_smoothCamBaseVel  = 6.0f;
const float g_smoothCamFastMul = 4.0f;
const float g_smoothCamPosLerp  = 0.4f;

const float g_smoothCamRotSpeed = 0.005f;
const float g_smoothCamRotLerp  = 0.4f;
#endif

#include "FrameworkFoundation.h"

using namespace SampleFramework;

								NxApplication::NxApplication(const NxCommandLine &cmdline, const char *assetPathPrefix, PxI32 camMoveButton) :
	m_cmdline(cmdline),
	m_disableRendering(false)
{
	m_platform->setCWDToEXE();

	if (assetPathPrefix)
	{
		if (!searchForPath(assetPathPrefix, m_assetPathPrefix, PX_ARRAY_SIZE(m_assetPathPrefix), true, 20))
		{
			RENDERER_ASSERT(false, "assetPathPrefix could not be found in any of the parent directories!");
			m_assetPathPrefix[0] = 0;
		}
	}
	else
	{
		RENDERER_ASSERT(assetPathPrefix, "assetPathPrefix must not be NULL (try \"media\" instead)");
		m_assetPathPrefix[0] = 0;		
	}

	m_renderer      = 0;
	m_sceneSize     = 1.0f;
	m_assetManager  = 0;
	m_timeCounter	= 0;
	m_camMoveButton = camMoveButton;

#ifdef AGPERFMON
#ifndef WIN32
#define MAX_IP_LENGTH 32
	FILE *agInFile = NULL;
	char ipBuffer[MAX_IP_LENGTH];
	//shdfnd::fopen_s(&agInFile, "/app_home/APEX/1.0/common/perfmonConfig.txt", "r");

	if (agInFile!=NULL)
	{
		// obtain file size:
		fseek (agInFile , 0 , SEEK_END);
		int lSize = ftell (agInFile);
		if (lSize > MAX_IP_LENGTH)
			lSize = MAX_IP_LENGTH;

		rewind (agInFile);

		// copy the file into the buffer
		fread (ipBuffer,1,lSize,agInFile);
		ipBuffer[lSize] = '\0';

		// terminate
		fclose (agInFile);
		AgAppPerfUtils::SetIPAddress(ipBuffer);
	}
	else
		AgAppPerfUtils::SetIPAddress("10.20.200.134");
#endif //!WIN32
	gAppPerfUtils = new AgAppPerfUtils;
#endif //AGPERFMON
	mProfileZone    = NULL;

	m_ActorManager  = NX_NEW(NxActorManager)();
	m_VehicleManager= NX_NEW(m_VehicleManager)();
	m_SceneManager  = NX_NEW(m_SceneManager)();
}
								NxApplication::~NxApplication(void)
{
	RENDERER_ASSERT(!m_renderer, "Renderer was not released prior to window closure.");
	RENDERER_ASSERT(!m_assetManager, "Asset Manager was not released prior to window closure.");

	DELETESINGLE(m_platform);

#ifdef AGPERFMON
	if(gAppPerfUtils)
	{
		delete gAppPerfUtils;
		gAppPerfUtils = 0;
	}
#endif

	clearSearchPaths();
}
void							NxApplication::setEyeTransform(const PxMat44& eyeTransform)
{
	m_worldToView.setInverseTransform(eyeTransform);
	m_eyeRot = Mat33ToEuler(eyeTransform);
#if defined(SMOOTH_CAM)
	m_targetEyePos = m_worldToView.getInverseTransform().getPosition();
	m_targetEyeRot = m_eyeRot;
#endif
}
void							NxApplication::setEyeTransform(const PxVec3& pos, const PxVec3& rot)
{
	PxMat44 eye = PxMat44::createIdentity();
	m_eyeRot = rot;
	eye = EulerToMat33(m_eyeRot);
	eye.setPosition(pos);
#if defined(SMOOTH_CAM)
	m_targetEyePos = pos;
	m_targetEyeRot = m_eyeRot;
#endif

	m_worldToView.setInverseTransform(eye);
}
void							NxApplication::setViewTransform(const PxMat44 &viewTransform)
{
	m_worldToView.setForwardTransform(viewTransform);
	m_eyeRot = Mat33ToEuler( m_worldToView.getInverseTransform() );
#if defined(SMOOTH_CAM)
	m_targetEyePos = m_worldToView.getInverseTransform().getPosition();
	m_targetEyeRot = m_eyeRot;
#endif
}
const PxMat44&					NxApplication::getViewTransform() const
{
	return m_worldToView.getForwardTransform();
}
void							NxApplication::onOpen(void)
{
	m_platform->preRendererSetup();

	char assetDir[1024];
	physx::string::strcpy_s(assetDir, sizeof(assetDir), m_assetPathPrefix);
	physx::string::strcat_s(assetDir, sizeof(assetDir), ASSET_DIR);

	m_eyeRot = PxVec3(0,0,0);
	PxMat44 eye = PxMat44::createIdentity();
	const PxVec3 pos = PxVec3(0.0f, 2.0f, 16.0f);
	eye.setPosition(pos);
	m_worldToView.setInverseTransform(eye);
#if defined(SMOOTH_CAM)
	m_targetEyePos = pos;
	m_targetEyeRot = m_eyeRot;
#endif

	SampleRenderer::RendererDesc renDesc;

	// default renderer drivers for various platforms...
	m_platform->setupRendererDescription(renDesc);
#if defined RENDERER_USE_OPENGL_ON_WINDONWS
	renDesc.driver = SampleRenderer::Renderer::DRIVER_OPENGL;
#endif

	// check to see if the user wants to override the renderer driver...
	if(m_cmdline.hasSwitch("ogl"))        renDesc.driver = SampleRenderer::Renderer::DRIVER_OPENGL;
	else if(m_cmdline.hasSwitch("gles2")) renDesc.driver = SampleRenderer::Renderer::DRIVER_GLES2;
	else if(m_cmdline.hasSwitch("d3d9"))  renDesc.driver = SampleRenderer::Renderer::DRIVER_DIRECT3D9;
	else if(m_cmdline.hasSwitch("d3d10")) renDesc.driver = SampleRenderer::Renderer::DRIVER_DIRECT3D10;
	else if(m_cmdline.hasSwitch("gcm"))   renDesc.driver = SampleRenderer::Renderer::DRIVER_LIBGCM;

#if defined(RENDERER_ANDROID)
	renDesc.windowHandle = (physx::PxU64)android_window_ptr;
#endif

	m_renderer = SampleRenderer::Renderer::createRenderer(renDesc, assetDir);
	m_platform->postRendererSetup(m_renderer);

	m_timeCounter = m_time.getCurrentCounterValue();

	m_assetManager = new SampleAssetManager(*m_renderer);
	addSearchPath(m_assetPathPrefix);
	addSearchPath(assetDir);
	onInit();

	// make sure the resize method is called once
	if (m_renderer)
	{
		PxU32 width,height;
		m_renderer->getWindowSize(width, height);
		onResize(width, height);
		if ( mProfileZone != NULL )
			m_renderer->setProfileZone( mProfileZone );
	}
}
bool							NxApplication::onClose(void)
{
	onShutdown();
	DELETESINGLE(m_assetManager);

	SAFE_RELEASE(m_renderer);
	m_platform->postRendererRelease();

	return true;
}
void							NxApplication::onDraw(void)
{
	if (!getRenderer())
		return;
	
	SAMPLE_PERF_SCOPE(SampleOnDraw);
#if USE_MEMORY_TRACKER
	TRACK_FRAME();
#endif

	physx::PxU64 qpc = m_time.getCurrentCounterValue();
	static float sToSeconds = float(m_time.getBootCounterFrequency().mNumerator) / float(m_time.getBootCounterFrequency().mDenominator * m_time.sNumTensOfNanoSecondsInASecond);
	float dtime = float(qpc - m_timeCounter) * sToSeconds;

	m_timeCounter = qpc;
	PX_ASSERT(dtime > 0);
	if(dtime > 0)
	{
		dtime = tweakElapsedTime(dtime);

		SAMPLE_PERF_SCOPE( SampleOnTickPreRender );
		SampleRenderer::Renderer* renderer = getRenderer();
		renderer->finishRendering();
		onTickPreRender(dtime);
		
		if(m_renderer)
		{
			SAMPLE_PERF_SCOPE( SampleOnRender );
			if(!m_disableRendering)
			{
				onRender();
			}
		}
		
		SAMPLE_PERF_SCOPE( SampleOnTickPostRender );
		onTickPostRender(dtime);

		if(m_renderer && !m_disableRendering)
		{
			m_renderer->swapBuffers();
		}

		updateWorldToViewTransform();
	}
}
void							NxApplication::updateWorldToViewTransform()
{
	// update scene

	PxMat44 tmp = m_worldToView.getInverseTransform();
	PxMat44 eye = EulerToMat33(m_eyeRot);
	eye.column3 = tmp.column3;

	PxVec3* targetParam;
#if defined(SMOOTH_CAM)
	const float eyeSpeed = m_sceneSize * g_smoothCamBaseVel * dtime * (getPlatform()->getSampleUserInput()->getDigitalInputEventState(CAMERA_SHIFT_SPEED) ? g_smoothCamFastMul : 1.0f);
	targetParam = &m_targetEyePos;
#else
	const float eyeSpeed = m_sceneSize * 4.0f * dtime * (getPlatform()->getSampleUserInput()->getDigitalInputEventState(CAMERA_SHIFT_SPEED) ? 4.0f : 1.0f);
	targetParam = &eye.t;
#endif

	const PxVec3 column0 = eye.getBasis(0);
	const PxVec3 column1 = eye.getBasis(1);
	const PxVec3 column2 = eye.getBasis(2);

	if(getPlatform()->getSampleUserInput()->getDigitalInputEventState(CAMERA_MOVE_FORWARD))
		*targetParam -= column2 * eyeSpeed;
	if(getPlatform()->getSampleUserInput()->getDigitalInputEventState(CAMERA_MOVE_BACKWARD))
		*targetParam += column2 * eyeSpeed;
	if(getPlatform()->getSampleUserInput()->getDigitalInputEventState(CAMERA_MOVE_LEFT))
		*targetParam -= column0 * eyeSpeed;
	if(getPlatform()->getSampleUserInput()->getDigitalInputEventState(CAMERA_MOVE_RIGHT))
		*targetParam += column0 * eyeSpeed;
	if(getPlatform()->getSampleUserInput()->getDigitalInputEventState(CAMERA_MOVE_UP))
		*targetParam += column1 * eyeSpeed;
	if(getPlatform()->getSampleUserInput()->getDigitalInputEventState(CAMERA_MOVE_DOWN))
		*targetParam -= column1 * eyeSpeed;

	// move forward from gamepad
	*targetParam -= column2 * eyeSpeed *  getPlatform()->getSampleUserInput()->getAnalogInputEventState(CAMERA_GAMEPAD_MOVE_FORWARD_BACK) * 40.0f * dtime;
	// strafe from gamepad
	*targetParam += column0 * eyeSpeed * getPlatform()->getSampleUserInput()->getAnalogInputEventState(CAMERA_GAMEPAD_MOVE_LEFT_RIGHT) * 40.0f * dtime;

#if defined(SMOOTH_CAM)
	PxVec3 eye_t = eye.getPosition();
	eye_t += (m_targetEyePos - eye_t) * g_smoothCamPosLerp;
	eye.setPosition(eye_t);
#endif

	// rotate from gamepad
	const PxF32 rotationSpeed = 200.0f * dtime;
	PxF32 dx = getPlatform()->getSampleUserInput()->getAnalogInputEventState(CAMERA_GAMEPAD_ROTATE_LEFT_RIGHT) * rotationSpeed;
	PxF32 dy = getPlatform()->getSampleUserInput()->getAnalogInputEventState(CAMERA_GAMEPAD_ROTATE_UP_DOWN) * rotationSpeed;
	rotateCamera(dx, dy);
		
	m_worldToView.setInverseTransform(eye);

	updateWorldToViewTransform();
}
void							NxApplication::onPointerInputEvent(const InputEvent& ie, physx::PxU32 x, physx::PxU32 y, physx::PxReal dx, physx::PxReal dy, bool val)
{
	switch (ie.m_Id)
	{
	case CAMERA_MOUSE_LOOK:
		{
			if(getPlatform()->getSampleUserInput()->getDigitalInputEventState(CAMERA_MOVE_BUTTON))
			{
				rotateCamera(dx, dy);
			}
		}
		break;
	}
}
bool							NxApplication::onDigitalInputEvent(const InputEvent& , bool val)
{
	return true;
}
void							NxApplication::onAnalogInputEvent(const InputEvent& , float val)
{
}
void							NxApplication::rotateCamera(PxF32 dx, PxF32 dy)
{
	const float eyeCap      = 1.5f;
#if defined(SMOOTH_CAM)
	m_targetEyeRot.x -= dy * g_smoothCamRotSpeed;
	m_targetEyeRot.y += dx * g_smoothCamRotSpeed;
	if(m_targetEyeRot.x >  eyeCap) m_targetEyeRot.x =  eyeCap;
	if(m_targetEyeRot.x < -eyeCap) m_targetEyeRot.x = -eyeCap;

	m_eyeRot= m_eyeRot + (m_targetEyeRot - m_eyeRot) * g_smoothCamRotLerp;
#else
	const float eyeRotSpeed = 0.005f;
	m_eyeRot.x -= dy * eyeRotSpeed;
	m_eyeRot.y += dx * eyeRotSpeed;
	if(m_eyeRot.x >  eyeCap) m_eyeRot.x =  eyeCap;
	if(m_eyeRot.x < -eyeCap) m_eyeRot.x = -eyeCap;
#endif
}
void							NxApplication::fatalError(const char * msg)
{
printf("Fatal Error in NxApplication: %s\n", msg);
close();
exit(1);
}
void							NxApplication::doInput()
{
	m_platform->doInput();
}
physx::PxProfileZone*			NxApplication::getOrCreateProfileZone(PxFoundation& inFoundation) 
{ 	
#ifdef PHYSX_PROFILE_SDK
	if ( mProfileZone == NULL )
		mProfileZone = &physx::PxProfileZone::createProfileZone( &inFoundation, "SampleProfileZone", gProfileNameProvider );
	if ( m_renderer != NULL )
		m_renderer->setProfileZone( mProfileZone );
#endif
	return mProfileZone;
}
physx::PxProfileZone*			NxApplication::getOrCreateProfileZone(physx::PxProfileZoneManager& zoneManager)
{
#ifdef PHYSX_PROFILE_SDK
	if ( mProfileZone == NULL )
		mProfileZone = &zoneManager.createProfileZone( "SampleProfileZone", &gProfileNameProvider );
	if ( m_renderer != NULL )
		m_renderer->setProfileZone( mProfileZone );
#endif
	return mProfileZone;
}
void							NxApplication::releaseProfileZone()
{
#ifdef PHYSX_PROFILE_SDK
	if ( m_renderer != NULL )
		m_renderer->setProfileZone( NULL );
	SAFE_RELEASE(mProfileZone);
#endif
}
physx::PxProfileEventSender*	NxApplication::getEventBuffer() 
{ 
#ifdef PHYSX_PROFILE_SDK
	if ( mProfileZone ) return mProfileZone; 
#endif
	return NULL; 
}



