#include <stdio.h>
#include <stdlib.h>

#include <GL/gl.h>

#include <glutpp/window.h>
#include <glutpp/plane.h>

glutpp::plane::plane(window* window):
	parallel_(1,0,0),
	plane_( math::vec3(0,1,0), 0 ),
	object(window)
{
	flags_ |= PLANAR_REFLECTION_STENCIL;
}
void	glutpp::plane::draw()
{
	printf("%s\n",__PRETTY_FUNCTION__);

	//glDisable(GL_LIGHTING);

	//if (useTexture) glEnable(GL_TEXTURE_2D);

	if(0)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	math::mat44 m;
	m.SetCoordinateTransform(parallel_, plane_.n);
	m.Invert();

	if(1)
	{	
		glPushMatrix();
		{
			//glMultMatrixf(pose_);

			glMaterialfv(GL_FRONT,GL_DIFFUSE,math::vec4(1.0,1.0,0.0,1.0));
			glMaterialfv(GL_FRONT,GL_AMBIENT,math::vec4(0.5,0.5,0.5,1.0));
			glMaterialfv(GL_FRONT,GL_SPECULAR,math::black);

			glMultMatrixf(m);

			glScalef(3.0f,1.0f,3.0f);

			glBegin(GL_QUADS);
			{
				glNormal3f(0.0f, 1.0f, 0.0f);
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
	}
	//if (useTexture) glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	//glEnable(GL_LIGHTING);
}
void	glutpp::plane::render_reflection()
{
	printf("%s\n",__PRETTY_FUNCTION__);

	if( flags_ & PLANAR_REFLECTION_STENCIL )
	{
		/* We can eliminate the visual "artifact" of seeing the "flipped"
		   dinosaur underneath the floor by using stencil.  The idea is
		   draw the floor without color or depth update but so that 
		   a stencil value of one is where the floor will be.  Later when
		   rendering the dinosaur reflection, we will only update pixels
		   with a stencil value of 1 to make sure the reflection only
		   lives on the floor, not below the floor. */

		/* Don't update color or depth. */
		glDisable(GL_DEPTH_TEST);
		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

		/* Draw 1 into the stencil buffer. */
		glEnable(GL_STENCIL_TEST);
		glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
		glStencilFunc(GL_ALWAYS, 1, 0xffffffff);

		/* Now render floor; floor pixels just get their stencil set to 1. */
		draw();

		/* Re-enable update of color and depth. */
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glEnable(GL_DEPTH_TEST);

		/* Now, only render where stencil is set to 1. */
		glStencilFunc(GL_EQUAL, 1, 0xffffffff);  /* draw if ==1 */
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	}

	glPushMatrix();
	{

		/* The critical reflection step: Reflect dinosaur through the floor
		   (the Y=0 plane) to make a relection. */
		math::mat44 reflect;
		reflect.SetReflection(plane_);
		glMultMatrixf(reflect);
		//glScalef(1.0, -1.0, 1.0);

		/* To avoid our normals getting reversed and hence botched lighting
		   on the reflection, turn on normalize.  */
		glEnable(GL_NORMALIZE);
		glCullFace(GL_FRONT);

		window_->lights_updateGL();

		window_->display_all_but(this);
		//window_->Display();

		/* Disable noramlize again and re-enable back face culling. */
		glDisable(GL_NORMALIZE);
		glCullFace(GL_BACK);
	}
	glPopMatrix();

	/* Switch back to the unreflected light position. */
	window_->lights_updateGL();
	//glLightfv(GL_LIGHT0, GL_POSITION, light_.camera_.eye_);

	if( flags_ & PLANAR_REFLECTION_STENCIL )
	{
		glDisable(GL_STENCIL_TEST);
	}
}

