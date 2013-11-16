#include <GL/gl.h>
#include <GL/glut.h>

#include <PxPhysicsAPI.h>

#include <NEB/Actor/Rigid_Dynamic_Box.h>

void	NEB::Actor::Rigid_Dynamic_Box::Display()
{
	physx::PxMat44 mat( pose_ );
	
	GLfloat diffuse[] = {1.0f, 0.0f, 0.0f, 1.0f};
	GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat shininess[] = {128.0f};
	
	glPushMatrix();
	
	glMultMatrixf( mat.front() );
	
	//glMaterialfv(GL_FRONT, GL_AMBIENT, color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	//glMaterialfv(GL_FRONT, GL_EMISSION, color);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	
	
	glutSolidCube(1.0f);
	//glutSolidTeapot(1.0f);
	
	glPopMatrix();
	
	
}


