#ifndef __NEBULA_UTILITIES_FREE_HPP__
#define __NEBULA_UTILITIES_FREE_HPP__

#include <nebula/ns.hpp>

namespace nebula
{
	namespace utilities
	{
		bnu::matrix<FLOAT,bnu::column_major>	matrix_yaw( FLOAT yaw );
		bnu::matrix<FLOAT,bnu::column_major>	matrix_pitch( FLOAT pitch );
		bnu::matrix<FLOAT,bnu::column_major>	matrix_roll( FLOAT roll );
		void					matrix_set_pos( bnu::matrix<FLOAT>&, bnu::vector<FLOAT> );
	}
}


#endif
