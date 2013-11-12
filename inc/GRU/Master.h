#ifndef __GRU_MASTER_H__
#define __GRU_MASTER_H__

#include <GL/glut.h>


#define MAX_NUMBER_OF_WINDOWS 256 

namespace GRU
{
	class Window;

	class Master
	{
		private:

			static void CallBackDisplayFunc(void);
			static void CallBackIdleFunc(void); 
			static void CallBackKeyboardFunc(unsigned char key, int x, int y);
			static void CallBackMotionFunc(int x, int y);
			static void CallBackMouseFunc(int button, int state, int x, int y);
			static void CallBackPassiveMotionFunc(int x, int y);
			static void CallBackReshapeFunc(int w, int h); 
			static void CallBackSpecialFunc(int key, int x, int y);   
			static void CallBackVisibilityFunc(int visible);

			static int currentIdleWindow;
			static int idleFunctionEnabled;

		public:
			
			Master();
			~Master();

			void  CallGlutCreateWindow(char * setTitle, GRU::Window * glutWindow);
			void  CallGlutMainLoop(void);

			void  DisableIdleFunction(void);
			void  EnableIdleFunction(void);
			int   IdleFunctionEnabled(void);

			int   IdleSetToCurrentWindow(void);
			void  SetIdleToCurrentWindow(void);
	};
	
	extern "C" Master master;
}


#endif




