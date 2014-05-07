#ifndef __GLUTPP_MASTER_H__
#define __GLUTPP_MASTER_H__

#include <map>
#include <memory>

#include <boost/asio/io_service.hpp>

/*
#include <galaxy/flag.hpp>
#include <galaxy/sig/signal.hpp>
*/

#include <ft2build.h>
#include FT_FREETYPE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Nebula/config.hpp> // Nebula/config.hpp.in
#include <Nebula/Actor/Types.hpp>
#include <Nebula/Memory/smart_ptr.hpp>

#include <Nebula/Flag.hpp>

namespace Neb {
	class master: public gal::flag<unsigned int> {
		public:
			typedef std::map< GLFWwindow*, Neb::unique_ptr<Neb::window::window> >			Window_Map_Type;
			

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
			std::shared_ptr<Neb::glsl::program>		use_program(Neb::program_name::e);
			std::shared_ptr<Neb::glsl::program>		get_program(Neb::program_name::e);
			std::shared_ptr<Neb::glsl::program>		current_program();
			void						create_programs();



		public:

			master();
			~master();
			
			static Neb::weak_ptr<master>					global();
			static void							global(Neb::weak_ptr<master>);
			
			Neb::weak_ptr<Neb::window::window>				getWindowMain();
			void								setWindowMain(Neb::weak_ptr<Neb::window::window>);
			
			template <class U> Neb::weak_ptr<U>				create_window(Neb::weak_ptr<Neb::window::desc> wd) {
				GLUTPP_DEBUG_0_FUNCTION;

				Neb::unique_ptr<U> u(new U(wd));
				
				auto g = reg(u);

				u->init();

				windows_[g] = u;
				
				auto wm = getWindowMain();
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

			/** @name Search @{ */
			Neb::weak_ptr<Neb::Actor::Base>					getActor(Neb::Actor::addr);


			Neb::weak_ptr<Neb::window::window>					get_window(GLFWwindow*);
			GLFWwindow*								reg(Neb::window::window_s);

			//Neb::Actor::raw_factory_s						get_raw_factory();

			unsigned int								f();
			void									f(unsigned int);
		public:
			/** @name Font @{ */
			FT_Library								ft_;
			/** @} */

			/** @name Boost Asio @{ */
			boost::asio::io_service							ios_;
			/** @} */

			/** @name Factories @{ */
			//Neb::gui::object::object_factory_s					object_factory_;
			//Neb::Actor::raw_factory_s						actor_raw_factory_;
			//Neb::Shape::raw_factory_s						shape_raw_factory_;
			/** @} */
		private:
			unsigned int								flag_;
	
			//GLFWwindow*								currentIdleWindow_;
			Window_Map_Type								windows_;
			static Neb::window::window_w						window_main_;
			
			std::map<int, std::shared_ptr<Neb::glsl::program> >			programs_;
			std::shared_ptr<Neb::glsl::program>					current_;

			static Neb::unique_ptr<Neb::master>					g_master_;
	};

	//extern "C" master_s g_master;
}


#endif




