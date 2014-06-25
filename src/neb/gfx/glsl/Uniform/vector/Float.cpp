#include <stdio.h>
#include <string.h>

#include <assert.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <GL/glut.h>

//#include <math/mat44.hpp>

//#include <neb/scene/scene.hpp>
#include <neb/gfx/glsl/Uniform/vector.hpp>
#include <neb/free.hh>





void	neb::glsl::Uniform::Vector::Float::load(int c, float f) {
	glUniform1f(o_[c], f);
	checkerror("glUniform1f");
}




