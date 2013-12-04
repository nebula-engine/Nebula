#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>

#include <glutpp/window.h>
#include <glutpp/sphere.h>

glutpp::sphere::sphere()
{

}
void	glutpp::sphere::draw()
{
	printf("%s\n",__PRETTY_FUNCTION__);

	//glDisable(GL_LIGHTING);

	//if (useTexture) glEnable(GL_TEXTURE_2D);

	glMaterialfv(GL_FRONT, GL_AMBIENT, math::white);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, math::blue);
	glMaterialfv(GL_FRONT, GL_SPECULAR, math::white);
	glMaterialf(GL_FRONT, GL_SHININESS, 16.0f);

	glPushMatrix();
	{

		glTranslatef(0,0.5,0);
		glutSolidSphere(0.2,20,20);
		
	}
	glPopMatrix();

	//if (useTexture) glDisable(GL_TEXTURE_2D);

	//glEnable(GL_LIGHTING);
}

