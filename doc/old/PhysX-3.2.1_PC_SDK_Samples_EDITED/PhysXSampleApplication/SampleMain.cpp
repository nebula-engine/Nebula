

#include "foundation/PxAssert.h"
#include "RendererConfig.h"
#include "NxCommandLine.h"
#include "RendererMemoryMacros.h"
#include "SampleAllocator.h"
#include "PhysXSampleApplication.h"

using namespace SampleFramework;

#if defined(RENDERER_ANDROID)
#include "NxPlatform.h"

struct android_app;
static android_app* gState;
#endif

static PhysXSampleApplication* g_app = NULL;
static SampleSetup g_settings;
static NxCommandLine* g_commandLine = NULL;

void mainInitialize()
{
	NX_ASSERT(g_commandLine);
	const NxCommandLine& cmdline = *g_commandLine;

	initNxAllocator();

	g_app = NX_NEW(PhysXSampleApplication)(cmdline);

	g_app->customizeSample(g_settings);

#if defined(RENDERER_ANDROID)
	/* We need to register event handling callbacks and process events, while window is not yet shown. */
	if(!NxPlatform::platform()->preOpenWindow(gState))
	{
		LOG_INFO("SampleMain", "CMD/Input handlers registration failed. Exiting.");
		return;
	}
	while(!NxPlatform::platform()->isOpen()) 
	{ 
		NxPlatform::platform()->update();
	}
#endif

	if (g_app->isOpen())	// inherited from RendererWindow
		g_app->close();		// inherited from RendererWindow

	g_app->open(g_settings.mWidth, g_settings.mHeight, g_settings.mName, g_settings.mFullscreen); // inherited from RendererWindow
}
void mainLoop()
{
	while (mainContinue());
}
void mainTerminate()
{
	DELETESINGLE(g_app);
	DELETESINGLE(g_commandLine);
	releaseSampleAllocator();
}
bool mainContinue()
{
	if (g_app->isOpen() && !g_app->isCloseRequested())
	{
		g_app->doInput(); // inherited from RendererWindow
		g_app->update(); // inherited from RendererWindow
#if defined(RENDERER_ANDROID)
		if (NxPlatform::platform()->isOpen())
			return true;
#else
		return true;
#endif
	}

	if (g_app->isOpen() || g_app->isCloseRequested())
	{
		g_app->close();
	}
		
	return false;
}

#if defined(RENDERER_ANDROID)

	extern "C" void android_main(struct android_app* state)
	{
		gState = state;
		const char* argv[] = { "dummy", 0 };
		g_commandLine = new NxCommandLine(1, argv);
		mainInitialize();
		mainLoop();
		mainTerminate();
		exit(0);
		/* Will not return return code, because NDK's native_app_glue declares this function to return nothing. Too bad. */
	}

#elif defined(RENDERER_IOS)

	#include "IosNxPlatform.h"

	int main(int argc, const char *const* argv)
	{
		g_commandLine = new NxCommandLine((unsigned int)argc, argv);
		SampleFramework::createApplication(mainInitialize, mainContinue, mainTerminate);
		return 0;
	}

#elif defined(RENDERER_WINDOWS)

	int main()
	{
		g_commandLine = new NxCommandLine(GetCommandLineA());
		mainInitialize();
		mainLoop();
		mainTerminate();
		return 0;
	}

#elif defined(RENDERER_XBOX360)

	int main()
	{
		const char* argv[] = {"XboxStuff",0};
		g_commandLine = new NxCommandLine(1, argv);
		mainInitialize();
		mainLoop();
		mainTerminate();
		return 0;
	}
	
#elif defined(RENDERER_PS3)

	int main(int argc, char** argv)
	{
		g_commandLine = new NxCommandLine((unsigned int)argc, argv);
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
			{
				printf("Failed to run %s! If xterm is missing, try running with this parameter: %s\n", argv[0], specialCommand);
			}
		}
		else
		{
		g_commandLine = new NxCommandLine((unsigned int)(argc), argv);
		mainInitialize();
		mainLoop();
		mainTerminate();
		}

		return 0;
	}

#else

	int main(int argc, const char *const* argv)
	{
		g_commandLine = new NxCommandLine((unsigned int)argc, argv);
		mainInitialize();
		mainLoop();
		mainTerminate();
		return 0;
	}

#endif
