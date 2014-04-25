#include <stdio.h>
#include <string.h>

#include <assert.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <GL/glut.h>

#include <math/mat44.hpp>

#include <gru/scene/scene.hpp>
#include <gru/glsl/uniform.hpp>
#include <gru/window/window.hpp>


void	glutpp::glsl::Uniform::Double::load(double f) {
	glUniform1d(o_[0], f);
	checkerror("glUniform1d");
}
void	glutpp::glsl::Uniform::Double::load(int c, double f) {
	glUniform1d(o_[c], f);
	checkerror("glUniform1d");
}




