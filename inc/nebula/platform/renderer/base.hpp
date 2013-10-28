#ifndef __NEBULA_PLATFORM_RENDERER_BASE_HPP__
#define __NEBULA_PLATFORM_RENDERER_BASE_HPP__

#include <nebula/define.hpp>
//#include <PxPhysicsAPI.h>
#include <foundation/PxMat44.h>

#include <jess/shared_ptr.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace platform
	{
		namespace renderer
		{
			/// base
			class base
			{
				public:
					typedef std::shared_ptr<base>		shared_t;
				public:
					/// ctor
					base();
					/// dtor
					virtual ~base();
					/// init
					virtual void							init( jess::shared_ptr<n22000::base> );
					/// update
					virtual void							update();
					/// shutdown
					virtual void							shutdown();
					///@name draw
					///@{
					/**
					*/
					/// cube
					virtual void							draw_cube();
					/// sphere
					virtual void							draw_sphere();
					/// quad
					virtual void							draw_quad();
					/// text
					virtual void							draw_text( int, int, std::string ) = 0;
					///@}
					/// resize
					virtual void							resize( int, int );
					/// push matrix
					virtual void							push_matrix();
					/// pop matrix
					virtual void							pop_matrix();
					/// swap
					virtual void							swap();
					/// mult matrix
					virtual void							mult_matrix( physx::PxMat44 );
					/// scale
					virtual void							scale( physx::PxVec3 );
					/// look at
					virtual void							look_at( physx::PxVec3, physx::PxVec3, physx::PxVec3 ); 
					/// light
					virtual void							light();
					virtual void							disable_lighting() = 0;
					/// begin render
					virtual void							begin_render();
					/** \brief begin 3d
					*/
					virtual void							begin_3d() = 0;
					/** \brief end 3d
					*/
					virtual void							end_3d() = 0;
					virtual void							begin_2d() = 0;
					virtual void							end_2d() = 0;

					/// end render
					virtual void							end_render();
					/// draw window quad
					virtual void							draw_window_quad( int, int, int, int );
					/// unproject
					virtual void							unproject( int, int, int, double*, double*, double* );
					/// parent
					std::weak_ptr<n22000::base>					parent_;
			};
		}
	}
}


#endif
