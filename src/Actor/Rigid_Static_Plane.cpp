#include <GL/glut.h>

#include <NEB/Actor/Rigid_Static_Plane.h>

void NEB::Actor::Rigid_Static_Plane::Display()
{


	physx::PxMat44 mat( pose_ );

	if(!list_)
	{
		list_ = glGenLists(1);
		glNewList(list_, GL_COMPILE);
		{
			GLfloat ambient[] = {0.2f, 0.2f, 1.0f, 1.0f};
			GLfloat diffuse[] = {0.0f, 0.0f, 1.0f, 1.0f};
			GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
			GLfloat shininess[] = {128.0f};

			glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
			glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

			glPushMatrix();
			{

				glScalef(10.0f, 0.1f, 10.0f);
	
				glutSolidCube(1.0f);
/*
				glScalef(10.0f, 1.0f, 10.0f);

				glBegin(GL_QUADS);

				glNormal3f( 0.0f, 1.0f,  0.0f);

				glVertex3f(-0.5f, 0.0f,  0.5f);
				glVertex3f(-0.5f, 0.0f, -0.5f);
				glVertex3f( 0.5f, 0.0f, -0.5f);
				glVertex3f( 0.5f, 0.0f,  0.5f);
*/
				glEnd();
			}
			glPopMatrix();

		}
		glEndList();
	}

	// color




	glPushMatrix();

	glMultMatrixf( mat.front() );
	//glTranslatef(pose_.p.x, pose_.p.y, pose_.p.z);
	glCallList(list_);

	glPopMatrix();



}

