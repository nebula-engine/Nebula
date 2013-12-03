#include <glutpp/uniform.h>

void	glutpp::uniform::load(math::mat44 m)
{
	glUniformMatrix4fv(o_,len_,GL_FALSE,m);
}



