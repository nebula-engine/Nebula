#ifndef __NEBULA_PLATFORM_RENDERER_BASE_HPP__
#define __NEBULA_PLATFORM_RENDERER_BASE_HPP__

#include <jess/shared_ptr.hpp>

#include <boost/numeric/ublas/vector.hpp>

#include <nebula/define.hpp>
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
					/// ctor
					base();
					/// dtor
					virtual ~base();
					/// init
					virtual void							init( jess::shared_ptr<npw::base> );
					/// update
					virtual void							update();
					/// shutdown
					virtual void							shutdown();
					///@name draw
					///@{
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
					virtual void							mult_matrix( bnu::matrix<float, bnu::column_major> );
					/// scale
					virtual void							scale( bnu::vector<FLOAT> );
					/// look at
					virtual void							look_at( bnu::vector<float>, bnu::vector<float>, bnu::vector<float> ); 
					/// light
					virtual void							light();
					virtual void							disable_lighting() = 0;
					/// begin render
					virtual void							begin_render();
					virtual void		begin_3d() = 0;
					virtual void		end_3d() = 0;
					virtual void		begin_2d() = 0;
					virtual void		end_2d() = 0;

					/// end render
					virtual void							end_render();
					/// draw window quad
					virtual void							draw_window_quad( int, int, int, int );
					/// unproject
					virtual void							unproject( int, int, int, double*, double*, double* );
					/// parent
					std::weak_ptr<npw::base>					parent_;
			};
		}
	}
}


#endif
