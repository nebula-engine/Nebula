#include <stdio.h>
#include <string.h>

#include <assert.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <GL/glut.h>


#include <Nebula/core/scene/Base.hh>
#include <Nebula/gfx/glsl/Uniform/vector.hpp>
#include <Nebula/free.hh>





void	neb::glsl::Uniform::Vector::Int::load(int c, int i) {
	glUniform1i(o_[c], i);
	checkerror("glUniform1i");
}




