#include <stdio.h>
#include <string.h>

#include <assert.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <GL/glut.h>

#include <math/mat44.hpp>

#include <gru/scene/scene.hpp>
#include <gru/glsl/uniform.hpp>
#include <gru/window/window.hpp>


glutpp::glsl::uniform::uniform()
{}
void	glutpp::glsl::uniform::init(char const * name)
{
	//printf("%s\n",__PRETTY_FUNCTION__);
	
	c_ = 1;
	
	s1_ = name;
	
	//printf("uniform %s\n",name_);
	
	checkerror("glGetUniformLocation");
	
	//locate();
}
void	glutpp::glsl::uniform::init(char const * s1, char const * s2, int c)
{
	//printf("%s\n",__PRETTY_FUNCTION__);
	
	c_ = c;
	
	s1_ = s1;
	s2_ = s2;
	
}
void	glutpp::glsl::uniform::locate(std::shared_ptr<glutpp::glsl::program> p)
{
	printf("%s\n",__PRETTY_FUNCTION__);

	assert(p);

	char o_str[8];
	char name[128];
	
	assert(s1_);
	
	if(c_ == 1)
	{
		o_[0] = glGetUniformLocation(p->o_, s1_);
	}
	else
	{
		assert(s2_);
		
		for(int c = 0; c < c_; c++)
		{
			sprintf(o_str, "%i", c);
			
			//printf("str = '%s' c = %i\n", o_str, c);

			name[0] = '\0';
			
			strcat(name, s1_);
			strcat(name, "[");
			strcat(name, o_str);
			strcat(name, "].");
			strcat(name, s2_);
			
			//printf("locate '%s'\n", name);

			o_[c] = glGetUniformLocation(p->o_, name);
		}
	}

}
void	glutpp::glsl::uniform::load(math::mat44 m) {

	glUniformMatrix4fv(o_[0],1,GL_FALSE,m);

	checkerror("glUniformMatrix4fv");
}
void	glutpp::glsl::uniform::load(math::color c) {

	glUniform4dv(o_[0], 1, c);
	
	checkerror("glUniformMatrix4fv");
}
void	glutpp::glsl::uniform::load(int o)
{
	glUniform1i(o_[0], o);

	checkerror("glUniform1i");
}
void	glutpp::glsl::uniform::load_4fv(double* v) {
	glUniform4dv(o_[0], 1, v);

	checkerror("glUniform4fv");
}
void	glutpp::glsl::uniform::load_3fv(double* v)
{
	glUniform3dv(o_[0], 1, v);

	checkerror("glUniform3fv");
}
void	glutpp::glsl::uniform::load(float f)
{
	glUniform1f(o_[0], f);

	checkerror("glUniform1f");
}
void	glutpp::glsl::uniform::load(int c, math::mat44 m) {

	glUniformMatrix4fv(o_[c],1,GL_FALSE,m);

	checkerror("glUniformMatrix4fv");
}
void	glutpp::glsl::uniform::load(int c, math::color color) {

	glUniform4dv(o_[c], 1, color);
	
	checkerror("glUniformMatrix4fv");
}
void	glutpp::glsl::uniform::load(int c, int o)
{
	glUniform1i(o_[c], o);

	checkerror("glUniform1i");
}
void	glutpp::glsl::uniform::load_4fv(int c, double* v)
{
	glUniform4dv(o_[c], 1, v);

	checkerror("glUniform4fv");
}
void	glutpp::glsl::uniform::load_3fv(int c, double* v)
{
	glUniform3dv(o_[c], 1, v);

	checkerror("glUniform3fv");
}
void	glutpp::glsl::uniform::load(int c, float f)
{
	glUniform1f(o_[c], f);

	checkerror("glUniform1f");
}





