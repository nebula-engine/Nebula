//#include <GL/glew.h>
//#include <GL/glut.h>

#include <math/mat44.h>

#include <glutpp/uniform.h>

void	glutpp::uniform::init(GLuint program, char const * name)
{
//	location_ = glGetUniformLocation(program, name);
	//checkerror("glGetUniformLocation");
}
void	glutpp::uniform::load(math::mat44 m)
{
	glUniformMatrix4fv(location_,1,GL_FALSE,m);
}



