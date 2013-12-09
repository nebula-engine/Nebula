#include <GL/glut.h>

#include <NEB/Actor/Light.h>

void NEB::Actor::Light::Display()
{
	//fprintf(stderr, "%s\n", __FUNCTION__);
	
	GLfloat ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat diffuse[] = { 1.0, 1.0, 1.0 };
	GLfloat pos[] =     { 0.0, 5.0, 5.0, 1.0 };

	glLightfv( GL_LIGHT0, GL_POSITION, pos );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuse );
	glLightfv( GL_LIGHT0, GL_AMBIENT, ambient );


}

