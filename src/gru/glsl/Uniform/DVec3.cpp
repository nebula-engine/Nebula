#include <stdio.h>
#include <string.h>

#include <assert.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <GL/glut.h>

#include <math/mat44.hpp>

#include <gru/scene/scene.hpp>
#include <gru/glsl/Uniform/uniform.hpp>
#include <gru/free.hpp>


void	glutpp::glsl::Uniform::Scalar::DVec3::load(double* v) {
	glUniform3dv(o_, 1, v);
	checkerror("glUniform3fv");
}
void	glutpp::glsl::Uniform::Scalar::DVec4::load(double* v) {
	glUniform4dv(o_, 1, v);
	checkerror("glUniform3fv");
}

void	glutpp::glsl::Uniform::Vector::DVec4::load(int c, double* v) {
	glUniform4dv(o_[c], 1, v);
	checkerror("glUniform3fv");
}
void	glutpp::glsl::Uniform::Vector::DVec3::load(int c, double* v) {
	glUniform3dv(o_[c], 1, v);
	checkerror("glUniform3fv");
}


