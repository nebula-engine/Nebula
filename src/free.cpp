#include <nebula/free.hpp>

std::ostream&	operator<<( std::ostream& os, physx::PxMat44 const & mat )
{
	os << "[" << mat.column0.x << " " << mat.column1.x << " " << mat.column2.x << " " << mat.column3.x << "" << std::endl;
	os << " " << mat.column0.y << " " << mat.column1.y << " " << mat.column2.y << " " << mat.column3.y << "" << std::endl;
	os << " " << mat.column0.z << " " << mat.column1.z << " " << mat.column2.z << " " << mat.column3.z << "" << std::endl;
	os << " " << mat.column0.w << " " << mat.column1.w << " " << mat.column2.w << " " << mat.column3.w << "]" << std::endl;

	return os;
}


