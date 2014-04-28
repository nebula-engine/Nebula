#include <stdio.h>
#include <string.h>

#include <assert.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <GL/glut.h>

//#include <math/mat44.hpp>

//#include <gru/scene/scene.hpp>
#include <gru/glsl/Uniform/uniform.hpp>
#include <gru/free.hpp>




void	glutpp::glsl::Uniform::Scalar::Float::load(float f) {
	glUniform1f(o_, f);
	checkerror("glUniform1f");
}
void	glutpp::glsl::Uniform::Scalar::Double::load(double f) {
	glUniform1d(o_, f);
	checkerror("glUniform1d");
}

void	glutpp::glsl::Uniform::Vector::Float::load(int c, float f) {
	glUniform1f(o_[c], f);
	checkerror("glUniform1f");
}
void	glutpp::glsl::Uniform::Vector::Double::load(int c, double f) {
	glUniform1d(o_[c], f);
	checkerror("glUniform1d");
}




