
#include <PxPhysicsAPI.h>

#include <nebula/actor/Rigid_Dynamic_Box.hpp>

/*void	NEB::Actor::Rigid_Dynamic_Box::Display()
{

	//Create spheres list if necessary
	if(!list_)
	{
		list_ = glGenLists(1);
		glNewList(list_, GL_COMPILE);
		{

			
			//glColor3f(0.0f, 1.0f, 0.0f);
			GLfloat ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
			GLfloat diffuse[] = {1.0f, 0.0f, 0.0f, 1.0f};
			GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
			GLfloat shininess[] = {128.0f};

			glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
			//glMaterialfv(GL_FRONT, GL_EMISSION, color);
			glMaterialfv(GL_FRONT, GL_SHININESS, shininess);



			glPushMatrix();

			glTranslatef(0.45f, 1.0f, 0.45f);
			glutSolidSphere(0.2, 24, 24);

			glTranslatef(-0.9f, 0.0f, 0.0f);
			glutSolidSphere(0.2, 24, 24);

			glTranslatef(0.0f, 0.0f,-0.9f);
			glutSolidSphere(0.2, 24, 24);

			glTranslatef(0.9f, 0.0f, 0.0f);
			glutSolidSphere(0.2, 24, 24);

			glPopMatrix();

			GLfloat ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
			GLfloat diffuse[] = {1.0f, 0.0f, 0.0f, 1.0f};
			GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
			GLfloat shininess[] = {128.0f};


			//glMultMatrixf( mat.front() );

			glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
			//glMaterialfv(GL_FRONT, GL_EMISSION, color);
			glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

			glPushMatrix();
			{
				glutSolidCube(2.0f);
				//glutSolidTeapot(1.0f);
			}
			glPopMatrix();







		}
		glEndList();
	}




	physx::PxMat44 mat( pose_ );


	glPushMatrix();

	glMultMatrixf( mat.front() );

	glCallList(list_);

	glPopMatrix();


}*/


