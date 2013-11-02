#include <jess/free.hpp>
#include <jess/except.hpp>

#include <nebula/platform/window/lin/base.hpp>
#include <nebula/platform/platform/lin/base.hpp>

n21100::base::base()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
n21100::base::~base()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	n21100::base::init( std::shared_ptr<n10000::app> parent )
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	n21000::base::init( parent );
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
	
	if ( !m_xdisplay )
	{
		throw jess::except( "cannot connect to default X server" );
	}
	
	
	m_screen_num = DefaultScreen( m_xdisplay );

	m_screen_width =	DisplayWidth( m_xdisplay, m_screen_num );
	m_screen_height =	DisplayHeight( m_xdisplay, m_screen_num );
	m_root_xwindow =	RootWindow( m_xdisplay, m_screen_num );
	m_white_pixel =		WhitePixel( m_xdisplay, m_screen_num );
	m_black_pixel =		BlackPixel( m_xdisplay, m_screen_num );
	
	
	
}
void	n21100::base::shutdown()
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	n21000::base::shutdown();
	
	XCloseDisplay( m_xdisplay );
	
}
std::shared_ptr<n22000::base>	n21100::base::create_window()
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	std::shared_ptr<n22100::base> wnd_lin( new n22100::base );
	std::shared_ptr<n22000::base> wnd = wnd_lin;
	
	// don't init here, need to send data first
	/**
	* \todo create init override for window that allows all necessary data to be sent OR have the window grab the data from it's parent
	**/
	windows_.push<n22100::base>( wnd_lin );
	
		
	std::cout << wnd.get();
	
	jess::assertion( m_xdisplay );// throw Except("xdisplay is null");
	
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
	/** \todo remove this **/
	wnd_lin->m_xdisplay     = m_xdisplay;
	wnd_lin->m_root_xwindow = m_root_xwindow;
	wnd_lin->m_xwindow      = xwindow;
	wnd_lin->m_screen_num   = m_screen_num;

	// init window
	wnd_lin->init( shared_from_this() );

	return wnd;
}
void	n21100::base::update()
{
	jess::clog << NEB_FUNCSIG << std::endl;

	n21000::base::update();
}











