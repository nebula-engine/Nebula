#include <stdio.h>
#include <string.h>

//#include <GL/glew.h>
//#include <GL/glut.h>

#include <math/mat44.h>

#include <glutpp/uniform.h>
#include <glutpp/window.h>

glutpp::uniform::uniform(window* window, char const * name):
	window_(window)
{
	location_ = glGetUniformLocation(window_->program_->o_, name);
	
	printf("uniform %s %i\n",name,location_);
	
	checkerror("glGetUniformLocation");
}
glutpp::uniform::uniform(window* window, char const * struct_str, char const * name, int o):
	window_(window)
{
	char o_str[32];
	sprintf(o_str, "%i", o);
	
	char* fullname = new char[strlen(o_str) + strlen(struct_str) + strlen(name) + 4];
	
	strncpy(fullname,						struct_str, strlen(struct_str));
	memset(	fullname + strlen(struct_str),				'[', 1);
	strncpy(fullname + strlen(struct_str) + 1,			o_str, strlen(o_str));
	memset(	fullname + strlen(struct_str) + 1 + strlen(o_str),	']', 1);
	memset(	fullname + strlen(struct_str) + 1 + strlen(o_str) + 1,	'.', 1);
	strncpy(fullname + strlen(struct_str) + 1 + strlen(o_str) + 2,	name, strlen(name));

	fullname[strlen(struct_str) + 1 + strlen(o_str) + 2 + strlen(name)] = '\0';
	
	location_ = glGetUniformLocation(window_->program_->o_, fullname);
	
	printf("uniform %s %i\n",fullname,location_);
	
	checkerror("glGetUniformLocation");
}
void	glutpp::uniform::load(math::mat44 m)
{
	glUniformMatrix4fv(location_,1,GL_FALSE,m);

	checkerror("glUniformMatrix4fv");
}
void	glutpp::uniform::load_1i(int o)
{
	glUniform1i(location_, o);

	checkerror("glUniform1i");
}
void	glutpp::uniform::load_4fv(float* v)
{
	glUniform4fv(location_, 1, v);

	checkerror("glUniform4fv");
}
void	glutpp::uniform::load_3fv(float* v)
{
	glUniform3fv(location_, 1, v);

	checkerror("glUniform3fv");
}
void	glutpp::uniform::load_1f(float f)
{
	glUniform1f(location_, f);
	
	checkerror("glUniform1f");
}
void	glutpp::uniform::load_matrix4fv(float* v)
{
	glUniformMatrix4fv(location_,1,GL_FALSE,v);
	
	checkerror("glUniformMatrix4fv");
}

