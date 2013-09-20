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
				
				/// lookat
				void							lookat(bnu::vector<FLOAT>,bnu::vector<FLOAT>,bnu::vector<FLOAT>);
				
				
			};
		}
	}
}


#endif
