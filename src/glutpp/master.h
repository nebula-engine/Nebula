#ifndef __GLUTPP_MASTER_H__
#define __GLUTPP_MASTER_H__

#include <GLFW/glfw3.h>

namespace glutpp
{
	class window;
	class master
	{
		private:

			static void CallBackDisplayFunc(void);
			static void CallBackIdleFunc(void); 
			static void CallBackKeyboardFunc(unsigned char key, int x, int y);
			static void CallBackKeyboardUpFunc(unsigned char key, int x, int y);

			static void CallBackMotionFunc(int x, int y);
			static void CallBackMouseFunc(int button, int state, int x, int y);
			static void CallBackPassiveMotionFunc(int x, int y);
			static void CallBackReshapeFunc(int w, int h); 
			static void CallBackSpecialFunc(int key, int x, int y);   
			static void CallBackVisibilityFunc(int visible);

			static int idleFunctionEnabled;

		public:
			
			master();
			~master();

			void  CallGlutCreateWindow(char * setTitle, glutpp::window * glutWindow);
			void  CallGlutMainLoop(void);

			void  DisableIdleFunction(void);
			void  EnableIdleFunction(void);
			int   IdleFunctionEnabled(void);

			int   IdleSetToCurrentWindow(void);
			void  SetIdleToCurrentWindow(void);
		private:
			GLFWwindow*				currentIdleWindow_;
			std::map<GLFWwindow*,glutpp::window*>	windows_;

	};
	
	extern "C" master __master;
}


#endif




