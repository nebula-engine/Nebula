#include <stdio.h>
#include <string.h>

#include <assert.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <GL/glut.h>


#include <Nebula/Graphics/glsl/Uniform/scalar.hpp>
#include <Nebula/free.hh>

void	neb::glsl::Uniform::Scalar::Mat4::load(mat4 const & m) {
	assert(o_ != -1);
	glUniformMatrix4fv(o_, 1, false, (float*)&m);
	checkerror("glUniform1i");
}




