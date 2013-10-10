#ifndef __NEBULA_PLATFORM_WINDOW_LIN_BASE_HPP__
#define __NEBULA_PLATFORM_WINDOW_LIN_BASE_HPP__

#include <X11/Xutil.h>
#include <X11/Xlib.h>
#include <X11/Xlibint.h>
#undef max
#undef min

#include <nebula/define.hpp>

#include <nebula/platform/window/base.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace platform
	{
		namespace window
		{
			namespace lin
			{
				class base:
					public npw::base
				{
				public:
					base();
					virtual ~base();
					virtual void			init( jess::shared_ptr<npp::base> );
					virtual void			shutdown();
					virtual void			update();
					virtual void			register_keys();
					virtual void			center_pointer();
					virtual void			expose_window( XEvent );
					virtual int			lookup_key( int );
					virtual void			focus_change( XEvent );
					virtual void			process_message( jess::shared_ptr<na::message> );
	
					/// keys
					std::map<int,int>		keys_;

					::XGCValues			m_values;
					unsigned long			m_valuemask;


					int				m_line_width;
					int				m_line_style;
					int				m_cap_style;
					int				m_join_style;


					UINT				m_center_x;
					UINT				m_center_y;

					int				m_screen_num;
					long				m_event_mask;

					::Display*			m_xdisplay;
					::Window			m_xwindow;
					::Window			m_root_xwindow;
					::GC				m_gc;

				};
			}
		}
	}
}

#endif
