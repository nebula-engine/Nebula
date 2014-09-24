#ifndef NEB_GFX_UTIL_IO_HPP
#define NEB_GFX_UTIL_IO_HPP

#include <ostream>

#include <glm/glm.hpp>

std::ostream&	operator<<(std::ostream& os, glm::vec3 const & v);
std::ostream&	operator<<(std::ostream& os, glm::vec4 const & v);
std::ostream&	operator<<(std::ostream& os, glm::mat4 const & v);

#endif
