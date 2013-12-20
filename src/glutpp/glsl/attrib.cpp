#include <stdio.h>

#include <GL/glew.h>

#include <glutpp/window.h>
#include <glutpp/glsl/attrib.h>

glutpp::glsl::attrib::attrib():
	o_(-1),
	o_bind_(-1)
{}
void	glutpp::glsl::attrib::init(char const * name, GLuint o_bind)
{
	name_ = name;
	o_bind_ = o_bind;
	
	printf("attrib %s\n",name_);
	
}
int	glutpp::glsl::attrib::locate(std::shared_ptr<glutpp::glsl::program> p)
{
	printf("program %i\n", p->o_);

	glBindAttribLocation(p->o_, o_bind_, name_);
	checkerror("glBindAttribLocation");
	
	o_ = glGetAttribLocation(p->o_, name_);
	
	checkerror("glGetAttribLocation");

	if(o_ == -1)
	{
		printf("could not find attrib '%s'\n", name_);
		exit(0);
	}

}
void	glutpp::glsl::attrib::enable()
{
	glEnableVertexAttribArray(o_);

	checkerror("glEnableVertexAttribArray");
}
void	glutpp::glsl::attrib::disable()
{
	glDisableVertexAttribArray(o_);

	checkerror("glDisableVertexAttribArray");
}

