#include <stdio.h>
#include <string.h>

#include <assert.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <GL/glut.h>

//#include <math/mat44.hpp>

//#include <Nebula/scene/scene.hpp>
#include <Nebula/gfx/glsl/Uniform/scalar.hpp>
#include <Nebula/free.hh>




void	neb::glsl::Uniform::Scalar::Float::load(float f) {
	glUniform1f(o_, f);
	checkerror("glUniform1f");
}




