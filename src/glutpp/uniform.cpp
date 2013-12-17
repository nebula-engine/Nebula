#include <stdio.h>
#include <string.h>

#include <assert.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <GL/glut.h>

#include <math/mat44.h>

#include <glutpp/scene.h>
#include <glutpp/uniform.h>
#include <glutpp/window.h>


glutpp::uniform::uniform()
{}
void	glutpp::uniform::init(std::shared_ptr<scene> scene, char const * name)
{
	//printf("%s\n",__PRETTY_FUNCTION__);
	
	scene_ = scene;
	
	strcpy(name_,name);
	
	//printf("uniform %s\n",name_);
	
	checkerror("glGetUniformLocation");
	
	locate();
}
void	glutpp::uniform::init(std::shared_ptr<scene> scene, char const * struct_str, char const * name, int o)
{
	//printf("%s\n",__PRETTY_FUNCTION__);

	scene_ = scene;
	
	char o_str[32];
	sprintf(o_str, "%i", o);
	
	name_[0] = '\0';
	
	strcat(name_, struct_str);
	strcat(name_, "[");
	strcat(name_, o_str);
	strcat(name_, "].");
	strcat(name_, name);
	
	//printf("uniform %s\n",name_);
	
	checkerror("glGetUniformLocation");
	
	locate();
}
void	glutpp::uniform::locate()
{
	printf("%s\n",__PRETTY_FUNCTION__);

	assert(name_);
	
	GLint p = scene_.lock()->get_program();
	
	if(p > 0) location_ = glGetUniformLocation(p, name_);
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

