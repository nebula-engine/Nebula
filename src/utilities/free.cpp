/*#include <nebula/utilities/free.hpp>


bnu::matrix<float,bnu::column_major>		nebula::utilities::matrix_yaw( float yaw )
{
	// y-axis rotation
	bnu::matrix<float> m = bnu::identity_matrix<float,bnu::column_major>(3,3);
	
	float c = cos( yaw );
	float s = sin( yaw );
	
	m(0,0) = c;	m(0,2) = s;
	m(2,0) = -s;	m(2,2) = c;
	
	return m;
}
bnu::matrix<float,bnu::column_major>		nebula::utilities::matrix_pitch( float pitch )
{
	// x-axis rotation
	bnu::matrix<float> m = bnu::identity_matrix<float,bnu::column_major>(3,3);

	float c = cos( pitch );
	float s = sin( pitch );
	
	m(1,1) = c;	m(1,2) = -s;
	m(2,1) = s;	m(2,2) = c;
	
	return m;
}
bnu::matrix<float,bnu::column_major>		nebula::utilities::matrix_roll( float roll )
{
	// z-axis rotation

	bnu::matrix<float> m = bnu::identity_matrix<float,bnu::column_major>(3,3);
	
	float c = cos( roll );
	float s = sin( roll );
	
	m(0,0) = c;	m(0,1) = -s;
	m(1,0) = s;	m(1,1) = c;

	return m;

}
void					nebula::utilities::matrix_set_pos( bnu::matrix<float>&, bnu::vector<float> )
{
	
}


*/
