#ifndef __NEBULA_PLATFORM_RENDERER_GL_GLX_BASE_HPP__
#define __NEBULA_PLATFORM_RENDERER_GL_GLX_BASE_HPP__

#include <GL/glew.h>
#include <GL/glx.h>

#include <X11/Xlibint.h>
#include <X11/Xlib.h>
#undef max
#undef min

#include <boost/numeric/ublas/vector.hpp>

#include <nebula/define.hpp>

#include <nebula/platform/renderer/gl/base.hpp>

namespace nebula
{
	namespace platform
	{
		namespace renderer
		{
			namespace gl
			{
				namespace glx
				{
					/// base
					class base:
						public nprg::base
					{
						public:
							///@name draw
							///{
							/// cube
							virtual void						draw_cube();
							///}
							/// init			
							virtual void						init( jess::shared_ptr<npw::base> );
							/// shutdown			
							virtual void						shutdown();
							/// update
							virtual void						update();
							/// viewport
							virtual void						viewport( int, int, int, int );
							/// push_matrix
							virtual void						push_matrix();
							/// pop_matrix
							virtual void						pop_matrix();
							/// swap
							virtual void						swap();
							/// mult_matrix
							virtual void						mult_matrix( bnu::matrix<FLOAT> );
							/// scale
							virtual void						scale( bnu::vector<FLOAT> );
							/// look at
							virtual void						look_at( bnu::vector<FLOAT>, bnu::vector<FLOAT>, bnu::vector<FLOAT> ); 
							/// light
							virtual void						light();
							/// begin render
							virtual void						begin_render();
							/// end render
							virtual void						end_render();
							/// draw window quad
							virtual void						draw_window_quad( int, int, int, int );
							/// attributes
							GLint*							att;
							/// visual info
							XVisualInfo*						m_vi;
							/// colormap
							Colormap						m_cmap;
							/// window attributes
							XSetWindowAttributes					m_swa;
							/// context
							GLXContext						m_glc;
							/// window
							::Window						m_xwindow;
							/// root window
							::Window						m_root_xwindow;
							/// display
							::Display*						m_xdisplay;
					};
				}
			}
		}
	}
}


#endif

