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


void	glutpp::glsl::uniform::load_3fv(double* v) {
	glUniform3dv(o_[0], 1, v);
	checkerror("glUniform3fv");
}
void	glutpp::glsl::uniform::load_3fv(int c, double* v) {
	glUniform3dv(o_[c], 1, v);
	checkerror("glUniform3fv");
}


