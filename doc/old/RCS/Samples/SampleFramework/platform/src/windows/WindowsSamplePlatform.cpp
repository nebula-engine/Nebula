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
#include <RendererMemoryMacros.h>
#include <windows/WindowsSamplePlatform.h>

#if defined(RENDERER_ENABLE_CG)
#include <cg/cg.h>
#endif

#include <direct.h>
#include <stdio.h>

#include <PsString.h>
#include <PsFile.h>

#if defined(RENDERER_ENABLE_DIRECT3D9)
	#include <d3d9.h>
	#include <d3dx9.h>
	#include <XInput.h>
#endif

#if defined(RENDERER_ENABLE_OPENGL)
	#define GLEW_STATIC
	#include <GL/glew.h>
	#include <GL/wglew.h>

	#pragma comment(lib, "OpenGL32.lib")
	#pragma comment(lib, "GLU32.lib")
#endif

using namespace SampleFramework;
using SampleRenderer::RendererWindow;
using namespace physx;

static void setDCPixelFormat(HDC &dc)
{
	const PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		8, 0, 8, 0, 8, 0,
		8,
		0,
		0,
		0, 0, 0, 0,
		24,
		8,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};
	int pfindex = ChoosePixelFormat(dc, &pfd);
	SetPixelFormat(dc, pfindex, &pfd);
}

static const char *g_windowClassName = "RendererWindow";
static const DWORD g_windowStyle     = WS_OVERLAPPEDWINDOW;
static const DWORD g_fullscreenStyle = WS_POPUP;

static void handleMouseEvent(UINT msg, LPARAM lParam, HWND hwnd, RendererWindow* window)
{
	if (!window || !window->getPlatform())
		return;

	RECT rect;
	GetClientRect(hwnd, &rect);
	PxU32 height = (PxU32)(rect.bottom-rect.top);
	PxU32 x = (PxU32)LOWORD(lParam);
	PxU32 y = height-(PxU32)HIWORD(lParam);
	PxVec2 current(static_cast<PxReal>(x), static_cast<PxReal>(y));

	WindowsPlatform& platform = *((WindowsPlatform*)window->getPlatform());
	PxVec2 diff = current - platform.getMouseCursorPos();
	platform.setMouseCursorPos(current);

	switch (msg)
	{
	case WM_MOUSEMOVE:
		if (!SamplePlatform::platform()->getMouseCursorRecentering())
		{
			platform.getWindowsSampleUserInput().doOnMouseMove(x, y, diff.x, diff.y, MOUSE_MOVE);
		}
		break;
	case WM_LBUTTONDOWN:
		SetCapture(hwnd);
		platform.getWindowsSampleUserInput().doOnMouseButton(x, y, WindowsSampleUserInput::LEFT_MOUSE_BUTTON, true);
		break;
	case WM_LBUTTONUP:
		ReleaseCapture();
		platform.getWindowsSampleUserInput().doOnMouseButton(x, y, WindowsSampleUserInput::LEFT_MOUSE_BUTTON, false);
		break;
	case WM_RBUTTONDOWN:
		SetCapture(hwnd);
		platform.getWindowsSampleUserInput().doOnMouseButton(x, y, WindowsSampleUserInput::RIGHT_MOUSE_BUTTON, true);
		break;
	case WM_RBUTTONUP:
		ReleaseCapture();
		platform.getWindowsSampleUserInput().doOnMouseButton(x, y, WindowsSampleUserInput::RIGHT_MOUSE_BUTTON, false);
		break;
	case WM_MBUTTONDOWN:
		SetCapture(hwnd);
		platform.getWindowsSampleUserInput().doOnMouseButton(x, y, WindowsSampleUserInput::CENTER_MOUSE_BUTTON, true);
		break;
	case WM_MBUTTONUP:
		ReleaseCapture();
		platform.getWindowsSampleUserInput().doOnMouseButton(x, y, WindowsSampleUserInput::CENTER_MOUSE_BUTTON, false);
		break;
	}
}

static INT_PTR CALLBACK windowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
#if defined(RENDERER_64BIT)
	RendererWindow* window = (RendererWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
#else
	RendererWindow* window = (RendererWindow*)LongToPtr(GetWindowLongPtr(hwnd, GWLP_USERDATA));
#endif

	bool customHandle = false;

	if(!customHandle)
	{
		switch(msg)
		{
		case WM_SETFOCUS:
			if(window)
				window->setFocus(true);
			break;

		case WM_KILLFOCUS:
			if(window)
				window->setFocus(false);
			break;

		case WM_EXITSIZEMOVE:
			if (window)
			{
				((WindowsPlatform*)window->getPlatform())->recenterMouseCursor(false);
			}
			break;

		case WM_CREATE:
			::UpdateWindow(hwnd);
			break;

		case WM_CLOSE:
			if(window)
			{
				window->close();
			}
			break;

		case WM_SIZE:
			if(window)
			{
				RECT rect;
				GetClientRect(hwnd, &rect);
				PxU32 width  = (PxU32)(rect.right-rect.left);
				PxU32 height = (PxU32)(rect.bottom-rect.top);
				window->onResize(width, height);
			}
			break;

		case WM_MOUSEMOVE:
			handleMouseEvent(WM_MOUSEMOVE, lParam, hwnd, window);
			break;

		case WM_LBUTTONDOWN:
			((WindowsPlatform*)window->getPlatform())->recenterMouseCursor(false);
			handleMouseEvent(WM_LBUTTONDOWN, lParam, hwnd, window);
			break;

		case WM_LBUTTONUP:
			handleMouseEvent(WM_LBUTTONUP, lParam, hwnd, window);
			break;

		case WM_RBUTTONDOWN:
			handleMouseEvent(WM_RBUTTONDOWN, lParam, hwnd, window);
			break;

		case WM_RBUTTONUP:
			handleMouseEvent(WM_RBUTTONUP, lParam, hwnd, window);
			break;

		case WM_MBUTTONDOWN:
			handleMouseEvent(WM_MBUTTONDOWN, lParam, hwnd, window);
			break;

		case WM_MBUTTONUP:
			handleMouseEvent(WM_MBUTTONUP, lParam, hwnd, window);
			break;

		case WM_CHAR:
			// PT: we need to catch this message to make a difference between lower & upper case characters
			if(window)
			{
				((WindowsPlatform*)window->getPlatform())->getWindowsSampleUserInput().onKeyDownEx(wParam);
			}
			break;

		case WM_SYSKEYDOWN:	// For F10 or ALT
			if (VK_F4 == wParam && (KF_ALTDOWN & HIWORD(lParam)))
			{
				if(window)
				{
					window->close();
					break;
				}
			}
			// no break, fall through
		case WM_KEYDOWN:
			if(window)
			{
				((WindowsPlatform*)window->getPlatform())->getWindowsSampleUserInput().onKeyDown(wParam, lParam);				
			}
			break;

		case WM_SYSKEYUP:
		case WM_KEYUP:
			if(window)
			{
				((WindowsPlatform*)window->getPlatform())->getWindowsSampleUserInput().onKeyUp(wParam, lParam);
			}
			break;

		case WM_PAINT:
			ValidateRect(hwnd, 0);
			break;
		default:
			return ::DefWindowProc(hwnd, msg, wParam, lParam);
		}
	}
	return 0; 
}

static ATOM registerWindowClass(HINSTANCE hInstance)
{
	static ATOM atom = 0;
	if(!atom)
	{
		WNDCLASSEX wcex;
		wcex.cbSize         = sizeof(WNDCLASSEX); 
		wcex.style          = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc    = (WNDPROC)windowProc;
		wcex.cbClsExtra     = 0;
		wcex.cbWndExtra     = sizeof(void*);
		wcex.hInstance      = hInstance;
		wcex.hIcon          = ::LoadIcon(hInstance, (LPCTSTR)0);
		wcex.hCursor        = ::LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
		wcex.lpszMenuName   = 0;
		wcex.lpszClassName  = g_windowClassName;
		wcex.hIconSm        = ::LoadIcon(wcex.hInstance, (LPCTSTR)0);
		atom = ::RegisterClassEx(&wcex);
	}
	return atom;
}

SamplePlatform*		SampleFramework::createPlatform(SampleRenderer::RendererWindow* _app)
{
	printf("Creating Windows platform abstraction.\n");
	SamplePlatform::setPlatform(new WindowsPlatform(_app));
	return SamplePlatform::platform();
}

void* WindowsPlatform::initializeD3D9()
{
	m_library   = 0;
	if(m_hwnd)
	{
#if defined(D3D_DEBUG_INFO)
#define D3D9_DLL "d3d9d.dll"
#else
#define D3D9_DLL "d3d9.dll"
#endif
		m_library = LoadLibraryA(D3D9_DLL);
		RENDERER_ASSERT(m_library, "Could not load " D3D9_DLL ".");
		if(!m_library)
		{
			MessageBoxA(0, "Could not load " D3D9_DLL ". Please install the latest DirectX End User Runtime available at www.microsoft.com/directx.", "Renderer Error.", MB_OK);
		}
#undef D3D9_DLL
		if(m_library)
		{
			typedef IDirect3D9* (WINAPI* LPDIRECT3DCREATE9)(UINT SDKVersion);
			LPDIRECT3DCREATE9 pDirect3DCreate9 = (LPDIRECT3DCREATE9)GetProcAddress(m_library, "Direct3DCreate9");
			RENDERER_ASSERT(pDirect3DCreate9, "Could not find Direct3DCreate9 function.");
			if(pDirect3DCreate9)
			{
				m_d3d = pDirect3DCreate9(D3D_SDK_VERSION);
			}
		}
	}
	return m_d3d;
}

void WindowsPlatform::showCursor(bool show)
{
	if(show != m_showCursor)
	{
		m_showCursor = show;
		PxI32 count = ShowCursor(show);
		PX_ASSERT((m_showCursor && (count == 0)) || (!m_showCursor && (count == -1)));
	}
}

void* WindowsPlatform::compileProgram(void * context, 
										const char* assetDir, 
										const char *programPath, 
										physx::PxU64 profile, 
										const char* passString, 
										const char *entry, 
										const char **args)

{
#if defined(RENDERER_ENABLE_CG)
	char fullpath[1024];
	physx::string::strcpy_s(fullpath, 1024, assetDir);
	physx::string::strcat_s(fullpath, 1024, "shaders/");
	physx::string::strcat_s(fullpath, 1024, programPath);
	CGprogram program = cgCreateProgramFromFile(static_cast<CGcontext>(context), CG_SOURCE, fullpath, static_cast<CGprofile>(profile), entry, args);

	return program;
#else
	return NULL;
#endif
}

WindowsPlatform::WindowsPlatform(SampleRenderer::RendererWindow* _app) : SamplePlatform(_app)
{
	m_isHandlingMessages = false;
	m_destroyWindow = false;
	m_hasFocus = true;
	m_hwnd = 0;
	m_library = 0;

	// adjust ShowCursor display counter to be 0 or -1
	m_showCursor = true;
	PxI32 count = ShowCursor(true);
	while(count != 0)
		count = ShowCursor(count < 0);
	strcpy(m_platformName, "windows");

	m_mouseCursorPos = PxVec2(0);
	m_recenterMouseCursor = false;
}

WindowsPlatform::~WindowsPlatform()
{
	RENDERER_ASSERT(m_hwnd==0, "RendererWindow was not closed before being destroyed.");
	if(m_library) 
	{
		FreeLibrary(m_library);
		m_library = 0;
	}
}

bool WindowsPlatform::isD3D9ok()
{
	if(m_library) 
	{
		return true;
	}
	return false;
}

bool WindowsPlatform::hasFocus() const
{
	return m_hasFocus;
}

void WindowsPlatform::setFocus(bool b)
{
	m_hasFocus = b;
}

bool WindowsPlatform::isOpen()
{
	if(m_hwnd) return true;
	return false;
}

void WindowsPlatform::getTitle(char *title, physx::PxU32 maxLength) const
{
	RENDERER_ASSERT(m_hwnd, "Tried to get the title of a window that was not opened.");
	if(m_hwnd)
	{
		GetWindowTextA(m_hwnd, title, maxLength);
	}
}

void WindowsPlatform::setTitle(const char *title)
{
	RENDERER_ASSERT(m_hwnd, "Tried to set the title of a window that was not opened.");
	if(m_hwnd)
	{
		::SetWindowTextA(m_hwnd, title);
	}
}

void WindowsPlatform::showMessage(const char* title, const char* message)
{
	printf("%s: %s\n", title, message);
}

void WindowsPlatform::setMouseCursorRecentering(bool val)
{
	if (m_recenterMouseCursor != val)
	{
		m_recenterMouseCursor = val;
		if (m_recenterMouseCursor)
			recenterMouseCursor(false);
	}
}

bool WindowsPlatform::getMouseCursorRecentering() const
{
	return m_recenterMouseCursor;
}

void WindowsPlatform::recenterMouseCursor(bool generateEvent)
{
	if (m_recenterMouseCursor && m_app->hasFocus())
	{
		RECT rect;
		GetWindowRect(m_hwnd, (LPRECT)&rect);
		PxU32 winHeight = (PxU32)(rect.bottom-rect.top);
		PxU32 winWidth = (PxU32)(rect.right - rect.left);

		POINT winPos;
		GetCursorPos(&winPos);
		PxVec2 current(static_cast<PxReal>(winPos.x), winHeight - static_cast<PxReal>(winPos.y));

		PxI32 winCenterX = 0;
		PxI32 winCenterY = 0;
		{
			winCenterX = rect.left + PxI32(winWidth>>1);
			winCenterY = rect.top + PxI32(winHeight>>1);
		}
		SetCursorPos(winCenterX, winCenterY);

		if (generateEvent)
		{
			PxVec2 diff = current - PxVec2(static_cast<PxReal>(winCenterX), winHeight - static_cast<PxReal>(winCenterY));
			getWindowsSampleUserInput().doOnMouseMove(winCenterX, winHeight - winCenterY, diff.x, diff.y, MOUSE_MOVE);
		}
	
		m_mouseCursorPos = current;
	}
}

void WindowsPlatform::setWindowSize(physx::PxU32 width, 
									physx::PxU32 height)
{
	bool fullscreen = false;
	RENDERER_ASSERT(m_hwnd, "Tried to resize a window that was not opened.");
	if(m_hwnd)
	{
		RECT rect;
		::GetWindowRect(m_hwnd, &rect);
		rect.right    = (LONG)(rect.left + width);
		rect.bottom   = (LONG)(rect.top  + height);
		RECT oldrect  = rect;
		DWORD dwstyle = (fullscreen ? g_fullscreenStyle : g_windowStyle);
		::AdjustWindowRect(&rect, dwstyle, 0);
		::MoveWindow(m_hwnd, (int)oldrect.left, (int)oldrect.top, (int)(rect.right-rect.left), (int)(rect.bottom-rect.top), 1);
	}
}

void WindowsPlatform::update()
{
	RENDERER_ASSERT(m_hwnd, "Tried to update a window that was not opened.");
	if(m_app->isOpen())
	{
		m_isHandlingMessages = true;
		MSG	msg;

		while(m_app->isOpen() && ::PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		m_isHandlingMessages = false;
		if(m_hwnd && m_destroyWindow)
		{
			if(m_app->onClose())
			{
				::DestroyWindow(m_hwnd);
				m_hwnd = 0;
			}
			m_destroyWindow = false;
		}
		recenterMouseCursor(true);
	}
}

bool WindowsPlatform::openWindow(physx::PxU32& width, 
								physx::PxU32& height,
								const char* title,
								bool fullscreen) 
{
	bool ok = false;
	RENDERER_ASSERT(m_hwnd==0, "Attempting to open a window that is already opened");
	if(m_hwnd==0)
	{
		registerWindowClass((HINSTANCE)::GetModuleHandle(0));
		RECT winRect;
		winRect.left   = 0;
		winRect.top    = 0;
		winRect.right  = width;
		winRect.bottom = height;
		DWORD dwstyle  = (fullscreen ? g_fullscreenStyle : g_windowStyle);
		UINT  offset   = fullscreen ? 0 : 50;
		::AdjustWindowRect(&winRect, dwstyle, 0);
		m_hwnd = ::CreateWindowA(g_windowClassName, title, dwstyle,
			offset, offset,
			winRect.right-winRect.left, winRect.bottom-winRect.top,
			0, 0, 0, 0);
		RENDERER_ASSERT(m_hwnd, "CreateWindow failed");
		if(m_hwnd)
		{
			ok = true;
			ShowWindow(m_hwnd, SW_SHOWNORMAL);
			SetFocus(m_hwnd);              
			SetWindowLongPtr(m_hwnd, GWLP_USERDATA, PtrToLong(m_app));
			m_app->onOpen();
		}
	}

	{
		RAWINPUTDEVICE rawInputDevice;
		rawInputDevice.usUsagePage	= 1;
		rawInputDevice.usUsage		= 6;
		rawInputDevice.dwFlags		= 0;
		rawInputDevice.hwndTarget	= NULL;

		BOOL status = RegisterRawInputDevices(&rawInputDevice, 1, sizeof(rawInputDevice));
		if(status!=TRUE)
		{
			DWORD err = GetLastError();
			printf("%d\n", err);
		}
	}

	return ok;
}

bool WindowsPlatform::closeWindow() 
{
	if(m_hwnd)
	{
		if(m_isHandlingMessages)
		{
			m_destroyWindow = true;
		}
		else if(m_app->onClose())
		{
			::DestroyWindow(m_hwnd);
			m_hwnd = 0;
		}
	}

	return true;
}

size_t WindowsPlatform::getCWD(char* path, size_t len)
{
	return ::GetCurrentDirectory((DWORD)len, path);
}
void WindowsPlatform::setCWDToEXE(void) 
{
	char exepath[1024] = {0};
	GetModuleFileNameA(0, exepath, sizeof(exepath));

	if(exepath[0])
	{
		popPathSpec(exepath);
		_chdir(exepath);
	}
}

void WindowsPlatform::setupRendererDescription(SampleRenderer::RendererDesc& renDesc) 
{
	renDesc.driver = SampleRenderer::Renderer::DRIVER_DIRECT3D9;
	renDesc.windowHandle = reinterpret_cast<physx::PxU64>(m_hwnd);
}

void WindowsPlatform::postRendererSetup(SampleRenderer::Renderer* renderer) 
{
	if(!renderer)
	{
		// quit if no renderer was created.  Nothing else to do.
		// error was output in createRenderer.
		exit(1);
	}
	char windowTitle[1024] = {0};
	m_app->getTitle(windowTitle, 1024);
	strcat_s(windowTitle, 1024, " : ");
	strcat_s(windowTitle, 1024, SampleRenderer::Renderer::getDriverTypeName(
												renderer->getDriverType()));
	m_app->setTitle(windowTitle);
}

void WindowsPlatform::doInput()
{
	m_windowsSampleUserInput.updateInput();
}

void WindowsPlatform::initializeOGLDisplay(const SampleRenderer::RendererDesc& desc,
										physx::PxU32& width, 
										physx::PxU32& height)
{
#if defined(RENDERER_ENABLE_OPENGL)
	m_hwnd = reinterpret_cast<HWND>(desc.windowHandle);

	RENDERER_ASSERT(m_hwnd, "Invalid window handle!");
	// Get the device context.
	m_hdc = GetDC(m_hwnd);

	RENDERER_ASSERT(m_hdc, "Invalid device context!");
	if(m_hdc)
	{
		setDCPixelFormat(m_hdc);
		m_hrc = wglCreateContext(m_hdc);
	}

	RENDERER_ASSERT(m_hrc, "Invalid render context!");
	if(m_hrc)
	{
		BOOL makeCurrentRet = wglMakeCurrent(m_hdc, m_hrc);
		RENDERER_ASSERT(m_hrc, "Unable to set current context!");
		if(!makeCurrentRet)
		{
			wglDeleteContext(m_hrc);
			m_hrc = 0;
		}
	}
#endif
}

physx::PxU64 WindowsPlatform::getWindowHandle()
{
	return reinterpret_cast<physx::PxU64>(m_hwnd);
}

void WindowsPlatform::getWindowSize(PxU32& width, PxU32& height)
{
	if(m_hwnd)
	{
		RECT rect;
		GetClientRect(m_hwnd, &rect);
		width  = (PxU32)(rect.right  - rect.left);
		height = (PxU32)(rect.bottom - rect.top);
	}
}

void WindowsPlatform::freeDisplay() 
{
#if defined(RENDERER_ENABLE_OPENGL)
	if(m_hrc)
	{
		wglMakeCurrent(m_hdc, 0);
		wglDeleteContext(m_hrc);
		m_hrc = 0;
	}
#endif
}

bool WindowsPlatform::makeContextCurrent()
{
	bool ok = false;

#if defined(RENDERER_ENABLE_OPENGL)
	if(m_hdc && m_hrc)
	{
		if(wglGetCurrentContext()==m_hrc)
		{
			ok = true;
		}
		else
		{
			bool ok = wglMakeCurrent(m_hdc, m_hrc) ? true : false;
			return ok;
		}
	}
#endif

	return ok;
}

void WindowsPlatform::swapBuffers()
{
	SwapBuffers(m_hdc);
}

bool WindowsPlatform::isContextValid()
{
	if(!m_hdc) return false;
	if(!m_hrc) return false;
	return true;
}

void WindowsPlatform::postInitializeOGLDisplay()
{
#if defined(RENDERER_ENABLE_OPENGL)
	glewInit();
		// turn off v-sync...
#if defined(GLEW_MX)
	wglewInit();
#endif
	if(WGLEW_EXT_swap_control)
	{
		wglSwapIntervalEXT(0);
	}
#endif
}

physx::PxU32 WindowsPlatform::initializeD3D9Display(void * d3dPresentParameters, 
																char* m_deviceName, 
																physx::PxU32& width, 
																physx::PxU32& height,
																void * m_d3dDevice_out)
{
	D3DPRESENT_PARAMETERS* m_d3dPresentParams = static_cast<D3DPRESENT_PARAMETERS*>(d3dPresentParameters);

	UINT       adapter    = D3DADAPTER_DEFAULT;
	D3DDEVTYPE deviceType = D3DDEVTYPE_HAL;

	// check to see if fullscreen is requested...
	bool fullscreen = false;
	WINDOWINFO wininfo = {0};
	if(GetWindowInfo(m_hwnd, &wininfo))
	{
		if(wininfo.dwStyle & WS_POPUP)
		{
			fullscreen = true;
		}
	}

	// search for supported adapter mode.
	if(fullscreen)
	{
		RECT rect = {0};
		GetWindowRect(m_hwnd, &rect);
		m_d3dPresentParams->BackBufferFormat = D3DFMT_X8R8G8B8;
		m_d3dPresentParams->BackBufferWidth  = rect.right-rect.left;
		m_d3dPresentParams->BackBufferHeight = rect.bottom-rect.top;

		bool foundAdapterMode = false;
		const UINT numAdapterModes = m_d3d->GetAdapterModeCount(0, m_d3dPresentParams->BackBufferFormat);
		for(UINT i=0; i<numAdapterModes; i++)
		{
			D3DDISPLAYMODE mode = {0};
			m_d3d->EnumAdapterModes(0, m_d3dPresentParams->BackBufferFormat, i, &mode);
			if(mode.Width       == m_d3dPresentParams->BackBufferWidth  &&
				mode.Height      == m_d3dPresentParams->BackBufferHeight &&
				mode.RefreshRate >  m_d3dPresentParams->FullScreen_RefreshRateInHz)
			{
				m_d3dPresentParams->FullScreen_RefreshRateInHz = mode.RefreshRate;
				foundAdapterMode = true;
			}
		}
		RENDERER_ASSERT(foundAdapterMode, "Unable to find supported fullscreen Adapter Mode.");
		if(!foundAdapterMode) fullscreen = false;
	}

	// enable fullscreen mode.
	if(fullscreen)
	{
		m_d3dPresentParams->Windowed = 0;
	}

#if defined(RENDERER_ENABLE_NVPERFHUD)
	// NvPerfHud Support.
	UINT numAdapters = m_d3d->GetAdapterCount();
	for(UINT i=0; i<numAdapters; i++)
	{
		D3DADAPTER_IDENTIFIER9 identifier;
		m_d3d->GetAdapterIdentifier(i, 0, &identifier);
		if(strstr(identifier.Description, "PerfHUD"))
		{
			adapter    = i;
			deviceType = D3DDEVTYPE_REF;
			break;
		}
	}
#endif

	D3DADAPTER_IDENTIFIER9 adapterIdentifier;
	m_d3d->GetAdapterIdentifier(adapter, 0, &adapterIdentifier);
	strncpy_s(m_deviceName, 256, adapterIdentifier.Description, 256);

	HRESULT res = m_d3d->CreateDevice( adapter, deviceType,
		m_hwnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		m_d3dPresentParams, &m_d3dDevice);
	*(static_cast<IDirect3DDevice9**>(m_d3dDevice_out)) = m_d3dDevice;
	return res;
}

physx::PxU32 WindowsPlatform::D3D9Present()
{
	return m_d3dDevice->Present(0, 0, m_hwnd, 0);
}


physx::PxU64 WindowsPlatform::getD3D9TextureFormat(SampleRenderer::RendererTexture2D::Format format)
{
	D3DFORMAT d3dFormat = D3DFMT_UNKNOWN;
	switch(format)
	{
	case SampleRenderer::RendererTexture2D::FORMAT_B8G8R8A8: d3dFormat = D3DFMT_A8R8G8B8; break;
	case SampleRenderer::RendererTexture2D::FORMAT_A8:       d3dFormat = D3DFMT_A8;       break;
	case SampleRenderer::RendererTexture2D::FORMAT_R32F:     d3dFormat = D3DFMT_R32F;     break;
	case SampleRenderer::RendererTexture2D::FORMAT_DXT1:     d3dFormat = D3DFMT_DXT1;     break;
	case SampleRenderer::RendererTexture2D::FORMAT_DXT3:     d3dFormat = D3DFMT_DXT3;     break;
	case SampleRenderer::RendererTexture2D::FORMAT_DXT5:     d3dFormat = D3DFMT_DXT5;     break;
	case SampleRenderer::RendererTexture2D::FORMAT_D16:      d3dFormat = D3DFMT_D16;      break;
	case SampleRenderer::RendererTexture2D::FORMAT_D24S8:    d3dFormat = D3DFMT_D24S8;    break;
	}
	return static_cast<physx::PxU64>(d3dFormat);
}

bool WindowsPlatform::makeSureDirectoryPathExists(const char* dirPath)
{
	// [Kai] Currently create the final folder only if the dirPath doesn't exist.
	// To create all the directories in the specified dirPath, use API
	// MakeSureDirectoryPathExists() declared in dbghelp.h
	bool ok = GetFileAttributes(dirPath) != -1;
	if (!ok)
		ok = CreateDirectory(dirPath, NULL) != 0;
	return ok;
}
