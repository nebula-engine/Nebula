#ifndef __NEBULA_APP_GFX_H__
#define __NEBULA_APP_GFX_H__

#include <fstream>

#include <boost/asio/io_service.hpp>
#include <boost/archive/polymorphic_xml_iarchive.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <Galaxy-Standard/shared.hpp>

#include <Galaxy-Network/decl.hpp>

#include <Nebula/Types.hh>
#include <Nebula/App/__base.hpp>
#include <Nebula/Graphics/Types.hh>
#include <Nebula/Graphics/Window/Util/Parent.hh>

namespace neb {
	namespace App {
		/** @brief gfx
		 * 
		 * graphics and window handling
		 */
		class __gfx:
			virtual public neb::App::__base,
			virtual public neb::gfx::Window::Util::Parent
		{
			public:
				typedef ::std::map< GLFWwindow*, sp::shared_ptr<neb::gfx::Window::Base> >			glfwwindow_map_type;

				static sp::shared_ptr<neb::App::__gfx>		global();


				static void					static_error_fun(int,char const *);
				static void					static_window_pos_fun(GLFWwindow*,int,int);
				static void					static_window_size_fun(GLFWwindow*,int,int);
				static void					static_window_close_fun(GLFWwindow*);
				static void					static_window_refresh_fun(GLFWwindow*);
				//static void					static_window_focus_fun(GLFWwindow*,int);
				//static void					static_window_iconify_fun(GLFWwindow*,int);
				//static void					static_window_buffer_size_fun(GLFWwindow*,int,int);
				static void					static_mouse_button_fun(GLFWwindow*,int,int,int);
				static void					static_key_fun(GLFWwindow*,int,int,int,int);



			public:

				//GLFWwindow*								currentIdleWindow_;
				glfwwindow_map_type							windows_glfw_;


				FT_Library								ft_;
		};
	}
}
#endif





