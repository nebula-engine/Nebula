#ifndef __NEBULA_PLATFORM_RENDERER_GL_BASE_HPP__
#define __NEBULA_PLATFORM_RENDERER_GL_BASE_HPP__

//#include <GL/gl.h>
//#include <GL/glu.h>
#include <GL/glew.h>

#include <jess/shared_ptr.hpp>

#include <boost/numeric/ublas/vector.hpp>

#include <nebula/define.hpp>

#include <nebula/platform/renderer/base.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace platform
	{
		namespace renderer
		{
			namespace gl
			{
				/// base
				class base:
					public npr::base
				{
					public:
						///@name draw
						///{
						/// cube
						virtual void						draw_cube();
						///}
						virtual void						init( jess::shared_ptr<npw::base> );	
						/// update						
						virtual void						update();
						/// push_matrix
						virtual void						push_matrix();
						/// pop_matrix
						virtual void						pop_matrix();
						/// swap
						virtual void						swap();
						/// mult_matrix
						virtual void						mult_matrix( bnu::matrix<float, bnu::column_major> );
						/// scale
						virtual void						scale( bnu::vector<FLOAT> );
						/// look at
						virtual void						look_at( bnu::vector<FLOAT>, bnu::vector<FLOAT>, bnu::vector<FLOAT> ); 
						/// light
						virtual void						light();
						void							disable_lighting();
						/// begin render
						virtual void						begin_render();
						virtual void		begin_3d();
						virtual void		end_3d();
						virtual void		begin_2d();
						virtual void		end_2d();
						/// end render
						virtual void						end_render();
						/// draw window quad
						virtual void						draw_window_quad( int, int, int, int );
						/// unproject
						virtual void						unproject( int, int, int, double*, double*, double* );
						/// sphere
						virtual void						draw_sphere();
						/// 2d quad
						virtual void						draw_2d_quad();
						/// quad	
						virtual void						draw_quad();
						virtual void						draw_text( int, int, std::string ) = 0;
						/// resize
						virtual void						resize( int, int );
						/// lookat
						void							lookat( bnu::vector<FLOAT>, bnu::vector<FLOAT>, bnu::vector<FLOAT> );
						/// compile shaders
						virtual void						compile_shaders( unsigned int& );
						/// load shader source form file
						virtual void						load_shader_source( const char *, char ** const );
						/// load identity
						virtual void						load_identity();
				};
			}	
		}
	}
}


#endif

