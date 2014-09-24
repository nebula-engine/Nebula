#include <iomanip>
#include <sstream>

#include <neb/gfx/free.hpp>
#include <neb/gfx/opengl/uniform.hpp>

void		neb::gfx::ogl::glUniformv(GLint location, GLsizei count, glm::vec3 const * const & value) {
	checkerror("unknown");
	glUniform3fv(location, count, (float*)value);
	checkerror("glUniform3fv");
}
void		neb::gfx::ogl::glUniformv(GLint location, GLsizei count, glm::vec4 const * const & value) {
	checkerror("unknown");
	glUniform4fv(location, count, (float*)value);
	checkerror("glUniform4fv");
}
void		neb::gfx::ogl::glUniformv(GLint location, GLsizei count, glm::mat4 const * const & value) {
	checkerror("unknown");
	glUniformMatrix4fv(location, count, GL_FALSE, (float*)value);
	checkerror("glUniformMatrix4fv");
}
void		neb::gfx::ogl::glUniformv(GLint location, GLsizei count, float const * const & value) {
	checkerror("unknown");
	glUniform1fv(location, count, value);
	checkerror("glUniform1fv %i %i\n", location, count);
}
void		neb::gfx::ogl::glUniformv(GLint location, GLsizei count, int const * const & value) {
	checkerror("unknown");
	glUniform1iv(location, count, value);
	checkerror("glUniform1iv %i %i\n", location, count);
}
void		neb::gfx::ogl::glUniform(GLint location, float const & value) {
	checkerror("unknown");
	glUniform1f(location, value);
	checkerror("glUniform1f %i\n", location);
}
void		neb::gfx::ogl::glUniform(GLint location, int const & value) {
	checkerror("unknown");
	glUniform1i(location, value);
	checkerror("glUniform1i %i\n", location);
}
void		neb::gfx::ogl::glUniform(GLint location, glm::mat4 const & value) {
	checkerror("unknown");
	glUniformMatrix4fv(location, 1, GL_FALSE, (float*)&value);
	checkerror("glUniformMatrix4fv %i\n", location);
}



