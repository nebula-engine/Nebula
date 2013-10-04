#include <nebula/utilities/free.hpp>


bnu::matrix<FLOAT>			nebula::utilities::matrix_yaw( FLOAT yaw )
{
	// y-axis rotation
	bnu::identity_matrix<FLOAT> m(4,4);
	
	float c = cos(pitch);
	float s = sin(pitch);
	
	m(1,1) = c;
	m(1,2) = s;
	m(2,1) = -1.0 * s;
	m(2,2) = c;
	

	
	return m;
}
bnu::matrix<FLOAT>			nebula::utilities::matrix_pitch( FLOAT pitch )
{
	// x-axis rotation
	bnu::identity_matrix<FLOAT> m(4,4);
	float c = cos(pitch);
	float s = sin(pitch);
	
	m(1,1) = c;
	m(1,2) = s;
	m(2,1) = -1.0 * s;
	m(2,2) = c;
	
	return m;
	
}
bnu::matrix<FLOAT>			nebula::utilities::matrix_roll( FLOAT roll )
{
	// z-axis rotation

	bnu::identity_matrix<FLOAT> m(4,4);
	
	float c = cos(pitch);
	float s = sin(pitch);
	
	m(1,1) = c;
	m(1,2) = s;
	m(2,1) = -1.0 * s;
	m(2,2) = c;

	return m;

}
void					nebula::utilities::matrix_set_pos( bnu::matrix<FLOAT>&, bnu::vector<FLOAT> )
{
	
}



