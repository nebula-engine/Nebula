#include <GL/glut.h>

#include <NEB/Actor/Rigid_Static_Plane.h>

void NEB::Actor::Rigid_Static_Plane::Display()
{
	physx::PxMat44 mat( pose_ );

	// color
	GLfloat diffuse[] = {0.0f, 0.0f, 1.0f, 1.0f};
	GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};

	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);



	glPushMatrix();

	glMultMatrixf( mat.front() );

	glScalef(100.0f, 1.0f, 100.0f);

	glBegin(GL_QUADS);

	glNormal3f( 0.0f, 1.0f,  0.0f);

	glVertex3f(-0.5f, 0.0f,  0.5f);
	glVertex3f(-0.5f, 0.0f, -0.5f);
	glVertex3f( 0.5f, 0.0f, -0.5f);
	glVertex3f( 0.5f, 0.0f,  0.5f);

	glEnd();

	glPopMatrix();



}

