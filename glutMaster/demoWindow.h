////////////////////////////////////////////////////////////////
//                                                            //
// demoWindow.h                                               //
// beta version 0.3 - 9/9/97)                                 //
//                                                            //
// George Stetten and Korin Crawford                          //
// copyright given to the public domain                       //
//                                                            //
// Please email comments to email@stetten.com                 //
//                                                            //
////////////////////////////////////////////////////////////////


#ifndef __DEMO_WINDOW_H__
#define __DEMO_WINDOW_H__

#include "glutMaster.h"

class DemoWindow : public GlutWindow
{
public:

   int          height, width;
   int          initPositionX, initPositionY;

   DemoWindow(GlutMaster * glutMaster,
              int setWidth, int setHeight,
              int setInitPositionX, int setInitPositionY,
              char * title);
   ~DemoWindow();

   void CallBackDisplayFunc(void);
   void CallBackReshapeFunc(int w, int h);   
   void CallBackIdleFunc(void);

   void StartSpinning(GlutMaster * glutMaster);
};

#endif

