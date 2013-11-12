
#include <GRU/Master.h>
#include <GRU/Window.h>

GRU::Window * viewPorts[MAX_NUMBER_OF_WINDOWS]; 

int GRU::Master::currentIdleWindow   = 0;
int GRU::Master::idleFunctionEnabled = 0;

GRU::Master::Master()
{
	// Create dummy variables 
	
	const char * dummy_argv[1];
	dummy_argv[0] = "run";
	int dummy_argc = 1;
	
	// Initialize GLUT
	
	glutInit( &dummy_argc, (char**)dummy_argv );
}
GRU::Master::~Master()
{

}
void GRU::Master::CallBackDisplayFunc(void)
{
	int windowID = glutGetWindow();
	viewPorts[windowID]->CallBackDisplayFunc();
}
void GRU::Master::CallBackIdleFunc(void)
{
	if(idleFunctionEnabled && currentIdleWindow)
	{
		glutSetWindow(currentIdleWindow);
		viewPorts[currentIdleWindow]->CallBackIdleFunc();
	}
}
void GRU::Master::CallBackKeyboardFunc(unsigned char key, int x, int y)
{
	int windowID = glutGetWindow();
	viewPorts[windowID]->CallBackKeyboardFunc(key, x, y);
}
void GRU::Master::CallBackMotionFunc(int x, int y)
{
	int windowID = glutGetWindow();
	viewPorts[windowID]->CallBackMotionFunc(x, y);
}
void GRU::Master::CallBackMouseFunc(int button, int state, int x, int y)
{
	int windowID = glutGetWindow();
	viewPorts[windowID]->CallBackMouseFunc(button, state, x, y);
}
void GRU::Master::CallBackPassiveMotionFunc(int x, int y)
{
	int windowID = glutGetWindow();
	viewPorts[windowID]->CallBackPassiveMotionFunc(x, y);
}
void GRU::Master::CallBackReshapeFunc(int w, int h)
{
	int windowID = glutGetWindow();
	viewPorts[windowID]->CallBackReshapeFunc(w, h);
}
void GRU::Master::CallBackSpecialFunc(int key, int x, int y)
{
	int windowID = glutGetWindow();
	viewPorts[windowID]->CallBackSpecialFunc(key, x, y);
}   
void GRU::Master::CallBackVisibilityFunc(int visible)
{
	int windowID = glutGetWindow();
	viewPorts[windowID]->CallBackVisibilityFunc(visible);
}
void GRU::Master::CallGlutCreateWindow(char * setTitle, GRU::Window * glutWindow)
{

	// Open new window, record its windowID , 

	int windowID = glutCreateWindow(setTitle);

	glutWindow->SetWindowID(windowID);

	// Store the address of new window in global array 
	// so GRU::Master can send events to propoer callback functions.

	viewPorts[windowID] = glutWindow;

	// Hand address of universal static callback functions to Glut.
	// This must be for each new window, even though the address are constant.

	glutDisplayFunc(CallBackDisplayFunc);
	glutIdleFunc(CallBackIdleFunc); 
	glutKeyboardFunc(CallBackKeyboardFunc);
	glutSpecialFunc(CallBackSpecialFunc);
	glutMouseFunc(CallBackMouseFunc);
	glutMotionFunc(CallBackMotionFunc);
	glutPassiveMotionFunc(CallBackPassiveMotionFunc);
	glutReshapeFunc(CallBackReshapeFunc); 
	glutVisibilityFunc(CallBackVisibilityFunc);
}
void GRU::Master::CallGlutMainLoop(void)
{
	glutMainLoop();
}

void GRU::Master::DisableIdleFunction(void)
{
	idleFunctionEnabled = 0;
}
void GRU::Master::EnableIdleFunction(void)
{
	idleFunctionEnabled = 1;
}
int GRU::Master::IdleFunctionEnabled(void)
{
	// Is idle function enabled?

	return(idleFunctionEnabled);
}
int GRU::Master::IdleSetToCurrentWindow(void)
{
	// Is current idle window same as current window?

	return( currentIdleWindow == glutGetWindow() );
}
void GRU::Master::SetIdleToCurrentWindow(void)
{
	currentIdleWindow = glutGetWindow();
}

namespace GRU
{
	Master master;
}


