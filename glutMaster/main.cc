////////////////////////////////////////////////////////////////
//                                                            //
// main.c++                                                   //
// beta version 0.3 - 9/9/97)                                 //
//                                                            //
// George Stetten and Korin Crawford                          //
// copyright given to the public domain                       //
//                                                            //
// Please email comments to email@stetten.com,                //
//                                                            //
////////////////////////////////////////////////////////////////


#include "glutMaster.h"
#include "glutWindow.h"
#include "demoWindow.h"

GlutMaster     * glutMaster;
DemoWindow     * firstWindow       = 0;
DemoWindow     * secondWindow      = 0;

int	main(void)
{

	glutMaster   = new GlutMaster();    

	firstWindow  = new DemoWindow(glutMaster,
			200, 200,    // height, width
			200, 100,    // initPosition (x,y)
			"First Window"); // title

	secondWindow = new DemoWindow(glutMaster,
			500, 500,    // height, width
			200, 400,    // initPosition (x,y)
			"Second Window"); // title

	secondWindow->StartSpinning(glutMaster);   // enable idle function

	glutMaster->CallGlutMainLoop();

	return 0;
}


