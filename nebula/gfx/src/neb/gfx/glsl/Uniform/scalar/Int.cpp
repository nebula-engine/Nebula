#include <stdio.h>
#include <string.h>

#include <assert.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <GL/glut.h>


#include <neb/gfx/glsl/Uniform/scalar.hpp>
#include <neb/free.hh>

void	neb::glsl::Uniform::Scalar::Int::load(int i) {
	glUniform1i(o_, i);
	checkerror("glUniform1i");
}
void	neb::glsl::Uniform::Scalar::Sampler2D::load(int i) {
	glUniform1i(o_, i);
	checkerror("glUniform1i");
}





