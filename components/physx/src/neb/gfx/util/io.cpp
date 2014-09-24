#include <iomanip>

#include <neb/gfx/util/io.hpp>

std::ostream&	operator <<(std::ostream& os, glm::vec3 const & v) {
	return os << v[0] << " " << v[1] << " " << v[2];
}
std::ostream&	operator <<(std::ostream& os, glm::vec4 const & v) {
	os
		<< std::setw(16) << v[0]
		<< std::setw(16) << v[1]
		<< std::setw(16) << v[2]
		<< std::setw(16) << v[3];
	return os;
}
std::ostream&	operator <<(std::ostream& os, glm::mat4 const & v) {
	os
		<< v[0] << std::endl
		<< v[1] << std::endl
		<< v[2] << std::endl
		<< v[3];
	return os;
}

