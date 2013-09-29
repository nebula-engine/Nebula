#ifndef __NEBULA_PLATFORM_RENDERER_BASE_HPP__
#define __NEBULA_PLATFORM_RENDERER_BASE_HPP__

#include <boost/numeric/ublas/vector.hpp>

namespace bnu = boost::numeric::ublas;

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
				///@name draw
				///{
				/// cube
				void							draw_cube();
				///}
			
/// push_matrix
void		push_matrix();
/// pop_matrix
void		pop_matrix();
/// swap
void		swap();
/// mult_matrix
void		mult_matrix(const bnu::matrix<FLOAT>&);
/// scale
void		scale(const bnu::vector<FLOAT>&);
/// look at
void		look_at( const bnu::vector<FLOAT>&, const bnu::vector<FLOAT>&, const bnu::vector<FLOAT>& ); 


	
				/// lookat
				void							lookat(bnu::vector<FLOAT>,bnu::vector<FLOAT>,bnu::vector<FLOAT>);
				
				
			};
		}
	}
}


#endif
