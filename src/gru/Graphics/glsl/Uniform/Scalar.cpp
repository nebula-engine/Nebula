#include <stdio.h>
#include <string.h>

#include <assert.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <GL/glut.h>

//#include <math/mat44.hpp>

//#include <gru/scene/scene.hpp>
#include <gru/Graphics/glsl/program.hpp>
#include <gru/Graphics/glsl/Uniform/uniform.hpp>
//#include <gru/window/window.hpp>

glutpp::glsl::Uniform::Scalar::Base::Base(std::string name) {
	//printf("%s\n",__PRETTY_FUNCTION__);
	name_ = name;
	o_ = -1;
	//printf("uniform %s\n",name_);
	//checkerror("glGetUniformLocation");
	//locate();
}
void	glutpp::glsl::Uniform::Scalar::Base::locate(std::shared_ptr<glutpp::glsl::program> p) {
	printf("%s\n",__PRETTY_FUNCTION__);

	assert(p);

	assert(!name_.empty());

	o_ = glGetUniformLocation(p->o_, name_.c_str());
}


