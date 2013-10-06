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
						void							draw_cube();
						///}
						virtual void						init( jess::shared_ptr<npw::base> );
						virtual void						shutdown();
						virtual void						update();
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




						GLint*							att;
						XVisualInfo*						m_vi;
						Colormap						m_cmap;
						XSetWindowAttributes					m_swa;
						GLXContext						m_glc;



						::Window						m_xwindow;
						::Window						m_root_xwindow;
						::Display*						m_xdisplay;
					};
				}
			}
		}
	}
}


#endif

