#include <stdio.h>

#include <GL/glew.h>

#include <glutpp/window.h>
#include <glutpp/glsl/attrib.h>

glutpp::glsl::attrib::attrib():
	o_(-1)
{}
void	glutpp::glsl::attrib::init(char const * name)
{
	name_ = name;

	printf("attrib %s\n",name_);

	GLint program;
	glGetIntegerv(GL_CURRENT_PROGRAM,&program);

	printf("program %i\n",program);

}
int	glutpp::glsl::attrib::locate(std::shared_ptr<glutpp::glsl::program> p)
{
	o_ = glGetAttribLocation(p->o_, name_);
	
	checkerror("glGetAttribLocation");

	if(o_ == -1)
	{
		printf("could not find attrib '%s'\n", name_);
		//exit(0);
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

