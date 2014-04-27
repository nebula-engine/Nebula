#include <stdio.h>
#include <string.h>

#include <assert.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <GL/glut.h>

#include <math/mat44.hpp>

#include <gru/scene/scene.hpp>
#include <gru/glsl/Uniform/uniform.hpp>
#include <gru/window/window.hpp>
#include <gru/free.hpp>

void	glutpp::glsl::Uniform::Scalar::Int::load(int i) {
	glUniform1i(o_, i);
	checkerror("glUniform1i");
}
void	glutpp::glsl::Uniform::Scalar::Sampler2D::load(int i) {
	glUniform1i(o_, i);
	checkerror("glUniform1i");
}





void	glutpp::glsl::Uniform::Vector::Int::load(int c, int i) {
	glUniform1i(o_[c], i);
	checkerror("glUniform1i");
}




