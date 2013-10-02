#ifndef __NEBULA_PLATFORM_PLATFORM_LIN_BASE_HPP__
#define __NEBULA_PLATFORM_PLATFORM_LIN_BASE_HPP__

#include <boost/shared_ptr.hpp>

#include <X11/Xlibint.h>
#include <X11/Xlib.h>
#undef max
#undef min


#include <nebula/define.hpp>

#include <nebula/platform/platform/base.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace platform
	{
		namespace platform
		{
			namespace lin
			{
				class base:
					public npp::base
				{
				public:
					base();
					virtual ~base();
					virtual void						init( const boost::shared_ptr<nf::app>& );
					virtual void						shutdown();
					virtual void						update();

					virtual void						create_window( boost::shared_ptr<npw::base>& );



					::Display*						m_xdisplay;// = XOpenDisplay( NULL );


					int							m_screen_num;//= DefaultScreen( m_xdisplay );

					UINT							m_screen_width;// =	DisplayWidth( m_xdisplay, m_screen_num );
					UINT							m_screen_height;// =	DisplayHeight( m_xdisplay, m_screen_num );
					::Window						m_root_xwindow;// =	RootWindow( m_xdisplay, m_screen_num );
					unsigned long						m_white_pixel;// =		WhitePixel( m_xdisplay, m_screen_num );
					unsigned long						m_black_pixel;// =		BlackPixel( m_xdisplay, m_screen_num );







				};
			}
		}
	}
}

#endif
