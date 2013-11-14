#include <GL/glut.h>

#include <NEB/Actor/Rigid_Static_Plane.h>

void NEB::Actor::Rigid_Static_Plane::Display()
{
	physx::PxMat44 mat( pose_ );
	
	glPushMatrix();
	
	glMultMatrixf( mat.front() );
	
	glColor4f(1,0,0,1);

	glBegin(GL_QUADS);
	
	glNormal3f( 0.0f, 1.0f,  0.0f);

	glVertex3f(-0.5f, 0.0f,  0.5f);
	glVertex3f(-0.5f, 0.0f, -0.5f);
	glVertex3f( 0.5f, 0.0f, -0.5f);
	glVertex3f( 0.5f, 0.0f,  0.5f);
	
	glEnd();
	
	glPopMatrix();
	
	
	
}

