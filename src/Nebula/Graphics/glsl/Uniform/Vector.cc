#include <stdio.h>
#include <string.h>

#include <assert.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <GL/glut.h>

//#include <Nebula/scene/scene.hpp>
#include <Nebula/Graphics/glsl/Uniform/uniform.hh>
#include <Nebula/Graphics/glsl/program.hh>
//#include <Nebula/window/window.hpp>


Neb::glsl::Uniform::Vector::Base::Base(std::string name1, std::string name2) {
	name1_ = name1;
	name2_ = name2;
	c_ = 0;
	for(int i = 0; i < LEN; i++) {
		o_[i] = -1;
	}
	//printf("%s\n",__PRETTY_FUNCTION__);
}
void	Neb::glsl::Uniform::Vector::Base::locate(std::shared_ptr<Neb::glsl::program> p) {
	printf("%s\n",__PRETTY_FUNCTION__);

	assert(p);

	char o_str[8];
	//char name[128];

	assert(!name1_.empty());
	assert(!name2_.empty());
	
	std::string name;
	
	for(int c = 0; c < LEN; c++) {
		
		sprintf(o_str, "%i", c);
		
		name = name1_ + "[" + o_str + "]." + name2_;
		
		//printf("str = '%s' c = %i\n", o_str, c);
		
		GLint o = glGetUniformLocation(p->o_, name.c_str());
		
		//printf("locate \"%s\" %i\n", name.c_str(), o);
		
		if(o == -1) {
			c_ = c;
			break;
		}
		
		o_[c] = o;
	}
}



