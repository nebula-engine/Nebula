#ifndef __NEBULA_PLATFORM_PLATFORM_LIN_BASE_HPP__
#define __NEBULA_PLATFORM_PLATFORM_LIN_BASE_HPP__

#include <jess/shared_ptr.hpp>

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
				/// base
				class base:
					public npp::base
				{
				public:
					/// ctor
					base();
					/// dtor
					virtual ~base();
					/// init
					virtual void						init( const jess::shared_ptr<nf::app>& );
					/// shutdown
					virtual void						shutdown();
					/// update
					virtual void						update();
					/// create window
					virtual void						create_window( jess::shared_ptr<npw::base>& );
					/// display
					::Display*						m_xdisplay;// = XOpenDisplay( NULL );
					/// screen num
					int							m_screen_num;//= DefaultScreen( m_xdisplay );
					/// width
					UINT							m_screen_width;// =	DisplayWidth( m_xdisplay, m_screen_num );
					/// height
					UINT							m_screen_height;// =	DisplayHeight( m_xdisplay, m_screen_num );
					/// root window
					::Window						m_root_xwindow;// =	RootWindow( m_xdisplay, m_screen_num );
					/// pixel
					unsigned long						m_white_pixel;// =		WhitePixel( m_xdisplay, m_screen_num );
					/// pixel
					unsigned long						m_black_pixel;// =		BlackPixel( m_xdisplay, m_screen_num );
				};
			}
		}
	}
}

#endif
