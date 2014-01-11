#ifndef __GLUTPP_MASTER_H__
#define __GLUTPP_MASTER_H__

#include <map>
#include <memory>

#include <gal/flag.h>
#include <gal/sig/signal.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <GLFW/glfw3.h>

#include <glutpp/config.h>


namespace glutpp
{
	class master: public gal::flag<>
	{
		public:
			enum option
			{
				//SHADERS = 1 << 0
			};
		private:
			static void static_error_fun(int,char const *);
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
			std::shared_ptr<glutpp::glsl::program>		use_program(glutpp::program_name::e);
			std::shared_ptr<glutpp::glsl::program>		get_program(glutpp::program_name::e);
			std::shared_ptr<glutpp::glsl::program>		current_program();
			int						create_programs();



		public:

			master();
			~master();

			template <class U> std::shared_ptr<U>	create_window(glutpp::window::desc_shared wd)
			{
				std::shared_ptr<U> u(new U(wd));
				
				reg(u);
				
				u->init();
				
				return u;
			}
			
			window::window_shared		get_window(GLFWwindow*);
			int				reg(window::window_shared);



			//void  CallGlutCreateWindow(char * setTitle, glutpp::window * glutWindow);
			//void  CallGlutMainLoop(void);

			//void  DisableIdleFunction(void);
			//void  EnableIdleFunction(void);
			//int   IdleFunctionEnabled(void);

			//int   IdleSetToCurrentWindow(void);
			//void  SetIdleToCurrentWindow(void);
			FT_Library						ft_;
			
			
			std::shared_ptr<glutpp::gui::object::object_factory>	object_factory_;


		private:
			unsigned int						f();
			void							f(unsigned int);
			unsigned int						flag_;
			
			GLFWwindow*						currentIdleWindow_;
			std::map<GLFWwindow*,window::window_weak>		windows_;


			std::map<int, std::shared_ptr<glutpp::glsl::program> >	programs_;
			std::shared_ptr<glutpp::glsl::program>			current_;
	};

	extern "C" master __master;
}


#endif




