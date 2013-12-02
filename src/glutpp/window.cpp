#include <string.h>
#include <stdio.h>

//#include <GLee.h>

#include <GL/glew.h>
#include <GL/glut.h>

#include <math/color.h>

#include <glutpp/free.h>
#include <glutpp/window.h>

void	check_error()
{
	GLenum errCode = glGetError();
	if (errCode != GL_NO_ERROR)
	{
		printf("%s\n",gluErrorString(errCode));
	}
}
glutpp::window::window(int setWidth, int setHeight,
		int setInitPositionX, int setInitPositionY,
		const char * title ):
	flags_(0),
	light_(GL_LIGHT0),
	width(setWidth),
	height(setHeight),
	initPositionX(setInitPositionX),
	initPositionY(setInitPositionY)
{
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(initPositionX, initPositionY);
	
	glEnable(GL_LIGHTING);
	glEnable(light_.o_);

	glutpp::__master.CallGlutCreateWindow( (char *)title, this );

	//Check for necessary extensions
	if(!GL_ARB_depth_texture || !GL_ARB_shadow)
	{
		printf("I require ARB_depth_texture and ARB_shadow extensionsn\n");
		exit(0);//return false;
	}

	//Shading states
	glShadeModel(GL_SMOOTH);
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//Depth states
	/*
	   glClearDepth(1.0f);
	   glDepthFunc(GL_LEQUAL);
	   */

	glEnable(GL_DEPTH_TEST);


	//We use glScale when drawing the scene
	glEnable(GL_NORMALIZE);

	//Create the shadow map texture
	//texture_shadow_map_.init(512,512);

	//Use the color as the ambient and diffuse material
	//glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	//glEnable(GL_COLOR_MATERIAL);
}
glutpp::window::~window()
{
	glutDestroyWindow(windowID);
}
void	glutpp::window::RenderLightPOV()
{
	//First pass - from light's point of view
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(light_.camera_.proj());

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(light_.camera_.view());

	//Use viewport the same size as the shadow map
	glViewport(0, 0, texture_shadow_map_.w_, texture_shadow_map_.h_);

	//Draw back faces into the shadow map
	glCullFace(GL_FRONT);

	//Disable color writes, and use flat shading for speed
	glShadeModel(GL_FLAT);
	glColorMask(0, 0, 0, 0);

	//Draw the scene
	//DrawScene(angle);
	Display();

	//Read the depth buffer into the shadow map texture
	texture_shadow_map_.bind();
	glCopyTexSubImage2D(
			GL_TEXTURE_2D,
			0, 0, 0, 0, 0,
			texture_shadow_map_.w_, texture_shadow_map_.h_);

	//restore states
	glCullFace(GL_BACK);
	glShadeModel(GL_SMOOTH);
	glColorMask(1, 1, 1, 1);


}
void	glutpp::window::RenderShadow()
{
	//Calculate texture matrix for projection
	//This matrix takes us from eye space to the light's clip space
	//It is postmultiplied by the inverse of the current view matrix when specifying texgen
	static math::mat44 biasMatrix(0.5f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.5f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.5f, 0.0f,
			0.5f, 0.5f, 0.5f, 1.0f);	//bias from [-1, 1] to [0, 1]

	math::mat44 textureMatrix = biasMatrix * light_.camera_.proj() * light_.camera_.view();

	//Set up texture coordinate generation.
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGenfv(GL_S, GL_EYE_PLANE, textureMatrix.GetRow(0));
	glEnable(GL_TEXTURE_GEN_S);

	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGenfv(GL_T, GL_EYE_PLANE, textureMatrix.GetRow(1));
	glEnable(GL_TEXTURE_GEN_T);

	glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGenfv(GL_R, GL_EYE_PLANE, textureMatrix.GetRow(2));
	glEnable(GL_TEXTURE_GEN_R);

	glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGenfv(GL_Q, GL_EYE_PLANE, textureMatrix.GetRow(3));
	glEnable(GL_TEXTURE_GEN_Q);

	//Bind & enable shadow map texture
	texture_shadow_map_.bind();
	glEnable(GL_TEXTURE_2D);

	//Enable shadow comparison
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE);

	//Shadow comparison should be true (ie not in shadow) if r<=texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);

	//Shadow comparison should generate an INTENSITY result
	glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE_ARB, GL_INTENSITY);

	//Set alpha test to discard false comparisons
	glAlphaFunc(GL_GEQUAL, 0.99f);
	glEnable(GL_ALPHA_TEST);

}
void	glutpp::window::RenderOrtho()
{
	//Restore other states
	glDisable(GL_LIGHTING);
	glDisable(GL_ALPHA_TEST);

	//Set matrices for ortho
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-1.0f, 1.0f, -1.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	DisplayOrtho();

	//Print text
	//glRasterPos2f(-1.0f, 0.9f);
	//for(unsigned int i=0; i<strlen(fpsString); ++i)
	//	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, fpsString[i]);

	//reset matrices
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

}
void	glutpp::window::RenderReflection()
{

	if(flags_ & PLANAR_REFLECTIONS_STENCIL)
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
		floor_.draw();

		/* Re-enable update of color and depth. */
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glEnable(GL_DEPTH_TEST);

		/* Now, only render where stencil is set to 1. */
		glStencilFunc(GL_EQUAL, 1, 0xffffffff);  /* draw if ==1 */
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	}

	glPushMatrix();


	/* The critical reflection step: Reflect dinosaur through the floor
	   (the Y=0 plane) to make a relection. */
	math::mat44 reflect;
	reflect.SetReflection(floor_.plane_);
	glLoadMatrixf(reflect);
	//glScalef(1.0, -1.0, 1.0);

	/* Reflect the light position. */
	glLightfv(GL_LIGHT0, GL_POSITION, light_.camera_.eye_);

	/* To avoid our normals getting reversed and hence botched lighting
	   on the reflection, turn on normalize.  */
	glEnable(GL_NORMALIZE);
	glCullFace(GL_FRONT);

	/* Draw the reflected dinosaur. */
	Display();

	/* Disable noramlize again and re-enable back face culling. */
	glDisable(GL_NORMALIZE);
	glCullFace(GL_BACK);

	glPopMatrix();

	/* Switch back to the unreflected light position. */
	glLightfv(GL_LIGHT0, GL_POSITION, light_.camera_.eye_);

	if(flags_ & PLANAR_REFLECTIONS_STENCIL)
	{
		glDisable(GL_STENCIL_TEST);
	}

}
void	glutpp::window::PrepRenderCamera(glutpp::camera c)
{
	glViewport(0, 0, width, height);

	math::mat44 proj = c.proj();
	math::mat44 view = c.view();

	//proj.print();
	//view.print();

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(proj);

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(view);	
}
void	glutpp::window::DisplayDim()
{
	glEnable(GL_LIGHTING);

	//Use dim light to represent shadowed areas
	light_.ambient_ = math::white*0.2f;
	light_.diffuse_ = math::white*0.2f;
	light_.specular_ = math::black;
	light_.updateGL();

	Display();
}
void	glutpp::window::PostRenderShadow()
{
	//Disable textures and texgen
	glDisable(GL_TEXTURE_2D);

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_GEN_Q);

}
void	glutpp::window::display_bright()
{
	//3rd pass: Draw with bright light
	light_.diffuse_ = math::white;
	light_.specular_ = math::white;
	light_.updateGL();

	//if( flags_ & PLANAR_REFLECTIONS ) RenderReflection();

	//if( ( flags_ & SHADOWS ) && ( flags_ & SHADOWS_TEXTURE ) ) RenderShadow();

	Display();

	check_error();

	//if( ( flags_ & SHADOWS ) && ( flags_ & SHADOWS_TEXTURE ) ) PostRenderShadow();
}
void glutpp::window::CallBackDisplayFunc(void)
{
	//if( ( flags_ & SHADOWS ) && ( flags_ & SHADOWS_TEXTURE ) ) RenderLightPOV();

	//2nd pass - Draw from camera's point of view
	glEnable(GL_LIGHTING);
	glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);

	PrepRenderCamera(camera_);

	//if( ( flags_ & SHADOWS ) && ( flags_ & SHADOWS_TEXTURE ) ) DisplayDim();

	display_bright();

	//if( flags_ & ORTHO) RenderOrtho();

	glFinish();
	glutSwapBuffers();
	glutPostRedisplay();
}
void glutpp::window::Reshape()
{
}
void glutpp::window::CallBackReshapeFunc(int w, int h)
{
	width = w;
	height = h;

	glViewport(0,0,width,height);

	camera_.w_ = width;
	camera_.h_ = height;

	CallBackDisplayFunc();
}
void glutpp::window::CallBackIdleFunc(void)
{
	Idle();

	CallBackDisplayFunc();
}
void glutpp::window::StartSpinning()
{
	glutpp::__master.SetIdleToCurrentWindow();
	glutpp::__master.EnableIdleFunction();
}
void glutpp::window::CallBackKeyboardFunc(unsigned char key, int x, int y)
{
	printf("%s\n",__FUNCTION__);

	switch(key)
	{
		case 's':
			flags_ &= !SHADOWS;
			break;
		case 'o':
			flags_ &= !ORTHO;
			break;

	}
	//key; x; y;                //dummy function
}
void glutpp::window::CallBackMotionFunc(int x, int y)
{
	//x; y;                     //dummy function
}
void glutpp::window::CallBackMouseFunc(int button, int state, int x, int y)
{
	//button; state; x; y;      //dummy function
}
void glutpp::window::CallBackPassiveMotionFunc(int x, int y)
{
	//x; y;                     //dummy function
}
void glutpp::window::CallBackSpecialFunc(int key, int x, int y)
{
	//key; x; y;
}   
void glutpp::window::CallBackVisibilityFunc(int visible)
{
	//visible;                  //dummy function
}
void glutpp::window::SetWindowID(int newWindowID)
{
	windowID = newWindowID;
}
int glutpp::window::GetWindowID(void)
{
	return( windowID );
}

void glutpp::window::Display()
{}   
void glutpp::window::DisplayOrtho()
{}   
void glutpp::window::Idle()
{}   







