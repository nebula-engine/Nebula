#ifndef __NEBULA_APP_GFX_H__
#define __NEBULA_APP_GFX_H__

#include <fstream>

#include <boost/asio/io_service.hpp>
#include <boost/archive/polymorphic_xml_iarchive.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <Galaxy-Standard/shared.hpp>

#include <Galaxy-Network/decl.hpp>

#include <neb/util/decl.hpp>
#include <neb/app/__base.hpp>
#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/window/util/Parent.hh>

namespace neb {
	namespace app {
		/** @brief gfx
		 * 
		 * graphics and window handling
		 */
		class __gfx:
			virtual public neb::app::__base,
			virtual public neb::gfx::window::util::parent
			virtual public neb::gfx::gui::layout::util::parent,
		{
			public:
				typedef ::std::map< GLFWwindow*, sp::shared_ptr<neb::gfx::window::base> >			glfwwindow_map_type;

				virtual void					init();

				static sp::shared_ptr<neb::app::__gfx>		global();


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
				FT_Face									face_;
		};
	}
}
#endif





