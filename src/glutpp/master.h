#ifndef __GLUTPP_MASTER_H__
#define __GLUTPP_MASTER_H__

#include <map>

#include <GLFW/glfw3.h>

namespace glutpp
{
	class window;
	class master
	{
		private:

			static void static_window_pos_fun(GLFWwindow*,int,int);
			static void static_window_size_fun(GLFWwindow*,int,int);
			static void static_window_close_fun(GLFWwindow*);
			static void static_window_refresh_fun(GLFWwindow*);
			//static void static_window_focus_fun(GLFWwindow*,int);
			//static void static_window_iconify_fun(GLFWwindow*,int);
			//static void static_window_buffer_size_fun(GLFWwindow*,int,int);
			
			static void static_mouse_button_fun(GLFWwindow*,int,int,int);
			static void static_key_fun(GLFWwindow*,int,int,int,int);

			
		public:

			master();
			~master();

			glutpp::window*	get_window(GLFWwindow*);
			void		reg(glutpp::window*);


			//void  CallGlutCreateWindow(char * setTitle, glutpp::window * glutWindow);
			//void  CallGlutMainLoop(void);

			//void  DisableIdleFunction(void);
			//void  EnableIdleFunction(void);
			//int   IdleFunctionEnabled(void);

			//int   IdleSetToCurrentWindow(void);
			//void  SetIdleToCurrentWindow(void);
		private:
			GLFWwindow*				currentIdleWindow_;
			std::map<GLFWwindow*,glutpp::window*>	windows_;

	};

	extern "C" master __master;
}


#endif




