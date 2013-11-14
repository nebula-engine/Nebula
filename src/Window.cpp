#include <GL/glut.h>

#include <GRU/Window.h>

GRU::Window::Window( GRU::Master * glutMaster,
		int setWidth, int setHeight,
		int setInitPositionX, int setInitPositionY,
		const char * title )
{
	width  = setWidth;               
	height = setHeight;

	initPositionX = setInitPositionX;
	initPositionY = setInitPositionY;

	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(initPositionX, initPositionY);
	//glViewport(0, 0, width, height);   // This may have to be moved to after the next line on some platforms

	glutMaster->CallGlutCreateWindow( (char *)title, this );

	// Settings
	glEnable(GL_DEPTH_TEST);
        glEnable( GL_NORMALIZE );
        glEnable( GL_LIGHTING );
	
        glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
	
        glEnable (GL_LIGHT0);
        glShadeModel (GL_SMOOTH); 

	// Setup viewport
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//glOrtho(-80.0, 80.0, -80.0, 80.0, -500.0, 500.0);
	gluPerspective(54.0, (GLdouble)width/(GLdouble)height, 1.0, 1000.0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	//glRotatef(60, 1, 1, 1);
	//glColor4f(1.0, 0.0, 0.0, 1.0);
	
	
	
}
GRU::Window::~Window()
{
	glutDestroyWindow(windowID);
}
void GRU::Window::CallBackDisplayFunc(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glColor4f(1.0, 0.0, 0.0, 1.0);
	//glutWireSphere(50, 10, 10);
	
	glLoadIdentity();
	
	if( CallBackDisplay_ )
	{
		CallBackDisplay_();
	}
	
	glutSwapBuffers();
}
void GRU::Window::Reshape()
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	//glOrtho(-80.0, 80.0, -80.0, 80.0, -500.0, 500.0);

	gluPerspective(54.0, (GLdouble)width/(GLdouble)height, 1.0, 1000.0);
	
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
}
void GRU::Window::CallBackReshapeFunc(int w, int h)
{
	width = w;
	height= h;

	Reshape();

	CallBackDisplayFunc();
}
void GRU::Window::CallBackIdleFunc(void)
{
	if( CallBackIdle_ )
	{
		CallBackIdle_();
	}
	
	CallBackDisplayFunc();
}
void GRU::Window::StartSpinning()
{
	GRU::master.SetIdleToCurrentWindow();
	GRU::master.EnableIdleFunction();
}
void GRU::Window::CallBackKeyboardFunc(unsigned char key, int x, int y)
{
	//key; x; y;                //dummy function
}
void GRU::Window::CallBackMotionFunc(int x, int y)
{
	//x; y;                     //dummy function
}
void GRU::Window::CallBackMouseFunc(int button, int state, int x, int y)
{
	//button; state; x; y;      //dummy function
}
void GRU::Window::CallBackPassiveMotionFunc(int x, int y)
{
	//x; y;                     //dummy function
}
void GRU::Window::CallBackSpecialFunc(int key, int x, int y)
{
	//key; x; y;
}   
void GRU::Window::CallBackVisibilityFunc(int visible)
{
	//visible;                  //dummy function
}
void GRU::Window::SetWindowID(int newWindowID)
{
	windowID = newWindowID;
}
int GRU::Window::GetWindowID(void)
{
	return( windowID );
}








