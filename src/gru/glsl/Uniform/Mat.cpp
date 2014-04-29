#include <stdio.h>
#include <string.h>

#include <assert.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <GL/glut.h>


#include <gru/scene/scene.hpp>
#include <gru/glsl/Uniform/uniform.hpp>
#include <gru/window/window.hpp>
#include <gru/free.hpp>

void	glutpp::glsl::Uniform::Scalar::Mat4::load(physx::PxMat44 m) {
	assert(o_ != -1);
	glUniformMatrix4fv(o_, 1, false, (float*)&m);
	checkerror("glUniform1i");
}



/*
void	glutpp::glsl::Uniform::Vector::Mat3::load(int c, int i) {
	glUniform1i(o_[c], i);
	checkerror("glUniform1i");
}

void	glutpp::glsl::Uniform::Vector::Mat3::load(int c, int i) {
	glUniform1i(o_[c], i);
	checkerror("glUniform1i");
}
*/



