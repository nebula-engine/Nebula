
#include <GL/glew.h>
#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

#include <glutpp/program.h>
#include <glutpp/shader.h>
#include <glutpp/window.h>

glutpp::program::program()
{
}
void	glutpp::program::init()
{
	printf("%s\n",__PRETTY_FUNCTION__);

	o_ = glCreateProgram();
	checkerror("glCreateProgram");
}
void	glutpp::program::add_shaders(glutpp::shader* s,int c)
{
	printf("%s\n",__PRETTY_FUNCTION__);
	
	for(int i = 0; i < c; ++i )
	{
		printf("shader %i attached to program %i\n",s[i].o_,o_);
		
		glAttachShader(o_, s[i].o_);
		checkerror("glAttachShader");
	}
}
void	glutpp::program::compile()
{
	printf("%s\n",__PRETTY_FUNCTION__);
	
	glLinkProgram(o_);
	checkerror("glLinkProgram");
	
	GLint blen = 0;	
	GLsizei slen = 0;
	
	glGetProgramiv(o_, GL_INFO_LOG_LENGTH , &blen);
	
	checkerror("glGetProgramiv");

	if (blen > 1)
	{
		GLchar* compiler_log = (GLchar*)malloc(blen);

		glGetInfoLogARB(o_, blen, &slen, compiler_log);
		printf("compiler_log:%s\n", compiler_log);
		free (compiler_log);
	}

	printf("program=%i\n",o_);

}
void	glutpp::program::use()
{
	printf("%s\n",__PRETTY_FUNCTION__);
	
	glUseProgram(o_);
	checkerror("glUseProgram");
}



