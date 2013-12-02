#include <string.h>
#include <stdio.h>

//#include <GLee.h>

#include <GL/glew.h>
#include <GL/glut.h>

#include <math/color.h>

#include <glutpp/free.h>
#include <glutpp/window.h>
#include <glutpp/object.h>
#include <glutpp/light.h>



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
	width(setWidth),
	height(setHeight),
	initPositionX(setInitPositionX),
	initPositionY(setInitPositionY)
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(initPositionX, initPositionY);
	

	glutpp::__master.CallGlutCreateWindow( (char *)title, this );

	glEnable(GL_LIGHTING);
	
	lights_enable();

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

	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	//We use glScale when drawing the scene
	glEnable(GL_NORMALIZE);

	//Create the shadow map texture


	//Use the color as the ambient and diffuse material
	//glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	//glEnable(GL_COLOR_MATERIAL);
}
glutpp::window::~window()
{
	glutDestroyWindow(windowID);
}
void	glutpp::window::lights_enable()
{
	for(auto it = objects_.begin(); it != objects_.end(); ++it )
	{
		object* o = *it;
		if( o->type_ == glutpp::object::LIGHT )
		{
			light* l = (light*)o;
			glEnable(l->o_);
		}
	};
}
void	glutpp::window::lights_updateGL()
{
	for(auto it = objects_.begin(); it != objects_.end(); ++it )
	{
		object* o = *it;
		if( o->type_ == glutpp::object::LIGHT )
		{
			light* l = (light*)o;
			l->updateGL();
		}
	};
}
void	glutpp::window::lights_dim()
{
	for(auto it = objects_.begin(); it != objects_.end(); ++it )
	{
		object* o = *it;
		if( o->type_ == glutpp::object::LIGHT )
		{
			light* l = (light*)o;
			l->dim();
		}
	};
}
void	glutpp::window::RenderLightPOV()
{
	for(auto it = objects_.begin(); it != objects_.end(); ++it )
	{
		object* o = *it;
		if( o->type_ == glutpp::object::LIGHT )
		{
			light* l = (light*)o;
			l->RenderLightPOV();
		}
	};

}
void	glutpp::window::RenderShadow()
{
	for(auto it = objects_.begin(); it != objects_.end(); ++it )
	{
		object* o = *it;
		if( o->type_ == glutpp::object::LIGHT )
		{
			light* l = (light*)o;
			l->RenderShadow();
		}
	};

}
void	glutpp::window::PostRenderShadow()
{
	for(auto it = objects_.begin(); it != objects_.end(); ++it )
	{
		object* o = *it;
		if( o->type_ == glutpp::object::LIGHT )
		{
			light* l = (light*)o;
			l->RenderShadowPost();
		}
	};

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
	for( auto it = objects_.begin(); it != objects_.end(); ++it )
	{
		(*it)->render_reflection();
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
	//glLoadIdentity();
	//gluPerspective(65.0f, (float)width/(float)height, 2.0f, 50.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(view);	
	//glLoadIdentity();
	//gluLookAt(0,5,5,0,0,0,0,1,0);
}
void	glutpp::window::DisplayDim()
{
	//glEnable(GL_LIGHTING);

	lights_dim();

	Display();
}
void	glutpp::window::display_bright()
{
	//3rd pass: Draw with bright light
	lights_updateGL();

	if( flags_ & PLANAR_REFLECTION ) RenderReflection();

	if( ( flags_ & SHADOW ) && ( flags_ & SHADOW_TEXTURE ) ) RenderShadow();

	Display();

	check_error();

	if( ( flags_ & SHADOW ) && ( flags_ & SHADOW_TEXTURE ) ) PostRenderShadow();
}
void glutpp::window::CallBackDisplayFunc()
{
	if( ( flags_ & SHADOW ) && ( flags_ & SHADOW_TEXTURE ) ) RenderLightPOV();

	//2nd pass - Draw from camera's point of view
	glEnable(GL_LIGHTING);
	glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);

	PrepRenderCamera(camera_);

	if( ( flags_ & SHADOW ) && ( flags_ & SHADOW_TEXTURE ) ) DisplayDim();

	display_bright();

	if( flags_ & ORTHO) RenderOrtho();

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
			flags_ &= !SHADOW;
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
{
	for( auto it = objects_.begin(); it != objects_.end(); ++it )
	{
		(*it)->draw();
	}
}
void	glutpp::window::display_all_but(object* o)
{
	for( auto it = objects_.begin(); it != objects_.end(); ++it )
	{
		if( (*it) != o ) (*it)->draw();
	}
}     
void glutpp::window::DisplayOrtho()
{}   
void glutpp::window::Idle()
{}   







