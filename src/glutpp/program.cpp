
#include <GL/glew.h>
#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

#include <glutpp/program.h>
#include <glutpp/shader.h>

glutpp::program::program()
{
	o_ = glCreateProgram();
}
void	glutpp::program::add_shader(glutpp::shader* s)
{
	glAttachShader(o_, s->o_);
}
void	glutpp::program::compile()
{
	// Link The Program Object
	glLinkProgram(o_);
	
	GLint blen = 0;	
	GLsizei slen = 0;
	
	glGetProgramiv(o_, GL_INFO_LOG_LENGTH , &blen);

	if (blen > 1)
	{
		GLchar* compiler_log = (GLchar*)malloc(blen);

		glGetInfoLogARB(o_, blen, &slen, compiler_log);
		printf("compiler_log:%s\n", compiler_log);
		free (compiler_log);
	}

	printf("program=%i\n",o_);

}

