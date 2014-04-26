#include <stdio.h>
#include <string.h>

#include <assert.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <GL/glut.h>

#include <math/mat44.hpp>

#include <gru/scene/scene.hpp>
#include <gru/glsl/Uniform/uniform.hpp>
#include <gru/window/window.hpp>


glutpp::glsl::Uniform::Scalar::Base::Base() {}
void	glutpp::glsl::Uniform::Scalar::Base::init(char const * name)
{
	//printf("%s\n",__PRETTY_FUNCTION__);
	name_ = name;
	//printf("uniform %s\n",name_);
	checkerror("glGetUniformLocation");
	//locate();
}

void	glutpp::glsl::Uniform::Vector::Base::init(std::string name1, std::string name2) {

	name1_ = name1;
	name2_ = name2;
	
	//printf("%s\n",__PRETTY_FUNCTION__);
	
}
void	glutpp::glsl::Uniform::Scalar::Base::locate(std::shared_ptr<glutpp::glsl::program> p) {
	printf("%s\n",__PRETTY_FUNCTION__);

	assert(p);

	assert(!name_.empty());

	o_ = glGetUniformLocation(p->o_, name_.c_str());
}


void	glutpp::glsl::Uniform::Vector::Base::locate(std::shared_ptr<glutpp::glsl::program> p) {
	printf("%s\n",__PRETTY_FUNCTION__);

	assert(p);

	char o_str[8];
	//char name[128];

	assert(!name1_.empty());
	assert(!name2_.empty());
	
	std::string name;
	
	for(int c = 0; c < c_; c++) {

		sprintf(o_str, "%i", c);

		name1_ + '[' + o_str + "]." + name2_;
		
		//printf("str = '%s' c = %i\n", o_str, c);

		//printf("locate '%s'\n", name);

		o_[c] = glGetUniformLocation(p->o_, name.c_str());
	}
}

