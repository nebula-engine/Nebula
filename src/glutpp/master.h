#ifndef __GLUTPP_MASTER_H__
#define __GLUTPP_MASTER_H__

#include <map>
#include <memory>

#include <gal/flag.h>
#include <gal/sig/signal.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glutpp/config.h>


namespace glutpp {
	class master: public gal::flag<> {
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
			std::shared_ptr<glutpp::glsl::program>		use_program(glutpp::program_name::e);
			std::shared_ptr<glutpp::glsl::program>		get_program(glutpp::program_name::e);
			std::shared_ptr<glutpp::glsl::program>		current_program();
			int						create_programs();



		public:

			master();
			~master();

			template <class U> std::shared_ptr<U>	create_window(glutpp::window::desc_s wd)
			{
				std::shared_ptr<U> u(new U(wd));
				
				reg(u);
				
				u->init();
				
				return u;
			}
			
			glutpp::window::window_s	get_window(GLFWwindow*);
			int				reg(glutpp::window::window_s);
			
			glutpp::actor::raw_factory_s	get_raw_factory();

			unsigned int			f();
			void				f(unsigned int);

		public:
			FT_Library						ft_;
					
			std::shared_ptr<glutpp::gui::object::object_factory>	object_factory_;

			glutpp::actor::raw_factory_s	raw_factory_;
		private:
			unsigned int						flag_;
			
			
			
			GLFWwindow*						currentIdleWindow_;
			std::map<GLFWwindow*,glutpp::window::window_w>		windows_;


			std::map<int, std::shared_ptr<glutpp::glsl::program> >	programs_;
			std::shared_ptr<glutpp::glsl::program>			current_;
	};
	
	extern "C" master __master;
}


#endif




