#ifndef __NEBULA_PLATFORM_RENDERER_GL_GLX_BASE_HPP__
#define __NEBULA_PLATFORM_RENDERER_GL_GLX_BASE_HPP__

#include <GL/glew.h>
#include <GL/glx.h>

#include <X11/Xlibint.h>
#include <X11/Xlib.h>
#undef max
#undef min

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
						public n23100::base
					{
						public:
							///@name draw
							///{
							/// cube
							virtual void						draw_cube();
							///}
							/// init			
							virtual void						init( std::shared_ptr<n22000::base> );
							virtual void						init_raster_font();
							/// shutdown			
							virtual void						shutdown();
							/// update
							virtual void						update();
							/// viewport
							virtual void						viewport( int, int, int, int );
							/// text
							virtual void						draw_text( int, int, std::string );
							/// push_matrix
							virtual void						push_matrix();
							/// pop_matrix
							virtual void						pop_matrix();
							/// swap
							virtual void						swap();
							/// mult_matrix
							virtual void						mult_matrix( physx::PxMat44 );
							/// scale
							virtual void						scale( physx::PxVec3 );
							/// look at
							virtual void						look_at( physx::PxVec3, physx::PxVec3, physx::PxVec3 ); 
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
							/// visual in10000o
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
							/// font base
							GLuint							font_base_;
					};
				}
			}
		}
	}
}


#endif

