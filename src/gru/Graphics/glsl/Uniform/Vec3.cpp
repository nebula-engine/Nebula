#include <stdio.h>
#include <string.h>

#include <assert.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <GL/glut.h>


//#include <gru/scene/scene.hpp>
#include <gru/Graphics/glsl/Uniform/uniform.hpp>
#include <gru/free.hpp>


void	glutpp::glsl::Uniform::Scalar::Vec3::load(float* v) {
	glUniform3fv(o_, 1, v);
	checkerror("glUniform3fv");
}
void	glutpp::glsl::Uniform::Scalar::Vec4::load(float* v) {
	glUniform4fv(o_, 1, v);
	checkerror("glUniform4fv");
}


void	glutpp::glsl::Uniform::Vector::Vec3::load(int c, float* v) {
	glUniform3fv(o_[c], 1, v);
	checkerror("glUniform3fv");
}
void	glutpp::glsl::Uniform::Vector::Vec4::load(int c, float* v) {
	GLint o = o_[c];
	assert(o != -1);
	glUniform4fv(o, 1, v);
	checkerror("glUniform4fv");
}




