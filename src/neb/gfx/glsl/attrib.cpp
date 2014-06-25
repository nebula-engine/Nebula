#include <stdio.h>

#include <GL/glew.h>


#include <neb/gfx/glsl/attrib.hh>
#include <neb/free.hh>
#include <neb/gfx/glsl/program.hh>

neb::glsl::attrib::attrib():
	o_(-1),
	o_bind_(-1)
{}
void	neb::glsl::attrib::init(char const * name, GLuint o_bind)
{
	name_ = name;
	o_bind_ = o_bind;
	
	printf("attrib %s\n",name_);
	
}
int	neb::glsl::attrib::locate(std::shared_ptr<neb::glsl::program> p) {
	glBindAttribLocation(p->o_, o_bind_, name_);
	checkerror("glBindAttribLocation");
	
	o_ = glGetAttribLocation(p->o_, name_);
	
	checkerror("glGetAttribLocation");

	/*
	if(o_ == -1)
	{
		printf("could not find attrib '%s'\n", name_);
		exit(0);
	}
	*/
	return o_;
}
void	neb::glsl::attrib::enable()
{
	glEnableVertexAttribArray(o_);

	checkerror("glEnableVertexAttribArray");
}
void	neb::glsl::attrib::disable()
{
	glDisableVertexAttribArray(o_);

	checkerror("glDisableVertexAttribArray");
}

