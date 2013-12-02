#include <stdio.h>
#include <glutpp/light.h>

glutpp::light::light(GLenum o):
	o_(o),
	ambient_(math::black),
	diffuse_(math::white),
	specular_(math::white)
{
	printf("%s\n",__FUNCTION__);
	printf("GL_LIGHT %i\n",o_ - GL_LIGHT0);

	glEnable(GL_LIGHTING);
	glEnable(o_);
	
	updateGL();
}
void	glutpp::light::updateGL()
{
	//printf("diffuse\n");
	//diffuse_.print();
	
	glLightfv(o_, GL_POSITION, camera_.eye_);
	glLightfv(o_, GL_AMBIENT, ambient_);
	glLightfv(o_, GL_DIFFUSE, diffuse_);
	glLightfv(o_, GL_SPECULAR, specular_);	
}

