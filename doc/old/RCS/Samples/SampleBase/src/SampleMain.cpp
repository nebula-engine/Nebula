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

#include "foundation/PxAssert.h"
#include "RendererConfig.h"
#include "SampleCommandLine.h"
#include "RendererMemoryMacros.h"
#include "SampleAllocator.h"
#include "PhysXSampleApplication.h"

using namespace SampleFramework;

#if defined(RENDERER_ANDROID)
#include "SamplePlatform.h"

struct android_app;
static android_app* gState;
#endif

static PhysXSampleApplication* gApp = NULL;
static SampleSetup gSettings;
static SampleCommandLine* gSampleCommandLine = NULL;

void mainInitialize()
{
	PX_ASSERT(gSampleCommandLine);
	const SampleCommandLine& cmdline = *gSampleCommandLine;
	initSampleAllocator();
	gApp = SAMPLE_NEW(PhysXSampleApplication)(cmdline);
	
	gApp->customizeSample(gSettings);
#if defined(RENDERER_ANDROID)
	/* We need to register event handling callbacks and process events, while window is not yet shown. */
	if(!SamplePlatform::platform()->preOpenWindow(gState))
	{
		LOG_INFO("SampleMain", "CMD/Input handlers registration failed. Exiting.");
		return;
	}
	while(!SamplePlatform::platform()->isOpen()) 
	{ 
		SamplePlatform::platform()->update();
	}
#endif

	if (gApp->isOpen())
		gApp->close();

	gApp->open(gSettings.mWidth, gSettings.mHeight, gSettings.mName, gSettings.mFullscreen);
}

void mainTerminate()
{
	DELETESINGLE(gApp);
	DELETESINGLE(gSampleCommandLine);
	releaseSampleAllocator();
}

bool mainContinue()
{
	if (gApp->isOpen() && !gApp->isCloseRequested())
	{
		gApp->doInput();
		gApp->update();
#if defined(RENDERER_ANDROID)
		if (SamplePlatform::platform()->isOpen())
			return true;
#else
		return true;
#endif
	}

	if (gApp->isOpen() || gApp->isCloseRequested())
	{
		gApp->close();
	}
		
	return false;
}

void mainLoop()
{
	while (mainContinue());
}


#if defined(RENDERER_ANDROID)

	extern "C" void android_main(struct android_app* state)
	{
		gState = state;
		const char* argv[] = { "dummy", 0 };
		gSampleCommandLine = new SampleCommandLine(1, argv);
		mainInitialize();
		mainLoop();
		mainTerminate();
		exit(0);
		/* Will not return return code, because NDK's native_app_glue declares this function to return nothing. Too bad. */
	}

#elif defined(RENDERER_IOS)

	#include "IosSamplePlatform.h"

	int main(int argc, const char *const* argv)
	{
		gSampleCommandLine = new SampleCommandLine((unsigned int)argc, argv);
		SampleFramework::createApplication(mainInitialize, mainContinue, mainTerminate);
		return 0;
	}

#elif defined(RENDERER_WINDOWS)

	int main()
	{
		gSampleCommandLine = new SampleCommandLine(GetCommandLineA());
		mainInitialize();
		mainLoop();
		mainTerminate();
		return 0;
	}

#elif defined(RENDERER_XBOX360)

	int main()
	{
		const char* argv[] = {
			"XboxStuff",
			0
		};
		gSampleCommandLine = new SampleCommandLine(1, argv);
		mainInitialize();
		mainLoop();
		mainTerminate();
		return 0;
	}
	
#elif defined(RENDERER_PS3)

	int main(int argc, char** argv)
	{
		gSampleCommandLine = new SampleCommandLine((unsigned int)argc, argv);
		mainInitialize();
		mainLoop();
		mainTerminate();
		return 0;
	}

#elif defined(RENDERER_LINUX)

	int main(int argc, const char *const* argv)
	{
		char* commandString = NULL;
		PxU32 commandLen = 0;
		const char* specialCommand = "--noXterm";
		const char* xtermCommand = "xterm -e ";
		bool foundSpecial = false;
		
		for(PxU32 i = 0; i < argc; i++)
		{
			foundSpecial = foundSpecial || (::strncmp(argv[i], specialCommand, ::strlen(specialCommand)) == 0);
			commandLen += ::strlen(argv[i]);
		}
		
		// extend command line if not chosen differently
		// and start again with terminal as parent
		if(!foundSpecial)
		{
			// increase size by new commands, spaces between commands and string terminator
			commandLen += ::strlen(xtermCommand) + ::strlen(specialCommand) + argc + 3;
			commandString = (char*)::malloc(commandLen * sizeof(char));
			
			::strcpy(commandString, xtermCommand);
			for(PxU32 i = 0; i < argc; i++)
			{
				::strcat(commandString, argv[i]);
				::strcat(commandString, " ");
			}
			::strcat(commandString, specialCommand);

			int ret = ::system(commandString);
			::free(commandString);
			
			if(ret < 0)
				printf("Failed to run %s! If xterm is missing, try running with this parameter: %s\n", argv[0], specialCommand);
		}
		else
		{
			gSampleCommandLine = new SampleCommandLine((unsigned int)(argc), argv);
			mainInitialize();
			mainLoop();
			mainTerminate();
		}

		return 0;
	}

#else

	int main(int argc, const char *const* argv)
	{
		gSampleCommandLine = new SampleCommandLine((unsigned int)argc, argv);
		mainInitialize();
		mainLoop();
		mainTerminate();
		return 0;
	}

#endif
