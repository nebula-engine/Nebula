#include <Windows.h>
#include <WinUser.h>

#define IDS_APP_TITLE 103
#define IDI_WIN32PROJECT1 107
#define IDI_SMALL 108
#define IDC_WIN32PROJECT1 109


#include <Platform/WindowWin.h>
#include <Platform/Renderer/PL_RE_Renderer.h>
#include <utilities/Types/Utilities.h>


					Platform::WindowWin::WindowWin() {
}
					Platform::WindowWin::~WindowWin() {
}
void				Platform::WindowWin::VInit( Void* data ) {
	PRINTSIG;

	char szTitle[] = "RCS Client";
    char szWindowClass[] = "Windows App";
    
    // Initialize global strings
	LoadStringA(m_hInst, IDS_APP_TITLE,		szTitle, 64);
	LoadStringA(m_hInst, IDC_WIN32PROJECT1,	szWindowClass, 64);
    
	WNDCLASSEX wcex;

	wcex.cbSize			= sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= m_hInst;
	wcex.hIcon			= LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_WIN32PROJECT1));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= NULL;
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	RegisterClassEx(&wcex);
    
	// Perform application initialization

	DWORD   dwExStyle;
	DWORD   dwStyle;
    
	RECT    windowRect;
    
	// Screen/display attributes
	int width;
	int height;
    
	int bits = 32;
    
	windowRect.left =   (long)0;
	windowRect.top =    (long)0;
    
	bool fullScreen = false;

    if (fullScreen)
    {
        width = 1280;
        height = 800;
        windowRect.right =  (long)width;
        windowRect.bottom = (long)height;
        
        DEVMODE dmScreenSettings;
        memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
        dmScreenSettings.dmSize = sizeof(dmScreenSettings);
        dmScreenSettings.dmPelsWidth = width;   //screen width
        dmScreenSettings.dmPelsHeight = height; //screen height
        dmScreenSettings.dmBitsPerPel = bits;   //bits per pixel
        dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

        if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN != DISP_CHANGE_SUCCESSFUL))
        {
            // Setting display mode failed, switch to windowed
            MessageBox(NULL, TEXT("Display mode failed"), NULL, MB_OK);
            fullScreen = false;
        }
    }
    // Check if fullscreen is still on
    if (fullScreen)
    {
		//window extended style
		dwExStyle = WS_EX_APPWINDOW;
		//windows style
		dwStyle = WS_POPUP;
    }
    else
    {
        width = 800;
        height = 600;
        windowRect.right =  (long)width;
        windowRect.bottom = (long)height;
        
        dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE; //window extended style
        dwStyle = WS_OVERLAPPEDWINDOW;                                  //windows style
    }
    //ShowCursor(FALSE);
    AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);

	int center_x = width/2;
    int center_y = height/2;

	

	HWND hWnd = CreateWindow( szWindowClass, szTitle, dwStyle | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top,
		NULL, NULL, m_hInst, NULL );

	if (!hWnd) 

	// Adds a pointer to your current class to the WndClassEx structure
	SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)this);

	ShowWindow(hWnd, m_nCmdShow);
	UpdateWindow(hWnd);

	center_x = width/2;
	center_y = height/2;
    
    SetCursorPos(center_x,center_y);

	
}
LRESULT				Platform::WindowWin::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	static HGLRC hrc;
	int width, height;
	//short xPos, yPos;

	//int (*WndProcFunc)( UINT, WPARAM, LPARAM ) = NULL;


	// handle message
	switch (message)
	{
	case WM_SIZE:
		height = HIWORD(lParam);
        width = LOWORD(lParam);
        if (height == 0) height = 1;

		m_renderer->VResize( height, width );

        
        break;
	case WM_CREATE:
		m_hdc = GetDC(hWnd);
        setupPixelFormat(m_hdc);
        hrc = wglCreateContext(m_hdc);
        wglMakeCurrent(m_hdc,hrc);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_MOUSEMOVE:
        if ( m_hasFocus )
		{
			//WndProcFunc( message, wParam, lParam );
		}
        break;
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_RBUTTONDOWN:
    case WM_RBUTTONUP:
    case WM_KEYDOWN:
    case WM_KEYUP:
		//WndProcFunc( message, wParam, lParam );
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
int					Platform::WindowWin::setupPixelFormat(HDC hDC)
{
    // Pixel format index
    int nPixelFormat;
    static PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),          //size of structure
        1,                                      //default version
        PFD_DRAW_TO_WINDOW |                    //window drawing support
        PFD_SUPPORT_OPENGL |                    //opengl support
        PFD_DOUBLEBUFFER,                       //double buffering support
        PFD_TYPE_RGBA,                          //RGBA color mode
        32,                                     //32 bit color mode
        0, 0, 0, 0, 0, 0,                       //ignore color bits
        0,                                      //no alpha buffer
        0,                                      //ignore shift bit
        0,                                      //no accumulation buffer
        0, 0, 0, 0,                             //ignore accumulation bits
        16,                                     //16 bit z-buffer size
        0,                                      //no stencil buffer
        0,                                      //no aux buffer
        PFD_MAIN_PLANE,                         //main drawing plane
        0,                                      //reserved
        0, 0, 0 };                              //layer masks ignored

        // Choose best matching format
        nPixelFormat = ChoosePixelFormat(hDC, &pfd);

        // Set the pixel format to the device context
        SetPixelFormat(hDC, nPixelFormat, &pfd);
        
        return 0;
};


LRESULT CALLBACK	WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	// Recover the pointer to our class, don't forget to type cast it back

    Platform::WindowWin* windowWin = (Platform::WindowWin*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
    
	// Check if the pointer is NULL and call the Default WndProc
    if (windowWin == NULL) {
        return DefWindowProc(hWnd, message, wParam, lParam);
    } else {
        // Call the Message Handler for my class (MsgProc in my case)
        return windowWin->MsgProc(hWnd, message, wParam, lParam); 
    }
}











/**
void NbWindow::onResize(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	height = HIWORD(lParam);
    width = LOWORD(lParam);
    if (height == 0)
    {
        height = 1;
    }
    // Reset the viewport to new dimensions
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    //reset projection matrix
    glLoadIdentity(); 
    // Time to calculate aspect ratio of our window
    gluPerspective(54.0, (GLdouble)width/(GLdouble)height, 1.0, 1000.0);
    //set modelview matrix
    glMatrixMode(GL_MODELVIEW); 
    //reset modelview matrix
    glLoadIdentity(); 
}
void NbWindow::onCreate(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	hdc = GetDC(hWnd);
    setupPixelFormat(hdc);
    hrc = wglCreateContext(hdc);
    wglMakeCurrent(hdc,hrc);
}

void NbWindow::onDestroy(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PostQuitMessage(0);
}


LRESULT CALLBACK NbInput::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (!app)
        fatalError();
    if (!app->interfaceController)
        fatalError();
    if (!app->playerController)
        fatalError();
    if (!app->window)
        fatalError();
    
    
    static HGLRC hrc;
	int width, height;
	short xPos, yPos;

	switch (message)
	{
	case WM_SIZE:
		app->window->onResize( hWnd, message, wParam, lParam );
        break;
	case WM_CREATE:
		app->window->onCreate( hWnd, message, wParam, lParam );
		break;
	case WM_DESTROY:
		app->window->onDestroy( hWnd, message, wParam, lParam );
		break;
	case WM_MOUSEMOVE:
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_RBUTTONDOWN:
    case WM_RBUTTONUP:
    case WM_KEYDOWN:
    case WM_KEYUP:
        if (app->interfaceController->interface)
        {
            if (app->interfaceController->interface->WndProc(hWnd, message, wParam, lParam))
            {
                break;
            }
        }
        if (app->playerController->scene)
        {
            if (app->playerController->scene->WndProc(hWnd, message, wParam, lParam))
            {
                break;
            }
        }
        break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}




void onLButtonDown( UINT message, WPARAM wParam, LPARAM lParam)
{
    
}

void onLButtonUp( UINT message, WPARAM wParam, LPARAM lParam)
{
    
}

void onRButtonDown( UINT message, WPARAM wParam, LPARAM lParam)
{
    
}

void onRButtonUp( UINT message, WPARAM wParam, LPARAM lParam)
{
    
}

void onKeyDown( UINT message, WPARAM wParam, LPARAM lParam)
{
    
}

void onKeyUp( UINT message, WPARAM wParam, LPARAM lParam)
{
    
}


case WM_MOUSEMOVE:
        onMouseMove( message, wParam, lParam );
        break;
    case WM_LBUTTONDOWN:
    	onLButtonDown( message, wParam, lParam );
		break;
    case WM_LBUTTONUP:
		onLButtonUp( message, wParam, lParam );
		break;
    case WM_RBUTTONDOWN:
		onRButtonDown( message, wParam, lParam );
		break;
    case WM_RBUTTONUP:
		onRButtonUp( message, wParam, lParam );
		break;
    case WM_KEYDOWN:
		onKeyDown( message, wParam, lParam );
		break;
    case WM_KEYUP:
    */
