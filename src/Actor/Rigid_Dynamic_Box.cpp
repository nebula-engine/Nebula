#include <GL/gl.h>
#include <GL/glut.h>

#include <PxPhysicsAPI.h>

#include <NEB/Actor/Rigid_Dynamic_Box.h>

void	NEB::Actor::Rigid_Dynamic_Box::Display()
{
	physx::PxMat44 mat( pose_ );
	
	
	
	glPushMatrix();
	
	glMultMatrixf( mat.front() );
	
	glColor4f(1,0,0,1);
	glutSolidCube(1.0);
	
	glPopMatrix();
	
	
}


