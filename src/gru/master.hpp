#ifndef __GLUTPP_MASTER_H__
#define __GLUTPP_MASTER_H__

#include <map>
#include <memory>

#include <galaxy/flag.hpp>
#include <galaxy/sig/signal.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <gru/config.hpp>


namespace glutpp {
	
	class master:
		public gal::flag<unsigned int>
	{
		public:
	
			//typedef std::shared_ptr<WINDOW>		WINDOW_S;
			//typedef std::weak_ptr<WINDOW>		WINDOW_W;

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
			void		Command(std::string);

			
		public:
			std::shared_ptr<glutpp::glsl::program>		use_program(glutpp::program_name::e);
			std::shared_ptr<glutpp::glsl::program>		get_program(glutpp::program_name::e);
			std::shared_ptr<glutpp::glsl::program>		current_program();
			void						create_programs();



		public:

			master();
			~master();
			
			static master_s		Global();
			static void		Global(master_s);
			
			window::window_s	Main_Window();
			void			Main_Window(window::window_s);
			
			template <class U> std::shared_ptr<U>	create_window(glutpp::window::desc_s wd)
			{
				GLUTPP_DEBUG_0_FUNCTION;

				auto p = new U(wd);
				
				std::shared_ptr<U> u(p);

				reg(u);

				u->init();
				
				auto wm = Main_Window();
				if(!wm) {
					Main_Window(u);
					//fprintf(stderr, "window main set\n");
					//abort();
				} else {
					//fprintf(stderr, "window main already set\n");
					//abort();
				}
				
				return u;
			}

			glutpp::window::window_s	get_window(GLFWwindow*);
			int				reg(glutpp::window::window_s);

			glutpp::actor::raw_factory_s	get_raw_factory();

			unsigned int			f();
			void				f(unsigned int);
		public:
			// font
			FT_Library						ft_;

			// factories
			glutpp::gui::object::object_factory_s			object_factory_;
			glutpp::actor::raw_factory_s				raw_factory_;
		private:
			unsigned int						flag_;
			
			//GLFWwindow*						currentIdleWindow_;
			std::map<GLFWwindow*,glutpp::window::window_w>		windows_;
			static glutpp::window::window_w				window_main_;
			
			std::map<int, std::shared_ptr<glutpp::glsl::program> >	programs_;
			std::shared_ptr<glutpp::glsl::program>			current_;

			static master_s						g_master_;
	};

	//extern "C" master_s g_master;
}


#endif




