#ifndef __NEBULA_PLATFORM_WINDOW_LIN_BASE_HPP__
#define __NEBULA_PLATFORM_WINDOW_LIN_BASE_HPP__

#include <X11/Xlib.h>
#include <X11/Xlibint.h>

#include <nebula/define.hpp>

#include <nebula/utilities/types/platform/types.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
namespace platform
{
namespace window
{
namespace lin
{
class base
{
//public:
base();
virtual ~base();
virtual void			init( const boost::shared_ptr<npp::base>& );

::XGCValues			m_values;
unsigned long			m_valuemask;


int				m_line_width;
int				m_line_style;
int				m_cap_style;
int				m_join_style;

UINT				m_win_width;
UINT				m_win_height;

UINT				m_center_x;
UINT				m_center_y;

int				m_screen_num;
long				m_event_mask;

::Display*			m_xdisplay;
::Window			m_xwindow;
::GC				m_gc;

};
}
}
}
}

#endif
