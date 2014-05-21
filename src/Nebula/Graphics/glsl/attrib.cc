#include <stdio.h>

#include <GL/glew.h>


#include <Nebula/Graphics/glsl/attrib.hh>
#include <Nebula/free.hh>
#include <Nebula/Graphics/glsl/program.hh>

Neb::glsl::attrib::attrib():
	o_(-1),
	o_bind_(-1)
{}
void	Neb::glsl::attrib::init(char const * name, GLuint o_bind)
{
	name_ = name;
	o_bind_ = o_bind;
	
	printf("attrib %s\n",name_);
	
}
int	Neb::glsl::attrib::locate(std::shared_ptr<Neb::glsl::program> p) {
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
void	Neb::glsl::attrib::enable()
{
	glEnableVertexAttribArray(o_);

	checkerror("glEnableVertexAttribArray");
}
void	Neb::glsl::attrib::disable()
{
	glDisableVertexAttribArray(o_);

	checkerror("glDisableVertexAttribArray");
}

