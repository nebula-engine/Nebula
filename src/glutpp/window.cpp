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
#include <glutpp/shader.h>
#include <glutpp/program.h>

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
	width(setWidth),
	height(setHeight),
	initPositionX(setInitPositionX),
	initPositionY(setInitPositionY)
{
	printf("%s\n",__PRETTY_FUNCTION__);
	
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(initPositionX, initPositionY);

	glutpp::__master.CallGlutCreateWindow( (char *)title, this );

	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		exit(1);
	}
	
	if (!GLEW_VERSION_2_1)
	{
		printf("wrong glew version\n");
		exit(1);
	}

	//CheckExt();

	printf("%s\n",glGetString(GL_SHADING_LANGUAGE_VERSION));




	glEnable(GL_LIGHTING);

	//lights_enable();

	//Check for necessary extensions
	if(!GL_ARB_depth_texture || !GL_ARB_shadow)
	{
		printf("I require ARB_depth_texture and ARB_shadow extensionsn\n");
		exit(0);//return false;
	}

	//Shading states
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//Depth states

	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_NORMALIZE);


	// shaders
	shaders_ = new shader[2];
	program_ = new program;
	
	shaders_[0].load("/home/charles/usr/include/glutpp/shaders/prog1/vs.glsl", GL_VERTEX_SHADER);
	shaders_[1].load("/home/charles/usr/include/glutpp/shaders/prog1/fs.glsl", GL_FRAGMENT_SHADER);
	
	program_->init();
	program_->add_shader(shaders_+0);
	program_->add_shader(shaders_+1);
	program_->compile();
	program_->use();
	
	//Create the shadow map texture
	

	//Use the color as the ambient and diffuse material
	//glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	//glEnable(GL_COLOR_MATERIAL);
	
	checkerror("dadas");
}
glutpp::window::~window()
{
	glutDestroyWindow(windowID);
}
void	glutpp::window::lights_for_each(std::function<void(glutpp::light*)> func)
{
	for(int i = 0; i < lights_.size(); ++i)
	{
		func(lights_.at(i));
	}
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

	lights_for_each(&glutpp::light::dim);

	Display();
}
void	glutpp::window::display_bright()
{
	//3rd pass: Draw with bright light
	lights_for_each(&glutpp::light::updateGL);

	if( isset( PLANAR_REFLECTION ) ) RenderReflection();

	if( isset( SHADOW | SHADOW_TEXTURE ) ) lights_for_each(&glutpp::light::RenderShadow);

	Display();

	check_error();

	if( isset( SHADOW | SHADOW_TEXTURE ) ) lights_for_each(&glutpp::light::RenderShadowPost);
}
void glutpp::window::CallBackDisplayFunc()
{
	if( isset( SHADOW | SHADOW_TEXTURE ) ) lights_for_each(&glutpp::light::RenderLightPOV);

	//2nd pass - Draw from camera's point of view
	glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);

	//PrepRenderCamera(camera_);
	camera_.load();

	glEnable(GL_LIGHTING);

	if( isset( SHADOW | SHADOW_TEXTURE ) ) DisplayDim();

	display_bright();

	if( isset(ORTHO) ) RenderOrtho();

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
			toggle( SHADOW );
			break;
		case 'o':
			toggle( ORTHO );
			break;
		case 'r':
			toggle( PLANAR_REFLECTION | PLANAR_REFLECTION_STENCIL );
			break;
		case 27:
			exit(0);
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


void checkerror(char const * msg)
{
	GLenum err = glGetError();
	if(err != GL_NO_ERROR)
	{
		unsigned char const * str = gluErrorString(err);
		printf("%s: %s\n",msg,str);
		exit(0);
	}


}





