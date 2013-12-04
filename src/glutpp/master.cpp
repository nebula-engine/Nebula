#include <stdio.h>

#include <glutpp/master.h>
#include <glutpp/window.h>

glutpp::window * viewPorts[MAX_NUMBER_OF_WINDOWS]; 

int glutpp::master::currentIdleWindow   = 0;
int glutpp::master::idleFunctionEnabled = 0;

glutpp::master::master()
{
	// Create dummy variables 

	const char * dummy_argv[1];
	dummy_argv[0] = "run";
	int dummy_argc = 1;

	// Initialize GLUT

	glutInit( &dummy_argc, (char**)dummy_argv );



}
glutpp::master::~master()
{

}
void glutpp::master::CallBackDisplayFunc(void)
{
	int windowID = glutGetWindow();
	viewPorts[windowID]->CallBackDisplayFunc();
}
void glutpp::master::CallBackIdleFunc(void)
{
	if(idleFunctionEnabled && currentIdleWindow)
	{
		glutSetWindow(currentIdleWindow);
		viewPorts[currentIdleWindow]->CallBackIdleFunc();
	}
}
void glutpp::master::CallBackKeyboardFunc(unsigned char key, int x, int y)
{
	int windowID = glutGetWindow();
	viewPorts[windowID]->CallBackKeyboardFunc(key, x, y);
}
void glutpp::master::CallBackMotionFunc(int x, int y)
{
	int windowID = glutGetWindow();
	viewPorts[windowID]->CallBackMotionFunc(x, y);
}
void glutpp::master::CallBackMouseFunc(int button, int state, int x, int y)
{
	int windowID = glutGetWindow();
	viewPorts[windowID]->CallBackMouseFunc(button, state, x, y);
}
void glutpp::master::CallBackPassiveMotionFunc(int x, int y)
{
	int windowID = glutGetWindow();
	viewPorts[windowID]->CallBackPassiveMotionFunc(x, y);
}
void glutpp::master::CallBackReshapeFunc(int w, int h)
{
	int windowID = glutGetWindow();
	viewPorts[windowID]->CallBackReshapeFunc(w, h);
}
void glutpp::master::CallBackSpecialFunc(int key, int x, int y)
{
	int windowID = glutGetWindow();
	viewPorts[windowID]->CallBackSpecialFunc(key, x, y);
}   
void glutpp::master::CallBackVisibilityFunc(int visible)
{
	int windowID = glutGetWindow();
	viewPorts[windowID]->CallBackVisibilityFunc(visible);
}
void glutpp::master::CallGlutCreateWindow(char * setTitle, glutpp::window * glutWindow)
{

	// Open new window, record its windowID , 

	int windowID = glutCreateWindow(setTitle);

	glutWindow->SetWindowID(windowID);

	// Store the address of new window in global array 
	// so glutpp::master can send events to propoer callback functions.

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
void glutpp::master::CallGlutMainLoop(void)
{
	glutMainLoop();
}

void glutpp::master::DisableIdleFunction(void)
{
	idleFunctionEnabled = 0;
}
void glutpp::master::EnableIdleFunction(void)
{
	idleFunctionEnabled = 1;
}
int glutpp::master::IdleFunctionEnabled(void)
{
	// Is idle function enabled?

	return(idleFunctionEnabled);
}
int glutpp::master::IdleSetToCurrentWindow(void)
{
	// Is current idle window same as current window?

	return( currentIdleWindow == glutGetWindow() );
}
void glutpp::master::SetIdleToCurrentWindow(void)
{
	currentIdleWindow = glutGetWindow();
}

namespace glutpp
{
	master __master;
}


