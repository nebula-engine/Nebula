#include <utilities/Types/Utilities.h>


#include <Platform/Window/Linux/PL_WI_LIN_Window.h>







#include <Platform/Platform/Linux/PL_PL_LIN_Platform.h>

		PL_PL_LIN_Platform::Platform() {
	
}
		PL_PL_LIN_Platform::~Platform() {
	
}
void	PL_PL_LIN_Platform::VInit( Void* v ) {
	PRINTSIG;
	PL_PL_Platform::VInit( v );
	/*
	char* pPath;
	pPath = getenv("DISPLAY");
	if ( !pPath ) {
		assert(0);
		return 0;
	}
	*/
	//printf("%p\n",pPath);
	
	m_xdisplay = XOpenDisplay( NULL );
	
	if ( !m_xdisplay ) {
		throw Except( "Cannot connect to default X server\n" );
		
	}
	
	
	m_screen_num = DefaultScreen( m_xdisplay );

	m_screen_width =	DisplayWidth( m_xdisplay, m_screen_num );
	m_screen_height =	DisplayHeight( m_xdisplay, m_screen_num );
	m_root_xwindow =	RootWindow( m_xdisplay, m_screen_num );
	m_white_pixel =		WhitePixel( m_xdisplay, m_screen_num );
	m_black_pixel =		BlackPixel( m_xdisplay, m_screen_num );
	
	
	
}
void	PL_PL_LIN_Platform::VShutDown() {
	PRINTSIG;
	
	Platform::Platform::VShutDown();
	
	XCloseDisplay( m_xdisplay );
	
}
void	PL_PL_LIN_Platform::VCreateWindow( PL_WI_Window*& window ) {
	PRINTSIG;
	
	PL_WI_LIN_Window* windowLinux = 0;
	m_window.Create(windowLinux);
	window = windowLinux;

	if ( windowLinux == NULL ) throw Except("WTF!");
	
	if ( !m_xdisplay ) throw Except("xdisplay is null");

	// Xlib stuff
	// Create XWindow with some defualt parameters

	int w = DisplayWidth( m_xdisplay, m_screen_num);
	int h = DisplayHeight( m_xdisplay, m_screen_num);
	

	::Window xwindow = XCreateSimpleWindow(
		m_xdisplay,
		m_root_xwindow,
		0,
		0,
		w/2,
		h/2,
		1,
		m_black_pixel,
		m_white_pixel);
	
	// Pass values to Window
	windowLinux->m_xdisplay     = m_xdisplay;
	windowLinux->m_root_xwindow = m_root_xwindow;
	windowLinux->m_xwindow      = xwindow;
	windowLinux->m_screen_num   = m_screen_num;
	
	// initialize Window
	AR_Init i;
	i.app =			m_app;
	i.platform =	this;

	windowLinux->VInit( &i );
	
}
void	PL_PL_LIN_Platform::VUpdate() {
	//PRINTSIG;
	PL_PL_Platform::VUpdate();
}











