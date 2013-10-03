//#include <jess/except.hpp>
#include <jess/free.hpp>

#include <boost/bind.hpp>

#include <nebula/platform/window/lin/base.hpp>

#include <nebula/platform/platform/lin/base.hpp>

nppl::base::base()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
nppl::base::~base()
{
	jess::clog << NEB_FUNCSIG << std::endl;
}
void	nppl::base::init( const boost::shared_ptr<nf::app>& parent )
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	npp::base::init( parent );
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
		//throw jess::except( "Cannot connect to default X server\n" );
		
	}
	
	
	m_screen_num = DefaultScreen( m_xdisplay );

	m_screen_width =	DisplayWidth( m_xdisplay, m_screen_num );
	m_screen_height =	DisplayHeight( m_xdisplay, m_screen_num );
	m_root_xwindow =	RootWindow( m_xdisplay, m_screen_num );
	m_white_pixel =		WhitePixel( m_xdisplay, m_screen_num );
	m_black_pixel =		BlackPixel( m_xdisplay, m_screen_num );
	
	
	
}
void	nppl::base::shutdown()
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	npp::base::shutdown();
	
	XCloseDisplay( m_xdisplay );
	
}
void	nppl::base::create_window( boost::shared_ptr<npw::base>& wnd )
{
	jess::clog << NEB_FUNCSIG << std::endl;
	
	boost::shared_ptr<npwl::base> wnd_lin;
	
	windows_.push<npwl::base>( wnd_lin, boost::bind( &npwl::base::init, _1, shared_from_this() ) );
	
	wnd = wnd_lin;
	
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
	wnd_lin->m_xdisplay     = m_xdisplay;
	wnd_lin->m_root_xwindow = m_root_xwindow;
	wnd_lin->m_xwindow      = xwindow;
	wnd_lin->m_screen_num   = m_screen_num;
}
void	nppl::base::update()
{
	jess::clog << NEB_FUNCSIG << std::endl;

	npp::base::update();
}











