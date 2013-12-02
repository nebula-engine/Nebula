#include <stdio.h>
#include <stdlib.h>

#include <GL/gl.h>

#include <glutpp/window.h>
#include <glutpp/sphere.h>

glutpp::sphere::sphere(window* window):
	object(window)
{

}
void	glutpp::sphere::draw()
{
	printf("%s\n",__FUNCTION__);

	//glDisable(GL_LIGHTING);

	//if (useTexture) glEnable(GL_TEXTURE_2D);

	glMaterialfv(GL_FRONT, GL_AMBIENT, math::white);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, math::blue);
	glMaterialfv(GL_FRONT, GL_SPECULAR, math::white);
	glMaterialf(GL_FRONT, GL_SHININESS, 16.0f);

	glPushMatrix();
	{

		glTranslatef(0,1,0);
		glutSolidSphere(0.5,20,20);
		
	}
	glPopMatrix();

	//if (useTexture) glDisable(GL_TEXTURE_2D);

	//glEnable(GL_LIGHTING);
}
/*void	glutpp::plane::render_reflection()
  {
  printf("%s\n",__FUNCTION__);

  if(0)//flags_ & PLANAR_REFLECTIONS_STENCIL)
  {*/
/* We can eliminate the visual "artifact" of seeing the "flipped"
   dinosaur underneath the floor by using stencil.  The idea is
   draw the floor without color or depth update but so that 
   a stencil value of one is where the floor will be.  Later when
   rendering the dinosaur reflection, we will only update pixels
   with a stencil value of 1 to make sure the reflection only
   lives on the floor, not below the floor. */
/*
// Don't update color or depth.
glDisable(GL_DEPTH_TEST);
glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

// Draw 1 into the stencil buffer. 
glEnable(GL_STENCIL_TEST);
glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
glStencilFunc(GL_ALWAYS, 1, 0xffffffff);

// Now render floor; floor pixels just get their stencil set to 1. 
draw();

// Re-enable update of color and depth. 
glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
glEnable(GL_DEPTH_TEST);

// Now, only render where stencil is set to 1. 
glStencilFunc(GL_EQUAL, 1, 0xffffffff);  *//* draw if ==1 *//*
							       glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
							       }

							       glPushMatrix();
							       {

// The critical reflection step: Reflect dinosaur through the floor
// (the Y=0 plane) to make a relection. */
/*		math::mat44 reflect;
		reflect.SetReflection(plane_);
		glLoadMatrixf(reflect);
 */		//glScalef(1.0, -1.0, 1.0);

/* To avoid our normals getting reversed and hence botched lighting
   on the reflection, turn on normalize.  */
/*		glEnable(GL_NORMALIZE);
		glCullFace(GL_FRONT);


		window_->lights_updateGL();
 */		/* Reflect the light position. */
//glLightfv(GL_LIGHT0, GL_POSITION, light_.camera_.eye_);

/* Draw the reflected dinosaur. */
/*		window_->Display();


 */		/* Disable noramlize again and re-enable back face culling. */
/*		glDisable(GL_NORMALIZE);
		glCullFace(GL_BACK);
		}
		glPopMatrix();

// Switch back to the unreflected light position.
window_->lights_updateGL();
//glLightfv(GL_LIGHT0, GL_POSITION, light_.camera_.eye_);

if(0)//flags_ & PLANAR_REFLECTIONS_STENCIL)
{
glDisable(GL_STENCIL_TEST);
}
}
 */
