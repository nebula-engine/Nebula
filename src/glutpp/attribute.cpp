#include <stdio.h>

#include <GL/glew.h>

#include <glutpp/window.h>
#include <glutpp/attribute.h>

glutpp::attribute::attribute():
	window_(NULL),
	o_(-1)
{}
void	glutpp::attribute::init(std::shared_ptr<scene> scene, int o, char const * name)
{
	o_ = o;
	name_ = name;

	printf("attribute %s\n",name_);

	GLint program;
	glGetIntegerv(GL_CURRENT_PROGRAM,&program);

	printf("program %i\n",program);

	//o_ = glGetAttribLocation(program, name_);

	checkerror("glGetAttribLocation");

	if(o_ == -1)
	{
		printf("could not find attribute '%s'\n", name_);
		//exit(0);
	}
}
void	glutpp::attribute::enable()
{
	glEnableVertexAttribArray(o_);

	checkerror("glEnableVertexAttribArray");
}
void	glutpp::attribute::disable()
{
	glDisableVertexAttribArray(o_);

	checkerror("glDisableVertexAttribArray");
}

