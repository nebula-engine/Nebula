#include <stdio.h>
#include <string.h>

#include <assert.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <Nebula/Graphics/glsl/program.hh>
#include <Nebula/Graphics/glsl/Uniform/scalar.hpp>

neb::glsl::Uniform::Scalar::Base::Base(std::string name) {
	//printf("%s\n",__PRETTY_FUNCTION__);
	name_ = name;
	o_ = -1;
	//printf("uniform %s\n",name_);
	//checkerror("glGetUniformLocation");
	//locate();
}
void	neb::glsl::Uniform::Scalar::Base::locate(std::shared_ptr<neb::glsl::program> p) {
	printf("%s\n",__PRETTY_FUNCTION__);

	assert(p);

	assert(!name_.empty());

	o_ = glGetUniformLocation(p->o_, name_.c_str());
}


