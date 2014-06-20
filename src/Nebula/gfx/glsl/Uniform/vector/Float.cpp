#include <stdio.h>
#include <string.h>

#include <assert.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <GL/glut.h>

//#include <math/mat44.hpp>

//#include <Nebula/scene/scene.hpp>
#include <Nebula/gfx/glsl/Uniform/vector.hpp>
#include <Nebula/free.hh>





void	neb::glsl::Uniform::Vector::Float::load(int c, float f) {
	glUniform1f(o_[c], f);
	checkerror("glUniform1f");
}




