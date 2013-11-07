#ifndef __NEBULA_PLATFORM_PLATFORM_LIN_BASE_HPP__
#define __NEBULA_PLATFORM_PLATFORM_LIN_BASE_HPP__


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
					public n21000::base
				{
				public:
					/// ctor
					base();
					/// dtor
					virtual ~base();
					/// init
					virtual void						init( std::shared_ptr<n10000::app> );
					/// shutdown
					virtual void						shutdown();
					/// update
					virtual void						update();
					/// create window
					virtual std::shared_ptr<n22000::base>			create_window();
					/// display
					::Display*						m_xdisplay;// = XOpenDisplay( NULL );
					/// screen num
					int							m_screen_num;//= DefaultScreen( m_xdisplay );
					/// width
					uint32_t						m_screen_width;// =	DisplayWidth( m_xdisplay, m_screen_num );
					/// height
					uint32_t						m_screen_height;// =	DisplayHeight( m_xdisplay, m_screen_num );
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
