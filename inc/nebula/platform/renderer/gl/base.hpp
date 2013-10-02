#ifndef __NEBULA_PLATFORM_RENDERER_GL_BASE_HPP__
#define __NEBULA_PLATFORM_RENDERER_GL_BASE_HPP__

//#include <GL/gl.h>
//#include <GL/glu.h>
#include <GL/glew.h>

#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/vector.hpp>

#include <nebula/define.hpp>
#include <nebula/utilities/types/platform/types.hpp>

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
					void							draw_cube();
					///}

					virtual void		init( const boost::shared_ptr<npw::base>& );	
					virtual void		update();
					/// push_matrix
					virtual void		push_matrix();
					/// pop_matrix
					virtual void		pop_matrix();
					/// swap
					virtual void		swap();
					/// mult_matrix
					virtual void		mult_matrix( bnu::matrix<FLOAT> );
					/// scale
					virtual void		scale( bnu::vector<FLOAT> );
					/// look at
					virtual void		look_at( bnu::vector<FLOAT>, bnu::vector<FLOAT>, bnu::vector<FLOAT> ); 
					/// light
					virtual void		light();
					/// begin render
					virtual void		begin_render();
					/// end render
					virtual void		end_render();
					/// draw window quad
					virtual void		draw_window_quad(int,int,int,int);
					virtual void		unproject( int, int, int, double*, double*, double* );
					virtual void		draw_sphere();
					virtual void			draw_2d_quad();
					virtual void			draw_quad();
					virtual void		resize( int, int );
					/// lookat
					void							lookat(bnu::vector<FLOAT>,bnu::vector<FLOAT>,bnu::vector<FLOAT>);

virtual void		compile_shaders( unsigned int& );
virtual void		load_shader_source( const char *, char ** const );
virtual void		load_identity();
				};
			}		}
	}
}


#endif

