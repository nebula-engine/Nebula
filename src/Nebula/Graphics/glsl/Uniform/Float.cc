#include <stdio.h>
#include <string.h>

#include <assert.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <GL/glut.h>

//#include <math/mat44.hpp>

//#include <Nebula/scene/scene.hpp>
#include <Nebula/Graphics/glsl/Uniform/uniform.hh>
#include <Nebula/free.hh>




void	Neb::glsl::Uniform::Scalar::Float::load(float f) {
	glUniform1f(o_, f);
	checkerror("glUniform1f");
}
void	Neb::glsl::Uniform::Scalar::Double::load(double f) {
	glUniform1d(o_, f);
	checkerror("glUniform1d");
}

void	Neb::glsl::Uniform::Vector::Float::load(int c, float f) {
	glUniform1f(o_[c], f);
	checkerror("glUniform1f");
}
void	Neb::glsl::Uniform::Vector::Double::load(int c, double f) {
	glUniform1d(o_[c], f);
	checkerror("glUniform1d");
}




