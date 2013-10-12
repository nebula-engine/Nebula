#ifndef __NEBULA_PLATFORM_RENDERER_GL_BASE_HPP__
#define __NEBULA_PLATFORM_RENDERER_GL_BASE_HPP__

//#include <GL/gl.h>
//#include <GL/glu.h>
#include <GL/glew.h>

#include <jess/shared_ptr.hpp>

#include <nebula/define.hpp>

#include <nebula/platform/renderer/base.hpp>

#include <nebula/ns.hpp>

void	GetGLError();

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
					public n23000::base
				{
					public:
						///@name draw
						///{
						/// cube
						virtual void						draw_cube();
						///}
						virtual void						init( jess::shared_ptr<n22000::base> );	
						/// update						
						virtual void						update();
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
						/// un23000oject
						virtual void						un23000oject( int, int, int, double*, double*, double* );
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
						void							lookat( physx::PxVec3, physx::PxVec3, physx::PxVec3 );
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

