#ifndef __NEBULA_PLATFORM_RENDERER_BASE_HPP__
#define __NEBULA_PLATFORM_RENDERER_BASE_HPP__

#include <jess/shared_ptr.hpp>

#include <boost/numeric/ublas/vector.hpp>

#include <nebula/utilities/types/platform/types.hpp>

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
				base();
				virtual ~base();

				virtual void						init( jess::shared_ptr<npw::base> );
				virtual void						update();
				virtual void						shutdown();
				
				///@name draw
				///{
				/// cube
				void							draw_cube();
				void							draw_sphere();
				void							draw_quad();
				///}


				virtual void						resize( int, int );
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
				virtual void						look_at( bnu::vector<float>, bnu::vector<float>, bnu::vector<float> ); 
				/// light
				virtual void						light();
				/// begin render
				virtual void						begin_render();
				/// end render
				virtual void						end_render();
				/// draw window quad
				virtual void						draw_window_quad( int, int, int, int );
				/// unproject
				virtual void						unproject( int, int, int, double*, double*, double* );
				
				
				


				std::weak_ptr<npw::base>				parent_;
			};
		}
	}
}


#endif
