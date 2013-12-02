#include <GL/gl.h>

#include <glutpp/plane.h>

glutpp::plane::plane():
	plane_( math::vec3(0,1,0), 0 )
{
	
}
void	glutpp::plane::draw()
{
        glDisable(GL_LIGHTING);

        if (useTexture) glEnable(GL_TEXTURE_2D);

        glPushMatrix();

        {
                glMultMatrixf(pose_);
                glScalef(20.0f,1.0f,20.0f);

                glBegin(GL_QUADS);

                {
                        glTexCoord2f(0.0, 0.0);
                        glVertex3f(-0.5f,0.0f,-0.5f);

                        glTexCoord2f(0.0, 16.0);
                        glVertex3f(-0.5f,0.0f,0.5f);

                        glTexCoord2f(16.0, 16.0);
                        glVertex3f(0.5f,0.0f,0.5f);

                        glTexCoord2f(16.0, 0.0);
                        glVertex3f(0.5f,0.0f,-0.5f);
                }

                glEnd();

        }

        glPopMatrix();

        if (useTexture) glDisable(GL_TEXTURE_2D);

        glEnable(GL_LIGHTING);
}

